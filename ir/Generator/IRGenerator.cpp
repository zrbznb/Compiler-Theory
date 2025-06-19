///
/// @file IRGenerator.cpp
/// @brief AST遍历产生线性IR的源文件
/// @author zenglj (zenglj@live.com)
/// @version 1.1
/// @date 2024-11-23
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// <tr><td>2024-11-23 <td>1.1     <td>zenglj  <td>表达式版增强
/// </table>
///
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include "GlobalVariable.h"
#include "AST.h"
#include "Common.h"
#include "Function.h"
#include "IRCode.h"
#include "IRGenerator.h"
#include "Module.h"
#include "EntryInstruction.h"
#include "LabelInstruction.h"
#include "ExitInstruction.h"
#include "FuncCallInstruction.h"
#include "BinaryInstruction.h"
#include "MoveInstruction.h"
#include "GotoInstruction.h"
#include "CondGotoInstruction.h"
#include "Move2Instruction.h"
#include "ArgInstruction.h"
#include "PointerType.h"
#include "Value.h"
#include "Types/ArrayType.h"
#include "Instructions/ArrayAccessInstruction.h"
#include "Types/IntegerType.h"
#include "PointerType.h"

/// @brief 构造函数
/// @param _root AST的根
/// @param _module 符号表
IRGenerator::IRGenerator(ast_node * _root, Module * _module) : root(_root), module(_module)
{
    /* 叶子节点 */
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_LITERAL_UINT] = &IRGenerator::ir_leaf_node_uint;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_VAR_ID] = &IRGenerator::ir_leaf_node_var_id;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_TYPE] = &IRGenerator::ir_leaf_node_type;

    /* 表达式运算 */
    ast2ir_handlers[ast_operator_type::AST_OP_SUB] = &IRGenerator::ir_sub;
    ast2ir_handlers[ast_operator_type::AST_OP_ADD] = &IRGenerator::ir_add;
    ast2ir_handlers[ast_operator_type::AST_OP_MUL] = &IRGenerator::ir_mul;
    ast2ir_handlers[ast_operator_type::AST_OP_DIV] = &IRGenerator::ir_div;
    ast2ir_handlers[ast_operator_type::AST_OP_MOD] = &IRGenerator::ir_mod;
    
    /* 关系运算 */
    ast2ir_handlers[ast_operator_type::AST_OP_LT] = &IRGenerator::ir_lt;
    ast2ir_handlers[ast_operator_type::AST_OP_GT] = &IRGenerator::ir_gt;
    ast2ir_handlers[ast_operator_type::AST_OP_LE] = &IRGenerator::ir_le;
    ast2ir_handlers[ast_operator_type::AST_OP_GE] = &IRGenerator::ir_ge;
    ast2ir_handlers[ast_operator_type::AST_OP_EQ] = &IRGenerator::ir_eq;
    ast2ir_handlers[ast_operator_type::AST_OP_NEQ] = &IRGenerator::ir_neq;
    
    /* 逻辑运算 */
    ast2ir_handlers[ast_operator_type::AST_OP_AND] = &IRGenerator::ir_and;
    ast2ir_handlers[ast_operator_type::AST_OP_OR] = &IRGenerator::ir_or;
    ast2ir_handlers[ast_operator_type::AST_OP_NOT] = &IRGenerator::ir_not;
    
    /* 控制流 */
    ast2ir_handlers[ast_operator_type::AST_OP_IF] = &IRGenerator::ir_if;
    ast2ir_handlers[ast_operator_type::AST_OP_IF_ELSE] = &IRGenerator::ir_if_else;
    ast2ir_handlers[ast_operator_type::AST_OP_WHILE] = &IRGenerator::ir_while;
    ast2ir_handlers[ast_operator_type::AST_OP_FOR] = &IRGenerator::ir_for;
    ast2ir_handlers[ast_operator_type::AST_OP_BREAK] = &IRGenerator::ir_break;
    ast2ir_handlers[ast_operator_type::AST_OP_CONTINUE] = &IRGenerator::ir_continue;

    /* 语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_ASSIGN] = &IRGenerator::ir_assign;
    ast2ir_handlers[ast_operator_type::AST_OP_RETURN] = &IRGenerator::ir_return;

    /* 函数调用 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_CALL] = &IRGenerator::ir_function_call;

    /* 函数定义 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_DEF] = &IRGenerator::ir_function_define;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGenerator::ir_function_formal_params;

    /* 变量定义语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_DECL_STMT] = &IRGenerator::ir_declare_statment;
    ast2ir_handlers[ast_operator_type::AST_OP_VAR_DECL] = &IRGenerator::ir_variable_declare;

    /* 语句块 */
    ast2ir_handlers[ast_operator_type::AST_OP_BLOCK] = &IRGenerator::ir_block;

    /* 编译单元 */
    ast2ir_handlers[ast_operator_type::AST_OP_COMPILE_UNIT] = &IRGenerator::ir_compile_unit;

    /* 数组相关 */
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_TYPE] = &IRGenerator::ir_array_type;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_DECL] = &IRGenerator::ir_array_decl;
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_ACCESS] = &IRGenerator::ir_array_access;
}

/// @brief 遍历抽象语法树产生线性IR，保存到IRCode中
/// @param root 抽象语法树
/// @param IRCode 线性IR
/// @return true: 成功 false: 失败
bool IRGenerator::run()
{
    ast_node * node;

    // 从根节点进行遍历
    node = ir_visit_ast_node(root);

    return node != nullptr;
}

///
/// @param node AST节点
/// @return 成功返回node节点，否则返回nullptr
ast_node * IRGenerator::ir_visit_ast_node(ast_node * node)
{
    // 空节点
    if (nullptr == node) {
        return nullptr;
    }

    bool result;

    std::unordered_map<ast_operator_type, ast2ir_handler_t>::const_iterator pIter;
    pIter = ast2ir_handlers.find(node->node_type);
    if (pIter == ast2ir_handlers.end()) {
        // 没有找到，则说明当前不支持
        result = (this->ir_default)(node);
    } else {
        result = (this->*(pIter->second))(node);
    }

    if (!result) {
        // 语义解析错误，则出错返回
        node = nullptr;
    }

    return node;
}

/// @brief 未知节点类型的节点处理
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_default(ast_node * node)
{
    // 未知的节点
    printf("Unkown node(%d)\n", (int) node->node_type);
    return true;
}

/// @brief 编译单元AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_compile_unit(ast_node * node)
{
    module->setCurrentFunction(nullptr);

    for (auto son: node->sons) {

        // 检查是否是全局数组声明
        if (son->node_type == ast_operator_type::AST_OP_ARRAY_DECL) {
            // 处理全局数组声明
            if (!ir_global_array_decl(son)) {
                return false;
            }
        } 
        else {
            // 处理其他类型的节点
            ast_node* son_node = ir_visit_ast_node(son);
            if (!son_node) {
                return false;
            }
        }
    }

    return true;
}

/// @brief 函数定义AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_function_define(ast_node * node)
{
    bool result;

    // 创建一个函数，用于当前函数处理
    if (module->getCurrentFunction()) {
        // 函数中嵌套定义函数，这是不允许的，错误退出
        // TODO 自行追加语义错误处理
        return false;
    }

    // 函数定义的AST包含四个孩子
    // 第一个孩子：函数返回类型
    // 第二个孩子：函数名字
    // 第三个孩子：形参列表
    // 第四个孩子：函数体即block
    ast_node * type_node = node->sons[0];
    ast_node * name_node = node->sons[1];
    ast_node * param_node = node->sons[2];
    ast_node * block_node = node->sons[3];

    // 创建一个新的函数定义
    Function * newFunc = module->newFunction(name_node->name, type_node->type);
    if (!newFunc) {
        // 新定义的函数已经存在，则失败返回。
        // TODO 自行追加语义错误处理
        return false;
    }

    // 当前函数设置有效，变更为当前的函数
    module->setCurrentFunction(newFunc);

    // 进入函数的作用域
    module->enterScope();

    // 获取函数的IR代码列表，用于后面追加指令用，注意这里用的是引用传值
    InterCode & irCode = newFunc->getInterCode();

    // 这里也可增加一个函数入口Label指令，便于后续基本块划分

    // 创建并加入Entry入口指令
    irCode.addInst(new EntryInstruction(newFunc));

    // 创建出口指令并不加入出口指令，等函数内的指令处理完毕后加入出口指令
    LabelInstruction * exitLabelInst = new LabelInstruction(newFunc);

    // 函数出口指令保存到函数信息中，因为在语义分析函数体时return语句需要跳转到函数尾部，需要这个label指令
    newFunc->setExitLabel(exitLabelInst);

    // 遍历形参，创建形参对应的局部变量和指令
    result = ir_function_formal_params(param_node);
    if (!result) {
        // 形参解析失败
        // TODO 自行追加语义错误处理
        return false;
    }
    node->blockInsts.addInst(param_node->blockInsts);

    // 新建一个Value，用于保存函数的返回值，如果没有返回值可不用申请
    LocalVariable * retValue = nullptr;
    if (!type_node->type->isVoidType()) {
        // 保存函数返回值变量到函数信息中，在return语句翻译时需要设置值到这个变量中
        retValue = static_cast<LocalVariable *>(module->newVarValue(type_node->type));
        
        // 特殊处理main函数，初始化返回值为0
        if (name_node->name == "main") {
            ConstInt* zeroVal = module->newConstInt(0);
            MoveInstruction* initRetInst = new MoveInstruction(newFunc, retValue, zeroVal);
            node->blockInsts.addInst(initRetInst);
        }
    }
    newFunc->setReturnValue(retValue);

    // 这里最好设置返回值变量的初值为0，以便在没有返回值时能够返回0

    // 函数内已经进入作用域，内部不再需要做变量的作用域管理
    block_node->needScope = false;
	module->newVarValue(IntegerType::getTypeInt(), "zhangrenbin");
    // 遍历block
    result = ir_block(block_node);
    if (!result) {
        // block解析失败
        // TODO 自行追加语义错误处理
        return false;
    }

    // IR指令追加到当前的节点中
    node->blockInsts.addInst(block_node->blockInsts);

    // 此时，所有指令都加入到当前函数中，也就是node->blockInsts

    // node节点的指令移动到函数的IR指令列表中
    irCode.addInst(node->blockInsts);

    // 添加函数出口Label指令，主要用于return语句跳转到这里进行函数的退出
    irCode.addInst(exitLabelInst);

    // 函数出口指令
    irCode.addInst(new ExitInstruction(newFunc, retValue));

    // 恢复成外部函数
    module->setCurrentFunction(nullptr);

    // 退出函数的作用域
    module->leaveScope();

    return true;
}

/// @brief 形式参数AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_function_formal_params(ast_node * node)
{
    Function * currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        return false;
    }
    
    // 没有参数的情况下直接返回成功
    if (node->sons.empty()) {
        return true;
    }
    
    for (auto& paramNode : node->sons) {
        // 获取参数类型和名称
        Type* paramType = paramNode->type;
        std::string paramName = paramNode->sons[1]->name; // 第二个子节点是参数名
        
        // 创建形参值对象，用于表示从实参传递过来的值
        FormalParam* param = new FormalParam(paramType, paramName);
        currentFunc->getParams().push_back(param);
        
        // 创建对应的局部变量，用于在函数内使用
        Value* localVar = module->newVarValue(paramType, paramName);
        
        // 生成形参到局部变量的赋值指令
        MoveInstruction* moveInst = new MoveInstruction(currentFunc, localVar, param);
        node->blockInsts.addInst(moveInst);
    }
    
    return true;
}

/// @brief 函数调用AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_function_call(ast_node * node)
{
    // 特殊处理std.c中的内置数组函数
    if (node->sons[0]->name == "getarray") {
        return processGetArrayCall(node);
    }
    else if (node->sons[0]->name == "putarray") {
        return processPutArrayCall(node);
    }
    
    // 原有方法的实现保持不变
    std::vector<Value *> realParams;

    // 获取当前正在处理的函数
    Function * currentFunc = module->getCurrentFunction();

    // 函数调用的节点包含两个节点：
    // 第一个节点：函数名节点
    // 第二个节点：实参列表节点

    std::string funcName = node->sons[0]->name;
    int64_t lineno = node->sons[0]->line_no;

    ast_node * paramsNode = node->sons[1];

    // 根据函数名查找函数，看是否存在。若不存在则出错
    // 这里约定函数必须先定义后使用
    auto calledFunction = module->findFunction(funcName);
    if (nullptr == calledFunction) {
        minic_log(LOG_ERROR, "函数(%s)未定义或声明", funcName.c_str());
        return false;
    }

    // 当前函数存在函数调用
    currentFunc->setExistFuncCall(true);

    // 如果没有孩子，也认为是没有参数
    if (!paramsNode->sons.empty()) {
        int32_t argsCount = (int32_t) paramsNode->sons.size();

        // 当前函数中调用函数实参个数最大值统计，实际上是统计实参传递需在栈中分配的大小
        if (argsCount > currentFunc->getMaxFuncCallArgCnt()) {
            currentFunc->setMaxFuncCallArgCnt(argsCount);
        }

        // 遍历参数列表，孩子是表达式
        // 这里自左往右计算表达式
        for (auto son: paramsNode->sons) {
            // 遍历Block的每个语句，进行显示或者运算
            ast_node * temp = ir_visit_ast_node(son);
            if (!temp) {
                return false;
            }

            realParams.push_back(temp->val);
            node->blockInsts.addInst(temp->blockInsts);
            
            // 为每个参数生成ARG指令，用于函数调用前的参数准备
            ArgInstruction* argInst = new ArgInstruction(currentFunc, temp->val);
            node->blockInsts.addInst(argInst);
            
            // 记录实参数量，用于栈空间分配和寄存器参数优化
            currentFunc->realArgCountInc();
        }
    }

    // 参数检查：不再严格要求参数数量匹配，以支持内置函数的可变参数
    if (!calledFunction->isBuiltin() && realParams.size() != calledFunction->getParams().size()) {
        // 只对非内置函数进行严格参数个数检查
        minic_log(LOG_ERROR, "第%lld行的被调用函数(%s)参数数量不匹配：期望%zu个参数，提供了%zu个参数", 
                (long long) lineno, funcName.c_str(),
                calledFunction->getParams().size(), realParams.size());
        return false;
    }

    // 返回调用有返回值，则需要分配临时变量，用于保存函数调用的返回值
    Type * type = calledFunction->getReturnType();

    // 创建函数调用指令
    FuncCallInstruction * funcCallInst = new FuncCallInstruction(currentFunc, calledFunction, realParams, type);
    node->blockInsts.addInst(funcCallInst);

    // 函数调用结果Value保存到node中，可能为空，上层节点可利用这个值
    node->val = funcCallInst;
    
    // 重置参数计数器，为下一次函数调用准备
    currentFunc->realArgCountReset();

    return true;
}

/// @brief 语句块（含函数体）AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_block(ast_node * node)
{
    // 进入作用域
    if (node->needScope) {
        module->enterScope();
    }

    std::vector<ast_node *>::iterator pIter;
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        ast_node * temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }

        node->blockInsts.addInst(temp->blockInsts);
    }

    // 离开作用域
    if (node->needScope) {
        module->leaveScope();
    }

    return true;
}

/// @brief 整数加法AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_add(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    Move2Instruction * movInst=nullptr;
    if (src1_node->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        movInst = new Move2Instruction(module->getCurrentFunction(), left->val, 1);
        left->val = movInst;
    }
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(movInst);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    Move2Instruction * movInst2=nullptr;
    if (src2_node->node_type == ast_operator_type::AST_OP_ARRAY_ACCESS) {
        movInst2 = new Move2Instruction(module->getCurrentFunction(), right->val, 1);
        right->val = movInst2;
    }
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(movInst2);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * addInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_ADD_I,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeInt());

    // 创建临时变量保存IR的值，以及线性IR指令
    
    
    node->blockInsts.addInst(addInst);

    node->val = addInst;

    return true;
}

/// @brief 整数乘法AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_mul(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 乘法节点，左结合，先计算左节点，后计算右节点

    // 乘法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }

    // 乘法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    BinaryInstruction * mulInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_MUL_I,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeInt());

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(mulInst);

    node->val = mulInst;

    return true;
}

/// @brief 整数除法AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_div(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 除法节点，左结合，先计算左节点，后计算右节点

    // 除法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }

    // 除法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    BinaryInstruction * divInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_DIV_I,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeInt());

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(divInst);

    node->val = divInst;

    return true;
}

/// @brief 整数求余AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_mod(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 求余节点，左结合，先计算左节点，后计算右节点

    // 求余的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }

    // 求余的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    BinaryInstruction * modInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_MOD_I,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeInt());

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(modInst);

    node->val = modInst;

    return true;
}

/// @brief 整数减法/求负AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_sub(ast_node * node)
{
    // 处理单操作数的求负运算
    if (node->sons.size() == 1) {
        ast_node * operand_node = node->sons[0];
        
        // 处理操作数
        ast_node * operand = ir_visit_ast_node(operand_node);
        if (!operand) {
            return false;
        }

        // 创建求负指令
        BinaryInstruction * negInst = new BinaryInstruction(module->getCurrentFunction(),
                                                            IRInstOperator::IRINST_OP_NEG_I,
                                                            operand->val,
                                                            nullptr,
                                                            IntegerType::getTypeInt());

        // 创建临时变量保存IR的值，以及线性IR指令
        node->blockInsts.addInst(operand->blockInsts);
        node->blockInsts.addInst(negInst);

        node->val = negInst;
    } 
    // 处理双操作数的减法运算
    else if (node->sons.size() == 2) {
        ast_node * src1_node = node->sons[0];
        ast_node * src2_node = node->sons[1];

        // 处理左操作数
        ast_node * left = ir_visit_ast_node(src1_node);
        if (!left) {
            return false;
        }

        // 处理右操作数
        ast_node * right = ir_visit_ast_node(src2_node);
        if (!right) {
            return false;
        }
        Move2Instruction * Move2Inst1;
        Move2Instruction * Move2Inst2;
		Value* ZEROval = module->newConstInt((int32_t) 0);
        Value * ONEval = module->newConstInt((int32_t) 1);
        
		node->blockInsts.addInst(left->blockInsts);
        node->blockInsts.addInst(right->blockInsts);
        if (right->node_type == ast_operator_type::AST_OP_NOT) {
            // Value * v = module->newVarValue(IntegerType::getTypeInt(), "zhangrenbin");
            Value * v  =module->findVarValue("zhangrenbin");
            LabelInstruction * label1 = new LabelInstruction(module->getCurrentFunction());
            LabelInstruction * label2 = new LabelInstruction(module->getCurrentFunction());
            LabelInstruction * labelexit = new LabelInstruction(module->getCurrentFunction());
            CondGotoInstruction * condGoto = new CondGotoInstruction(module->getCurrentFunction(), right->val, label1, label2);
            Move2Inst1 = new Move2Instruction(module->getCurrentFunction(), ONEval);
            MoveInstruction * movInst1 = new MoveInstruction(module->getCurrentFunction(), v, Move2Inst1);
            Move2Inst2 = new Move2Instruction(module->getCurrentFunction(), ZEROval);
			MoveInstruction * movInst2 = new MoveInstruction(module->getCurrentFunction(), v, Move2Inst2);
			node->blockInsts.addInst(condGoto);
            node->blockInsts.addInst(label1);
            node->blockInsts.addInst(Move2Inst1);
            node->blockInsts.addInst(movInst1);
            node->blockInsts.addInst(new GotoInstruction(module->getCurrentFunction(), labelexit));
            node->blockInsts.addInst(label2);
            node->blockInsts.addInst(Move2Inst2);
            node->blockInsts.addInst(movInst2);
            node->blockInsts.addInst(new GotoInstruction(module->getCurrentFunction(), labelexit));
            node->blockInsts.addInst(labelexit);
            BinaryInstruction * subInst = new BinaryInstruction(module->getCurrentFunction(),
                                                                IRInstOperator::IRINST_OP_SUB_I,
                                                                left->val,
                                                                v,
                                                                IntegerType::getTypeInt());
            node->blockInsts.addInst(subInst);
            node->val = subInst;
        }
        else {
			BinaryInstruction * subInst = new BinaryInstruction(module->getCurrentFunction(),
			IRInstOperator::IRINST_OP_SUB_I,
			left->val,
			right->val,
			IntegerType::getTypeInt());
            node->blockInsts.addInst(subInst);
            node->val = subInst;
		}

        
    } else {
        // 操作数数量不正确
        return false;
    }
    return true;
}

/// @brief 赋值AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_assign(ast_node * node)
{
    ast_node * son1_node = node->sons[0];
    ast_node * son2_node = node->sons[1];

    // 赋值节点，自右往左运算

    // 赋值运算符的左侧操作数
    ast_node * left = ir_visit_ast_node(son1_node);
    if (!left) {
        // 某个变量没有定值
        // 这里缺省设置变量不存在则创建，因此这里不会错误
        return false;
    }

    // 赋值运算符的右侧操作数
    ast_node * right = ir_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    MoveInstruction * movInst = new MoveInstruction(module->getCurrentFunction(), left->val, right->val);
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(movInst);

    // 这里假定赋值的类型是一致的
    node->val = movInst;

    return true;
}

/// @brief return节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_return(ast_node * node)
{
    ast_node * right = nullptr;
    Function * currentFunc = module->getCurrentFunction();

    // return语句可能没有没有表达式，也可能有，因此这里必须进行区分判断
    if (!node->sons.empty()) {
        ast_node * son_node = node->sons[0];

        // 返回的表达式的指令保存在right节点中
        right = ir_visit_ast_node(son_node);
        if (!right) {
            return false;
        }
    }

    // 函数返回值的处理
    LocalVariable* returnValue = currentFunc->getReturnValue();

    // 如果存在返回值表达式且函数有返回值类型
    if (right && returnValue) {
        // 创建临时变量保存IR的值，以及线性IR指令
        node->blockInsts.addInst(right->blockInsts);

        // 将表达式的值赋值给返回值变量
        node->blockInsts.addInst(new MoveInstruction(currentFunc, returnValue, right->val));
        node->val = right->val;
    } 
    // 如果不存在返回值表达式，但函数是非void类型，默认返回0
    else if (returnValue && !right && currentFunc->getName() != "main") {
        // 对于非main函数，如果没有提供返回值但函数返回类型不是void，默认返回0
        Value* zeroVal = module->newConstInt(0);
        node->blockInsts.addInst(new MoveInstruction(currentFunc, returnValue, zeroVal));
    }
    else {
        // 没有返回值或函数是void类型
        node->val = nullptr;
    }

    // 跳转到函数的尾部出口指令上
    node->blockInsts.addInst(new GotoInstruction(currentFunc, currentFunc->getExitLabel()));

    return true;
}

/// @brief 类型叶子节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_type(ast_node * node)
{
    // 不需要做什么，直接从节点中获取即可。

    return true;
}

/// @brief 标识符叶子节点翻译成线性中间IR，变量声明的不走这个语句
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_var_id(ast_node * node)
{
    Value * val;

    // 查找ID型Value
    // 变量，则需要在符号表中查找对应的值

    val = module->findVarValue(node->name);

    node->val = val;

    return true;
}

/// @brief 无符号整数字面量叶子节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_uint(ast_node * node)
{
    ConstInt * val;

    // 新建一个整数常量Value
    val = module->newConstInt((int32_t) node->integer_val);

    node->val = val;

    return true;
}

/// @brief 变量声明语句节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_declare_statment(ast_node * node)
{
    bool result = false;

    for (auto & child: node->sons) {

        // 遍历每个变量声明
        if(child->node_type ==ast_operator_type::AST_OP_ARRAY_DECL) {
			// 不是变量声明节点，跳过
            if (module->getCurrentFunction())
                result = ir_array_decl(child);
            else result= ir_global_array_decl(child);
        }
        else 
        	result = ir_variable_declare(child);
        if (!result) {
            break;
        }
        
        // 如果变量声明中有初始值表达式，则将其指令添加到声明语句节点
        if (child->blockInsts.getInsts().size() > 0) {
            node->blockInsts.addInst(child->blockInsts);
        }
    }

    return result;
}

/// @brief 变量定声明节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_variable_declare(ast_node * node)
{
    // 共有两个孩子，第一个类型，第二个变量名
    // 或者共有三个孩子，第一个类型，第二个变量名，第三个初值表达式

    // 创建变量
    node->val = module->newVarValue(node->sons[0]->type, node->sons[1]->name);
    
    // 如果有初始值表达式，处理赋值操作
    if (node->sons.size() > 2 && node->sons[2] != nullptr) {
        Function * currentFunc = module->getCurrentFunction();
        
        // 处理初始值表达式
        ast_node *initExpr = ir_visit_ast_node(node->sons[2]);
        if (!initExpr) {
            return false;
        }
        
        // 将表达式的指令添加到变量声明节点
        node->blockInsts.addInst(initExpr->blockInsts);
        
        // 创建赋值指令
        MoveInstruction *moveInst = new MoveInstruction(currentFunc, node->val, initExpr->val);
        node->blockInsts.addInst(moveInst);
    }

    return true;
}

/// @brief 创建新的标签指令
LabelInstruction * IRGenerator::createLabel()
{
    static int labelCounter = 1; // 静态计数器，确保标签按序号递增
    LabelInstruction *label = new LabelInstruction(module->getCurrentFunction());
    
    // 手动设置标签名称为 .L1, .L2 等格式
    label->setIRName(".L" + std::to_string(labelCounter++));
    
    return label;
}

/// @brief 小于比较运算
bool IRGenerator::ir_lt(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 比较节点，左结合，先计算左节点，后计算右节点
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }

    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    BinaryInstruction * ltInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_LT,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool()); // 布尔值用整型表示
	BinaryInstruction * neInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_NEQ,
                                                       ltInst,
                                                       module->newConstInt(0),
                                                       IntegerType::getTypeBool()); // 布尔值用整型表示

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(ltInst);
    node->blockInsts.addInst(neInst);
    node->val = neInst;
    return true;
}

/// @brief 大于比较运算
bool IRGenerator::ir_gt(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 比较节点，左结合，先计算左节点，后计算右节点
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }

    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    BinaryInstruction * gtInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_GT,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool()); // 布尔值用整型表示
	BinaryInstruction * neInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_NEQ,
                                                       gtInst,
                                                       module->newConstInt(0),
                                                       IntegerType::getTypeBool()); // 布尔值用整型表示
													   

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(gtInst);
    node->blockInsts.addInst(neInst);
    node->val = neInst;
    return true;
}

/// @brief 小于等于比较运算
bool IRGenerator::ir_le(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 比较节点，左结合，先计算左节点，后计算右节点
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }

    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    BinaryInstruction * leInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_LE,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool()); // 布尔值用整型表示

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(leInst);
    node->val = leInst;
    return true;
}

/// @brief 大于等于比较运算
bool IRGenerator::ir_ge(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 比较节点，左结合，先计算左节点，后计算右节点
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }

    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    BinaryInstruction * geInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_GE,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool()); // 布尔值用整型表示

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(geInst);
    node->val = geInst;
    return true;
}

/// @brief 等于比较运算
bool IRGenerator::ir_eq(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 比较节点，左结合，先计算左节点，后计算右节点
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }

    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    BinaryInstruction * eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_EQ,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool()); // 布尔值用整型表示

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(eqInst);
    node->val = eqInst;
    return true;
}

/// @brief 不等于比较运算
bool IRGenerator::ir_neq(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 比较节点，左结合，先计算左节点，后计算右节点
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        return false;
    }

    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        return false;
    }

    BinaryInstruction * neqInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_NEQ,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeBool()); // 布尔值用整型表示

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(neqInst);
    node->val = neqInst;
    return true;
}

/// @brief 逻辑与运算（短路求值）
bool IRGenerator::ir_and(ast_node * node)
{
    ast_node * left_node = node->sons[0];
    ast_node * right_node = node->sons[1];
    Function * currentFunc = module->getCurrentFunction();
    
    // 为短路求值创建标签
    LabelInstruction *rightEvalLabel = createLabel();
	LabelInstruction *trueLabel = createLabel();
	LabelInstruction *falselabel = createLabel();
    LabelInstruction *endLabel = createLabel();
    // 计算左操作数
    ast_node *left = ir_visit_ast_node(left_node);
    if (!left) {
        return false;
    }
    ast_node *right = ir_visit_ast_node(right_node);
    if (!right) {
        return false;
    }
    // 创建临时变量存储结果
    // LocalVariable *result = static_cast<LocalVariable *>(module->newVarValue(IntegerType::getTypeInt()));
	Value * result  =module->findVarValue("zhangrenbin");
    
    // 将指令添加到当前节点
    
    
    // 条件跳转：如果左操作数为真（非0），则评估右操作数，否则跳到结束
    CondGotoInstruction *LcondGoto = new CondGotoInstruction(currentFunc, left->val, rightEvalLabel, falselabel);

    
    // 将右操作数的结果赋值给结果变量
	CondGotoInstruction *RcondGoto = new CondGotoInstruction(currentFunc, right->val, trueLabel, falselabel);
    // MoveInstruction *moveRight = new MoveInstruction(currentFunc, result, right->val);
	
    
    // 跳转到结束标签
	node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(LcondGoto);
    node->blockInsts.addInst(rightEvalLabel);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(RcondGoto);
    node->blockInsts.addInst(trueLabel);
    node->blockInsts.addInst(new MoveInstruction(currentFunc, result, module->newConstInt(1)));
	node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));
	node->blockInsts.addInst(falselabel);
    node->blockInsts.addInst(new MoveInstruction(currentFunc, result, module->newConstInt(0)));
	node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));
    node->blockInsts.addInst(endLabel);
    node->val = result;
    return true;
}
bool IRGenerator::ir_or(ast_node * node)
{
    ast_node * left_node = node->sons[0];
    ast_node * right_node = node->sons[1];
    Function * currentFunc = module->getCurrentFunction();
    
    // 为短路求值创建标签
    LabelInstruction *rightEvalLabel = createLabel();
	LabelInstruction *trueLabel = createLabel();
	LabelInstruction *falselabel = createLabel();
    LabelInstruction *endLabel = createLabel();
    // 计算左操作数
    ast_node *left = ir_visit_ast_node(left_node);
    if (!left) {
        return false;
    }
    ast_node *right = ir_visit_ast_node(right_node);
    if (!right) {
        return false;
    }
    // 创建临时变量存储结果
    // LocalVariable *result = static_cast<LocalVariable *>(module->newVarValue(IntegerType::getTypeInt()));
	Value * result  =module->findVarValue("zhangrenbin");
    
    // 将指令添加到当前节点
    
    
    // 条件跳转：如果左操作数为真，则评估右操作数，否则跳到结束
    CondGotoInstruction *LcondGoto = new CondGotoInstruction(currentFunc, left->val, trueLabel, rightEvalLabel);

    
    // 将右操作数的结果赋值给结果变量
	CondGotoInstruction *RcondGoto = new CondGotoInstruction(currentFunc, right->val, trueLabel, falselabel);
    // MoveInstruction *moveRight = new MoveInstruction(currentFunc, result, right->val);
	
    
    // 跳转到结束标签
	node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(LcondGoto);
    node->blockInsts.addInst(rightEvalLabel);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(RcondGoto);
    node->blockInsts.addInst(trueLabel);
    node->blockInsts.addInst(new MoveInstruction(currentFunc, result, module->newConstInt(1)));
	node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));
	node->blockInsts.addInst(falselabel);
    node->blockInsts.addInst(new MoveInstruction(currentFunc, result, module->newConstInt(0)));
	node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));
    node->blockInsts.addInst(endLabel);
    node->val = result;
    return true;
}
/// @brief 逻辑或运算（短路求值）
// bool IRGenerator::ir_or(ast_node * node)
// {
//     ast_node * left_node = node->sons[0];
//     ast_node * right_node = node->sons[1];
//     Function * currentFunc = module->getCurrentFunction();
    
//     // 为短路求值创建标签
//     LabelInstruction *rightEvalLabel = createLabel();
//     LabelInstruction *endLabel = createLabel();
    
//     // 计算左操作数
//     ast_node *left = ir_visit_ast_node(left_node);
//     if (!left) {
//         return false;
//     }
    
//     // 创建临时变量存储结果
//     LocalVariable *result = static_cast<LocalVariable *>(module->newVarValue(IntegerType::getTypeInt()));
    
//     // 将指令添加到当前节点
//     node->blockInsts.addInst(left->blockInsts);
    
//     // 条件跳转：如果左操作数为真，则直接跳到结束，否则评估右操作数
//     CondGotoInstruction *condGoto = new CondGotoInstruction(currentFunc, left->val, endLabel, rightEvalLabel);
//     node->blockInsts.addInst(condGoto);
    
//     // 右操作数评估的标签
//     node->blockInsts.addInst(rightEvalLabel);
    
//     // 计算右操作数
//     ast_node *right = ir_visit_ast_node(right_node);
//     if (!right) {
//         return false;
//     }
//     node->blockInsts.addInst(right->blockInsts);
    
//     // 将右操作数的结果赋值给结果变量
//     MoveInstruction *moveRight = new MoveInstruction(currentFunc, result, right->val);
//     node->blockInsts.addInst(moveRight);
    
//     // 跳转到结束标签
//     GotoInstruction *gotoEnd = new GotoInstruction(currentFunc, endLabel);
//     node->blockInsts.addInst(gotoEnd);
    
//     // 结束标签：如果左操作数为真，则结果为1
//     node->blockInsts.addInst(endLabel);
    
//     // 如果通过左操作数的条件直接跳转到这里，需要设置结果为左操作数的值
//     MoveInstruction *moveLeft = new MoveInstruction(currentFunc, result, left->val);
//     node->blockInsts.addInst(moveLeft);
    
//     // 将结果值存入节点的val字段
//     node->val = result;
//     return true;
// }

/// @brief 逻辑非运算
bool IRGenerator::ir_not(ast_node * node)
{
    ast_node * operand_node = node->sons[0];
    Function * currentFunc = module->getCurrentFunction();
    
    // 处理操作数
    ast_node *operand = ir_visit_ast_node(operand_node);
    if (!operand) {
        return false;
    }
    
    // 将操作数的指令添加到当前节点
    node->blockInsts.addInst(operand->blockInsts);
    
    // 创建逻辑非指令：使用等于0的比较来实现逻辑非，直接返回i1类型结果
    BinaryInstruction *cmpInst = new BinaryInstruction(
        currentFunc, 
        IRInstOperator::IRINST_OP_EQ, 
        operand->val,
        module->newConstInt(0),
        IntegerType::getTypeBool()  // 直接返回布尔类型(i1)
    );
    
    node->blockInsts.addInst(cmpInst);
    node->val = cmpInst;
    
    return true;
}

/// @brief 简单if语句（无else分支）
bool IRGenerator::ir_if(ast_node * node)
{
    ast_node * cond_node = node->sons[0];
    ast_node * then_node = node->sons[1];
    Function * currentFunc = module->getCurrentFunction();
    
    // 创建标签
    LabelInstruction *thenLabel = createLabel();
    LabelInstruction *endLabel = createLabel();
    
    // 计算条件表达式
    ast_node *cond = ir_visit_ast_node(cond_node);
    if (!cond) {
        return false;
    }
    
    // 添加条件表达式的指令
    node->blockInsts.addInst(cond->blockInsts);
    BinaryInstruction * neqInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_NEQ,
                                                        cond->val,
                                                        module->newConstInt(0),
                                                        IntegerType::getTypeBool()); // 布尔值用整型表示
    // 条件跳转：如果条件为真，则执行then部分，否则跳到结束
    node->blockInsts.addInst(neqInst);
    CondGotoInstruction *condGoto = new CondGotoInstruction(currentFunc, neqInst, thenLabel, endLabel);
    node->blockInsts.addInst(condGoto);
    
    // then部分标签
    node->blockInsts.addInst(thenLabel);
    
    // 计算then部分
    ast_node *then = ir_visit_ast_node(then_node);
    if (!then) {
        return false;
    }
    node->blockInsts.addInst(then->blockInsts);
    
    // 结束标签
    node->blockInsts.addInst(endLabel);
    
    return true;
}

/// @brief if-else语句
bool IRGenerator::ir_if_else(ast_node * node)
{
    ast_node * cond_node = node->sons[0];
    ast_node * then_node = node->sons[1];
    ast_node * else_node = node->sons[2];
    Function * currentFunc = module->getCurrentFunction();
    
    // 创建标签
    LabelInstruction *thenLabel = createLabel();
    LabelInstruction *elseLabel = createLabel();
    LabelInstruction *endLabel = createLabel();
    
    // 计算条件表达式
    ast_node *cond = ir_visit_ast_node(cond_node);
    if (!cond) {
        return false;
    }
    
    // 添加条件表达式的指令
    node->blockInsts.addInst(cond->blockInsts);
    
    // 条件跳转：直接使用条件值进行跳转，无需额外的转换
    CondGotoInstruction *condGoto = new CondGotoInstruction(currentFunc, cond->val, thenLabel, elseLabel);
    node->blockInsts.addInst(condGoto);
    
    // then部分标签
    node->blockInsts.addInst(thenLabel);
    
    // 计算then部分
    ast_node *then = ir_visit_ast_node(then_node);
    if (!then) {
        return false;
    }
    node->blockInsts.addInst(then->blockInsts);
    
    // then部分执行完后跳转到结束
    GotoInstruction *thenGotoEnd = new GotoInstruction(currentFunc, endLabel);
    node->blockInsts.addInst(thenGotoEnd);
    
    // else部分标签
    node->blockInsts.addInst(elseLabel);
    
    // 计算else部分
    ast_node *else_part = ir_visit_ast_node(else_node);
    if (!else_part) {
        return false;
    }
    node->blockInsts.addInst(else_part->blockInsts);
    
    // 结束标签
    node->blockInsts.addInst(endLabel);
    
    return true;
}

/// @brief while循环语句
bool IRGenerator::ir_while(ast_node * node)
{
    ast_node * cond_node = node->sons[0];
    ast_node * body_node = node->sons[1];
    Function * currentFunc = module->getCurrentFunction();
    
    // 创建标签 - 使用更清晰的标签名字
    LabelInstruction *condLabel = createLabel(); // 循环开始标签（条件判断）
    LabelInstruction *bodyLabel = createLabel();  // 循环体标签
    LabelInstruction *endLabel = createLabel();   // 循环结束标签
    
    // 保存当前循环的break和continue标签
    LoopContext ctx;
    ctx.continueLabel = condLabel;  // continue应该跳到条件判断处
    ctx.breakLabel = endLabel;     // break应该跳到循环后
    loopStack.push_back(ctx);
    
    // 无条件跳转到条件判断处，确保先判断条件
    node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));
    
    // 循环开始标签，先进行条件判断
    node->blockInsts.addInst(condLabel);
    
    // 计算条件表达式
    ast_node *cond = ir_visit_ast_node(cond_node);
    if (!cond) {
        loopStack.pop_back();
        return false;
    }
    
    // 添加条件表达式的指令
    node->blockInsts.addInst(cond->blockInsts);
    
    // 条件跳转：如果条件为假，直接跳到结束标签
    CondGotoInstruction *condGoto = new CondGotoInstruction(currentFunc, cond->val, bodyLabel, endLabel);
    node->blockInsts.addInst(condGoto);
    
    // 循环体标签
    node->blockInsts.addInst(bodyLabel);
    
    // 计算循环体
    ast_node *body = ir_visit_ast_node(body_node);
    if (!body) {
        loopStack.pop_back();
        return false;
    }
    node->blockInsts.addInst(body->blockInsts);
    
    // 循环体执行完后跳回循环条件判断
    GotoInstruction *loopBack = new GotoInstruction(currentFunc, condLabel);
    node->blockInsts.addInst(loopBack);
    
    // 循环结束标签
    node->blockInsts.addInst(endLabel);
    
    // 恢复循环上下文
    loopStack.pop_back();
    
    return true;
}

/// @brief for循环语句
bool IRGenerator::ir_for(ast_node * node)
{
    Function * currentFunc = module->getCurrentFunction();
    
    // 创建标签 - 使用更清晰的标签名字
    LabelInstruction *condLabel = createLabel(); // 条件判断标签
    LabelInstruction *bodyLabel = createLabel(); // 循环体标签
    LabelInstruction *stepLabel = createLabel(); // 步进标签
    LabelInstruction *endLabel = createLabel();  // 循环结束标签
    
    // 保存当前循环的break和continue标签
    LoopContext ctx;
    ctx.continueLabel = stepLabel;  // continue应该跳到步进部分
    ctx.breakLabel = endLabel;      // break应该跳到循环结束
    loopStack.push_back(ctx);
    
    // 初始化部分（可能为空）
    if (node->sons.size() > 0 && node->sons[0] != nullptr) {
        ast_node *init = ir_visit_ast_node(node->sons[0]);
        if (init) {
            node->blockInsts.addInst(init->blockInsts);
        }
    }
    
    // 直接跳转到条件判断
    node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));
    
    // 条件判断标签
    node->blockInsts.addInst(condLabel);
    
    // 条件部分（可能为空）
    if (node->sons.size() > 1 && node->sons[1] != nullptr) {
        ast_node *cond = ir_visit_ast_node(node->sons[1]);
        if (cond) {
            node->blockInsts.addInst(cond->blockInsts);
            
            // 条件跳转：如果条件为假，则跳到循环结束
            CondGotoInstruction *condGoto = new CondGotoInstruction(currentFunc, cond->val, bodyLabel, endLabel);
            node->blockInsts.addInst(condGoto);
        } else {
            // 如果条件解析失败，清理上下文并返回
            loopStack.pop_back();
            return false;
        }
    } else {
        // 如果没有条件，则无条件进入循环体
        GotoInstruction *unconditionalGoto = new GotoInstruction(currentFunc, bodyLabel);
        node->blockInsts.addInst(unconditionalGoto);
    }
    
    // 循环体标签
    node->blockInsts.addInst(bodyLabel);
    
    // 循环体部分
    ast_node *body = nullptr;
    if (node->sons.size() > 3 && node->sons[3] != nullptr) {
        body = ir_visit_ast_node(node->sons[3]);
        if (!body) {
            loopStack.pop_back();
            return false;
        }
        node->blockInsts.addInst(body->blockInsts);
    }
    
    // 步进标签
    node->blockInsts.addInst(stepLabel);
    
    // 步进部分（可能为空）
    if (node->sons.size() > 2 && node->sons[2] != nullptr) {
        ast_node *step = ir_visit_ast_node(node->sons[2]);
        if (step) {
            node->blockInsts.addInst(step->blockInsts);
        } else {
            // 如果步进表达式解析失败
            loopStack.pop_back();
            return false;
        }
    }
    
    // 步进部分执行完后跳回条件判断
    GotoInstruction *loopBack = new GotoInstruction(currentFunc, condLabel);
    node->blockInsts.addInst(loopBack);
    
    // 循环结束标签
    node->blockInsts.addInst(endLabel);
    
    // 恢复循环上下文
    loopStack.pop_back();
    
    return true;
}

/// @brief break语句
bool IRGenerator::ir_break(ast_node * node)
{
    // 检查是否在循环内
    if (loopStack.empty()) {
        minic_log(LOG_ERROR, "第%lld行的break语句不在循环内", (long long)node->line_no);
        return false;
    }
    
    Function *currentFunc = module->getCurrentFunction();
    
    // 获取当前循环的结束标签
    LabelInstruction *breakTarget = loopStack.back().breakLabel;
    if (!breakTarget) {
        minic_log(LOG_ERROR, "第%lld行的break语句找不到对应的循环结束标签", (long long)node->line_no);
        return false;
    }
    
    // 创建无条件跳转指令，跳转到循环结束标签
    GotoInstruction *gotoBreak = new GotoInstruction(currentFunc, breakTarget);
    node->blockInsts.addInst(gotoBreak);
    
    return true;
}

/// @brief continue语句
bool IRGenerator::ir_continue(ast_node * node)
{
    // 检查是否在循环内
    if (loopStack.empty()) {
        minic_log(LOG_ERROR, "第%lld行的continue语句不在循环内", (long long)node->line_no);
        return false;
    }
    
    Function *currentFunc = module->getCurrentFunction();
    
    // 获取当前循环的继续标签
    LabelInstruction *continueTarget = loopStack.back().continueLabel;
    if (!continueTarget) {
        minic_log(LOG_ERROR, "第%lld行的continue语句找不到对应的循环继续标签", (long long)node->line_no);
        return false;
    }
    
    // 创建无条件跳转指令，跳转到循环继续标签
    GotoInstruction *gotoContinue = new GotoInstruction(currentFunc, continueTarget);
    node->blockInsts.addInst(gotoContinue);
    
    return true;
}

/// @brief 数组类型AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_array_type(ast_node* node) 
{
    // 获取基本类型
    Type* baseType = IntegerType::getTypeInt();
    
    // 收集维度信息
    std::vector<int> dimensions;
    for (auto& dimNode : node->sons) {
        // 如果维度是常量
        if (dimNode->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
            dimensions.push_back(dimNode->integer_val);
        } else {
            // 非常量维度（可能是变量或表达式）
            dimensions.push_back(10); // 默认维度
        }
    }
    
    // 将维度信息存储在节点中，供后续处理使用
    node->type = baseType;
    node->integer_val = dimensions.size();
    
    return true;
}

/// @brief 数组变量声明AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
// bool IRGenerator::ir_array_decl(ast_node* node) 
// {
//     // 处理数组类型节点
//     ast_node* typeNode = node->sons[0];
//     ast_node* typeResult = ir_visit_ast_node(typeNode);
//     if (!typeResult) {
//         return false;
//     }
    
//     // 创建适当的数组类型
//     Type* baseType = typeNode->type;
    
//     // 获取数组变量名
//     ast_node* idNode = node->sons[1];
//     std::string arrayName = idNode->name;
    
//     // 创建数组变量
//     Function* currentFunc = module->getCurrentFunction();
    
//     // 创建本地变量
//     Value* arrayVar = nullptr;
//     if (currentFunc) {
//         arrayVar = module->newVarValue(baseType, arrayName);
//     }
    
//     // 处理可能的初始化表达式
//     if (node->sons.size() > 3) {
//         // 最后一个子节点可能是初始化表达式
//         ast_node* initExpr = node->sons.back();
//         ast_node* initResult = ir_visit_ast_node(initExpr);
//         if (initResult && initResult->val) {
//             // 添加初始化表达式的计算指令
//             node->blockInsts.addInst(initResult->blockInsts);
//         }
//     }
    
//     node->val = arrayVar;
    
//     return true;
// }

// 实现数组访问节点翻译
bool IRGenerator::ir_array_access(ast_node* node) 
{
    // 处理数组变量
    ast_node* arrayNode = node->sons[0];
    ast_node* arrayResult = ir_visit_ast_node(arrayNode);
    if (!arrayResult) {
        return false;
    }
    
    // 收集索引表达式
    std::vector<Value*> indices;
    for (size_t i = 1; i < node->sons.size(); i++) {
        ast_node* indexNode = node->sons[i];
        ast_node* indexResult = ir_visit_ast_node(indexNode);
        if (!indexResult || !indexResult->val) {
            return false;
        }
        
        // 添加索引表达式的指令
        node->blockInsts.addInst(indexResult->blockInsts);
        
        indices.push_back(indexResult->val);
    }
    BinaryInstruction *t = nullptr;
    BinaryInstruction * mulInst;
    for (int i = 0; i < indices.size() - 1; i++) {
        if (t==nullptr) {
            mulInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_MUL_I,
                                                        indices[i],
                                                        module->newConstInt(arrayResult->val->getDimensions()[i+1 ]),
                                                        IntegerType::getTypeInt());
        } else {
            mulInst = new BinaryInstruction(module->getCurrentFunction(),
                                      IRInstOperator::IRINST_OP_MUL_I,
                                      t,
                                      module->newConstInt(arrayResult->val->getDimensions()[i+1]),
                                      IntegerType::getTypeInt());
            }
        node->blockInsts.addInst(mulInst);
        BinaryInstruction * addInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_ADD_I,
                                                        indices[i+1],
                                                        mulInst,
                                                        IntegerType::getTypeInt());
        // indices[i] = module->newConstInt(0);
        t=addInst;
        node->blockInsts.addInst(addInst);
    }
    BinaryInstruction * mulInst4=nullptr;
    if (t != nullptr) {
        mulInst4 = new BinaryInstruction(module->getCurrentFunction(),
                                                            IRInstOperator::IRINST_OP_MUL_I,
                                                            t,
                                                            module->newConstInt(4),
                                                            IntegerType::getTypeInt());
		node->blockInsts.addInst(mulInst4);
    }
    // 创建 int* 类型
	Type* intType = IntegerType::getTypeInt();  // 假设32位整数
	// ...existing code...
	PointerType* intPtrType = const_cast<PointerType*>(PointerType::get(intType));
// ...existing code...

    BinaryInstruction * addInst2 = new BinaryInstruction(module->getCurrentFunction(),
                                                            IRInstOperator::IRINST_OP_ADD_I,
                                                            arrayResult->val,
                                                            mulInst4,
                                                    		intPtrType);
		node->blockInsts.addInst(addInst2);

    node->val = addInst2;
    
    return true;
}

// 修复getarray内置函数处理
bool IRGenerator::processGetArrayCall(ast_node* node)
{
    // getarray(array, size) 读取数组元素
    ast_node* paramsNode = node->sons[1];
    Function* currentFunc = module->getCurrentFunction();
    
    if (paramsNode->sons.size() != 2) {
        // getarray需要两个参数：数组和大小
        return false;
    }
    
    // 处理数组参数
    ast_node* arrayParam = ir_visit_ast_node(paramsNode->sons[0]);
    if (!arrayParam || !arrayParam->val) {
        return false;
    }
    
    // 处理大小参数
    ast_node* sizeParam = ir_visit_ast_node(paramsNode->sons[1]);
    if (!sizeParam || !sizeParam->val) {
        return false;
    }
    
    // 添加参数处理指令
    node->blockInsts.addInst(arrayParam->blockInsts);
    node->blockInsts.addInst(sizeParam->blockInsts);
    
    // 为每个参数生成ARG指令
    ArgInstruction* arrayArgInst = new ArgInstruction(currentFunc, arrayParam->val);
    ArgInstruction* sizeArgInst = new ArgInstruction(currentFunc, sizeParam->val);
    node->blockInsts.addInst(arrayArgInst);
    node->blockInsts.addInst(sizeArgInst);
    
    // 记录实参数量，用于栈空间分配和寄存器参数优化
    currentFunc->realArgCountInc();
    currentFunc->realArgCountInc();
    
    // 创建参数列表
    std::vector<Value*> params;
    params.push_back(arrayParam->val);
    params.push_back(sizeParam->val);
    
    Function* getarrayFunc = module->findFunction("getarray");
    
    if (!getarrayFunc) {
        // 创建内置函数声明，不需要提供形参列表
        getarrayFunc = module->newFunction("getarray", IntegerType::getTypeInt(), {});
        
        // 手动添加形参
        FormalParam* arrayParam = new FormalParam(IntegerType::getTypeInt(), "array");
        FormalParam* sizeParam = new FormalParam(IntegerType::getTypeInt(), "size");
        getarrayFunc->getParams().push_back(arrayParam);
        getarrayFunc->getParams().push_back(sizeParam);
    }
    
    // 创建函数调用指令
    FuncCallInstruction* callInst = new FuncCallInstruction(
        currentFunc, getarrayFunc, params, IntegerType::getTypeInt()
    );
    node->blockInsts.addInst(callInst);
    node->val = callInst;
    
    // 重置参数计数器，为下一次函数调用准备
    currentFunc->realArgCountReset();
    
    return true;
}

// 修复putarray内置函数处理
bool IRGenerator::processPutArrayCall(ast_node* node)
{
    // putarray(size, array) 输出数组元素
    ast_node* paramsNode = node->sons[1];
    Function* currentFunc = module->getCurrentFunction();
    
    if (paramsNode->sons.size() != 2) {
        // putarray需要两个参数：大小和数组
        return false;
    }
    
    // 处理大小参数
    ast_node* sizeParam = ir_visit_ast_node(paramsNode->sons[0]);
    if (!sizeParam || !sizeParam->val) {
        return false;
    }
    
    // 处理数组参数
    ast_node* arrayParam = ir_visit_ast_node(paramsNode->sons[1]);
    if (!arrayParam || !arrayParam->val) {
        return false;
    }
    
    // 添加参数处理指令
    node->blockInsts.addInst(sizeParam->blockInsts);
    node->blockInsts.addInst(arrayParam->blockInsts);
    
    // 为每个参数生成ARG指令
    ArgInstruction* sizeArgInst = new ArgInstruction(currentFunc, sizeParam->val);
    ArgInstruction* arrayArgInst = new ArgInstruction(currentFunc, arrayParam->val);
    node->blockInsts.addInst(sizeArgInst);
    node->blockInsts.addInst(arrayArgInst);
    
    // 记录实参数量，用于栈空间分配和寄存器参数优化
    currentFunc->realArgCountInc();
    currentFunc->realArgCountInc();
    
    // 创建参数列表
    std::vector<Value*> params;
    params.push_back(sizeParam->val);
    params.push_back(arrayParam->val);
    
    Function* putarrayFunc = module->findFunction("putarray");
    
    if (!putarrayFunc) {
        // 创建内置函数声明，不需要提供形参列表
        putarrayFunc = module->newFunction("putarray", VoidType::getType(), {});
        
        // 手动添加形参
        FormalParam* sizeParam = new FormalParam(IntegerType::getTypeInt(), "size");
        FormalParam* arrayParam = new FormalParam(IntegerType::getTypeInt(), "array");
        putarrayFunc->getParams().push_back(sizeParam);
        putarrayFunc->getParams().push_back(arrayParam);
    }
    
    // 创建函数调用指令
    FuncCallInstruction* callInst = new FuncCallInstruction(
        currentFunc, putarrayFunc, params, VoidType::getType()
    );
    
    node->blockInsts.addInst(callInst);
    node->val = callInst;
    
    // 重置参数计数器，为下一次函数调用准备
    currentFunc->realArgCountReset();
    
    return true;
}
bool IRGenerator::ir_array_decl(ast_node* node) 
{
    // 获取数组元素类型
    Type* elementType = IntegerType::getTypeInt(); // 默认为int类型
    
    // 获取数组名
    std::string arrayName = node->sons[1]->name;
    
    // 收集维度信息
    std::vector<int> dimensions;
    for (size_t i = 2; i < node->sons.size(); i++) {
        ast_node* dimNode = node->sons[i];
        if (dimNode->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
            dimensions.push_back(dimNode->integer_val);
        } else {
            // 全局数组必须使用常量维度
            minic_log(LOG_ERROR, "全局数组必须使用常量维度");
            return false;
        }
    }
    
    // 创建数组类型
    ArrayType* arrayType = ArrayType::getType(elementType);

    // 创建全局数组变量
    Value* arrayVar = module->newVarValue(arrayType, arrayName, dimensions);
    // GlobalVariable* globalVar = module->newGlobalVariable(arrayType, arrayName, dimensions);
    
    // 存储到节点中
    node->val = arrayVar;
    
    return true;
}

// 添加全局数组声明处理
bool IRGenerator::ir_global_array_decl(ast_node* node) 
{
    // 获取数组元素类型
    Type* elementType = IntegerType::getTypeInt(); // 默认为int类型
    
    // 获取数组名
    std::string arrayName = node->sons[1]->name;
    
    // 收集维度信息
    std::vector<int> dimensions;
    for (size_t i = 2; i < node->sons.size(); i++) {
        ast_node* dimNode = node->sons[i];
        if (dimNode->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
            dimensions.push_back(dimNode->integer_val);
        } else {
            // 全局数组必须使用常量维度
            minic_log(LOG_ERROR, "全局数组必须使用常量维度");
            return false;
        }
    }
    
    // 创建数组类型
    ArrayType* arrayType = ArrayType::getType(elementType);
    
    // 创建全局数组变量
    GlobalVariable* globalVar = module->newGlobalVariable(arrayType, arrayName, dimensions);
    
    // 存储到节点中
    node->val = globalVar;
    
    return true;
}
