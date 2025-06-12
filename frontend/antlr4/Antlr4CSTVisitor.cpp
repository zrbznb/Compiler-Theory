///
/// @file Antlr4CSTVisitor.cpp
/// @brief Antlr4的具体语法树的遍历产生AST
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

#include <string>

#include "Antlr4CSTVisitor.h"
#include "AST.h"
#include "AttrType.h"

#define Instanceof(res, type, var) auto res = dynamic_cast<type>(var)

/// @brief 构造函数
MiniCCSTVisitor::MiniCCSTVisitor()
{}

/// @brief 析构函数
MiniCCSTVisitor::~MiniCCSTVisitor()
{}

/// @brief 遍历CST产生AST
/// @param root CST语法树的根结点
/// @return AST的根节点
ast_node * MiniCCSTVisitor::run(MiniCParser::CompileUnitContext * root)
{
    return std::any_cast<ast_node *>(visitCompileUnit(root));
}

/// @brief 非终结运算符compileUnit的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitCompileUnit(MiniCParser::CompileUnitContext * ctx)
{
    // compileUnit: (funcDef | varDecl)* EOF

    // 请注意这里必须先遍历全局变量后遍历函数。肯定可以确保全局变量先声明后使用的规则，但有些情况却不能检查出。
    // 事实上可能函数A后全局变量B后函数C，这时在函数A中是不能使用变量B的，需要报语义错误，但目前的处理不会。
    // 因此在进行语义检查时，可能追加检查行号和列号，如果函数的行号/列号在全局变量的行号/列号的前面则需要报语义错误
    // TODO 请追加实现。

    ast_node * temp_node;
    ast_node * compileUnitNode = create_contain_node(ast_operator_type::AST_OP_COMPILE_UNIT);

    // 可能多个变量，因此必须循环遍历
    for (auto varCtx: ctx->varDecl()) {

        // 变量函数定义
        temp_node = std::any_cast<ast_node *>(visitVarDecl(varCtx));
        (void) compileUnitNode->insert_son_node(temp_node);
    }

    // 可能有多个函数，因此必须循环遍历
    for (auto funcCtx: ctx->funcDef()) {

        // 变量函数定义
        temp_node = std::any_cast<ast_node *>(visitFuncDef(funcCtx));
        (void) compileUnitNode->insert_son_node(temp_node);
    }

    return compileUnitNode;
}

/// @brief 非终结运算符funcDef的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitFuncDef(MiniCParser::FuncDefContext * ctx)
{
    // 识别的文法产生式：funcDef : returnType T_ID T_L_PAREN formalParams? T_R_PAREN block;

    // 函数返回类型
    type_attr funcReturnType = std::any_cast<type_attr>(visitReturnType(ctx->returnType()));

    // 创建函数名的标识符终结符节点
    char * id = strdup(ctx->T_ID()->getText().c_str());
    var_id_attr funcId{id, (int64_t) ctx->T_ID()->getSymbol()->getLine()};

    // 形参结点
    ast_node * formalParamsNode = nullptr;
    if (ctx->formalParams()) {
        formalParamsNode = std::any_cast<ast_node *>(visitFormalParams(ctx->formalParams()));
    } else {
        // 创建空参数列表节点
        formalParamsNode = new ast_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS);
    }

    // 遍历block结点创建函数体节点
    auto blockNode = std::any_cast<ast_node *>(visitBlock(ctx->block()));

    // 创建函数定义的节点
    return create_func_def(funcReturnType, funcId, blockNode, formalParamsNode);
}

/// @brief 访问返回类型
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitReturnType(MiniCParser::ReturnTypeContext* ctx) 
{
    type_attr typeAttr;
    typeAttr.lineno = -1;
    
    if (ctx->T_INT()) {
        typeAttr.type = BasicType::TYPE_INT;
        typeAttr.lineno = (int64_t) ctx->T_INT()->getSymbol()->getLine();
    } else if (ctx->T_VOID()) {
        typeAttr.type = BasicType::TYPE_VOID;
        typeAttr.lineno = (int64_t) ctx->T_VOID()->getSymbol()->getLine();
    }
    
    return typeAttr;
}

/// @brief 访问形参列表
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitFormalParams(MiniCParser::FormalParamsContext* ctx) 
{
    // 创建形参列表节点
    ast_node* paramsNode = new ast_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS);
    
    // 遍历每个形参
    for (auto paramCtx : ctx->formalParam()) {
        // 获取形参节点
        ast_node* paramNode = std::any_cast<ast_node*>(visitFormalParam(paramCtx));
        
        // 添加到形参列表
        paramsNode->insert_son_node(paramNode);
    }
    
    return paramsNode;
}

/// @brief 访问单个形参
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitFormalParam(MiniCParser::FormalParamContext* ctx) 
{
    // 检查是否是数组形参
    if (ctx->T_L_BRACKET().size() > 0) {
        return processArrayFormalParam(ctx);
    }
    
    // 获取类型
    type_attr typeAttr = std::any_cast<type_attr>(visitBasicType(ctx->basicType()));
    
    // 获取参数名
    std::string paramName = ctx->T_ID()->getText();
    int64_t lineNo = (int64_t) ctx->T_ID()->getSymbol()->getLine();
    
    // 创建形参节点
    ast_node* paramNode = create_func_formal_param(typeAttr, paramName, lineNo);
    
    return paramNode;
}

/// @brief 处理数组类型的形参定义
/// @param ctx CST上下文
/// @return 形参节点
ast_node* MiniCCSTVisitor::processArrayFormalParam(MiniCParser::FormalParamContext* ctx)
{
    // 获取基本类型
    type_attr typeAttr = std::any_cast<type_attr>(visitBasicType(ctx->basicType()));
    
    // 获取参数名
    std::string paramName = ctx->T_ID()->getText();
    int64_t lineNo = (int64_t) ctx->T_ID()->getSymbol()->getLine();
    
    // 处理维度信息
    // 注意：作为形参的数组，第一维要设为0
    std::vector<int> dimensions;
    dimensions.push_back(0); // 第一维为0
    
    // 处理后续维度，从第二个开始
    for (size_t i = 1; i < ctx->T_L_BRACKET().size(); i++) {
        // 确保有对应的数字字面量
        if (i-1 < ctx->T_DIGIT().size()) {
            int dim = std::stoi(ctx->T_DIGIT(i-1)->getText());
            dimensions.push_back(dim);
        }
    }
    
    // 创建数组类型节点
    ast_node* arrayTypeNode = create_array_type_node(typeAttr.type, dimensions);
    
    // 创建ID节点
    ast_node* idNode = ast_node::New(paramName, lineNo);
    
    // 创建形参节点
    ast_node* paramNode = new ast_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAM);
    paramNode->type = arrayTypeNode->type;
    paramNode->line_no = lineNo;
    
    // 添加类型和名字作为孩子节点
    (void) paramNode->insert_son_node(arrayTypeNode);
    (void) paramNode->insert_son_node(idNode);
    
    return paramNode;
}

/// @brief 非终结运算符VarDef的分析
std::any MiniCCSTVisitor::visitVarDef(MiniCParser::VarDefContext* ctx) 
{
    // 变量名
    auto varId = ctx->T_ID()->getText();

    // 获取行号
    int64_t lineNo = (int64_t) ctx->T_ID()->getSymbol()->getLine();
    
    // 检查是否是数组变量定义
    if (!ctx->T_L_BRACKET().empty()) {
        // 不再创建未使用的idNode
        
        // 如果有下标表达式，收集它们
        std::vector<ast_node*> dimExprs;
        for (auto exprCtx : ctx->expr()) {
            // 第一个expr可能是初始化表达式，需要检查
            if (ctx->T_ASSIGN() != nullptr && exprCtx == ctx->expr().back() && 
                ctx->expr().size() > ctx->T_L_BRACKET().size()) {
                continue; // 跳过初始化表达式
            }
            
            ast_node* dimExpr = std::any_cast<ast_node*>(visitExpr(exprCtx));
            dimExprs.push_back(dimExpr);
        }
        
        // 检查是否有初始化表达式
        ast_node* initExpr = nullptr;
        if (ctx->T_ASSIGN() != nullptr) {
            // 确保这是初始化表达式而不是数组维度
            // 修复条件表达式，避免无效的比较
            if (!ctx->expr().empty() && ctx->T_L_BRACKET().size() < ctx->expr().size()) {
                initExpr = std::any_cast<ast_node*>(visitExpr(ctx->expr().back()));
            }
        }
        
        // 创建一个临时节点存储所有信息，便于外部处理
        ast_node* tempNode = new ast_node(ast_operator_type::AST_OP_LEAF_VAR_ID);
        tempNode->name = varId;
        tempNode->line_no = lineNo;
        
        // 存储维度表达式和初始化表达式
        for (auto dimExpr : dimExprs) {
            tempNode->insert_son_node(dimExpr);
        }
        
        if (initExpr) {
            // 特殊标记，表示最后一个子节点是初始化表达式
            tempNode->insert_son_node(initExpr);
        }
        
        return tempNode;
    }
    
    // 创建变量标识符节点
    ast_node* idNode = ast_node::New(varId, lineNo);
    
    // 检查是否有赋值表达式
    if (ctx->T_ASSIGN() != nullptr && !ctx->expr().empty()) {
        // 有初始化表达式，递归解析表达式
        ast_node* initExpr = std::any_cast<ast_node*>(visitExpr(ctx->expr(0)));
        
        // 创建带初始值的变量定义节点
        idNode->insert_son_node(initExpr);
    }

    return idNode;
}

/// @brief 处理数组变量定义
/// @param ctx CST上下文
/// @param typeAttr 类型属性
/// @return 数组变量定义节点
ast_node* MiniCCSTVisitor::processArrayVarDef(MiniCParser::VarDefContext* ctx, type_attr& typeAttr)
{
    // 获取变量名
    std::string varId = ctx->T_ID()->getText();
    int64_t lineNo = (int64_t) ctx->T_ID()->getSymbol()->getLine();
    
    // 创建ID节点 - 这里修复未使用变量的问题
    ast_node* idNode = ast_node::New(varId, lineNo);
    
    // 处理数组维度表达式
    std::vector<ast_node*> dimExprs;
    std::vector<int> dimSizes; // 用于创建类型
    
    // 计算实际维度表达式的数量及其索引
    int dimExprCount = ctx->T_L_BRACKET().size();
    
    // 收集所有维度表达式 - 修复条件表达式错误
    for (size_t i = 0; i < dimExprCount && i < ctx->expr().size(); i++) {
        // 获取表达式的起始位置
        size_t exprStart = ctx->expr(i)->getStart()->getStartIndex();
        size_t bracketStart = ctx->T_L_BRACKET(i)->getSymbol()->getStartIndex();
        
        // 如果表达式在方括号之后，且不是初始化表达式
        if (exprStart > bracketStart) {
            // 仅当表达式不是最后一个或没有赋值符号时，才视为维度表达式
            bool isInitExpr = (i == ctx->expr().size()-1 && ctx->T_ASSIGN() != nullptr);
            
            if (!isInitExpr) {
                ast_node* dimExpr = std::any_cast<ast_node*>(visitExpr(ctx->expr(i)));
                dimExprs.push_back(dimExpr);
                
                // 如果维度是常量表达式，提取尺寸
                if (dimExpr->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
                    dimSizes.push_back(dimExpr->integer_val);
                } else {
                    // 非常量表达式，使用默认尺寸
                    dimSizes.push_back(10); // 默认尺寸
                }
            }
        }
    }
    
    // 创建数组类型节点
    ast_node* arrayTypeNode = create_array_type_node(typeAttr.type, dimSizes);
    
    // 处理可能的初始化表达式
    ast_node* initExpr = nullptr;
    if (ctx->T_ASSIGN() != nullptr && ctx->expr().size() > 0) {
        // 获取最后一个表达式
        size_t lastIndex = ctx->expr().size() - 1;
        // 如果最后一个表达式在赋值符号之后，则为初始化表达式
        if (ctx->expr(lastIndex)->getStart()->getStartIndex() > 
            ctx->T_ASSIGN()->getSymbol()->getStartIndex()) {
            initExpr = std::any_cast<ast_node*>(visitExpr(ctx->expr(lastIndex)));
        }
    }
    
    // 创建数组声明节点
    return create_array_decl_node(arrayTypeNode, idNode, dimExprs, initExpr);
}

/// @brief 非终结符VarDecl的分析
std::any MiniCCSTVisitor::visitVarDecl(MiniCParser::VarDeclContext* ctx)
{
    // varDecl: basicType varDef (T_COMMA varDef)* T_SEMICOLON;

    // 声明语句节点
    ast_node* stmt_node = create_contain_node(ast_operator_type::AST_OP_DECL_STMT);

    // 类型节点
    type_attr typeAttr = std::any_cast<type_attr>(visitBasicType(ctx->basicType()));

    for (auto& varCtx: ctx->varDef()) {
        ast_node* declNode = nullptr;
        
        // 判断是否为数组变量定义
        if (!varCtx->T_L_BRACKET().empty()) {
            // 数组变量定义
            declNode = processArrayVarDef(varCtx, typeAttr);
        } else {
            // 普通变量定义 - 保持原有逻辑
            ast_node* id_node = std::any_cast<ast_node*>(visitVarDef(varCtx));
            ast_node* value_node = nullptr;
            
            if(id_node->sons.size() > 0) {
                // 如果有初始值表达式，则将其作为子节点
                value_node = id_node->sons[0];
            }

            // 创建类型节点
            ast_node* type_node = create_type_node(typeAttr);

            if (value_node) {
                declNode = ast_node::New(ast_operator_type::AST_OP_VAR_DECL, type_node, id_node, value_node, nullptr);
            } else {
                // 创建变量定义节点
                declNode = ast_node::New(ast_operator_type::AST_OP_VAR_DECL, type_node, id_node, nullptr);
            }
        }

        // 插入到变量声明语句
        (void)stmt_node->insert_son_node(declNode);
    }

    return stmt_node;
}

/// @brief 非终结符LVal的分析
std::any MiniCCSTVisitor::visitLVal(MiniCParser::LValContext* ctx)
{
    // 识别文法产生式：lVal: T_ID (T_L_BRACKET expr T_R_BRACKET)*;
    
    // 如果有下标访问，则是数组访问
    if (!ctx->T_L_BRACKET().empty()) {
        // 获取数组变量名
        std::string arrayName = ctx->T_ID()->getText();
        int64_t lineNo = (int64_t) ctx->T_ID()->getSymbol()->getLine();
        
        // 创建数组变量节点
        ast_node* arrayNode = ast_node::New(arrayName, lineNo);
        
        // 处理所有索引表达式
        std::vector<ast_node*> indexNodes;
        for (auto exprCtx : ctx->expr()) {
            ast_node* indexNode = std::any_cast<ast_node*>(visitExpr(exprCtx));
            indexNodes.push_back(indexNode);
        }
        
        // 创建数组访问节点
        return create_array_access_node(arrayNode, indexNodes);
    }
    
    // 普通变量访问
    // 获取ID的名字
    auto varId = ctx->T_ID()->getText();

    // 获取行号
    int64_t lineNo = (int64_t) ctx->T_ID()->getSymbol()->getLine();

    return ast_node::New(varId, lineNo);
}

/// @brief 处理break语句节点
/// @param ctx 上下文
/// @return 语义值
///
std::any MiniCCSTVisitor::visitBreakStatement(MiniCParser::BreakStatementContext * ctx)
{
    // 获取行号
    uint32_t lineno = ctx->T_BREAK()->getSymbol()->getLine();
    
    // 创建break节点 - 修改为正确的创建方式
    ast_node *breakNode = new ast_node(ast_operator_type::AST_OP_BREAK);
    breakNode->line_no = lineno;  // 设置行号
    
    return breakNode;
}

///
/// @brief 处理continue语句节点
/// @param ctx 上下文
/// @return 语义值
///
std::any MiniCCSTVisitor::visitContinueStatement(MiniCParser::ContinueStatementContext * ctx)
{
    // 获取行号
    uint32_t lineno = ctx->T_CONTINUE()->getSymbol()->getLine();
    
    // 创建continue节点 - 使用正确的创建方式
    ast_node *continueNode = new ast_node(ast_operator_type::AST_OP_CONTINUE);
    continueNode->line_no = lineno;  // 设置行号
    
    return continueNode;
}

std::any MiniCCSTVisitor::visitIfStatement(MiniCParser::IfStatementContext *ctx) 
{
    // 识别文法产生式：ifStatement: T_IF T_L_PAREN expr T_R_PAREN statement (T_ELSE statement)?
    
    // 条件表达式节点
    auto condExpr = std::any_cast<ast_node *>(visitExpr(ctx->expr()));
    
    // then分支语句
    auto thenStmt = std::any_cast<ast_node *>(visit(ctx->statement(0)));
    
    // 创建if语句节点
    ast_node *ifNode;
    
    // 判断是否有else分支
    if (ctx->T_ELSE()) {
        // 有else分支
        auto elseStmt = std::any_cast<ast_node *>(visit(ctx->statement(1)));
        
        // 创建带else分支的if节点
        ifNode = ast_node::New(ast_operator_type::AST_OP_IF_ELSE, condExpr, thenStmt, elseStmt, nullptr);
    } else {
        // 没有else分支
        ifNode = ast_node::New(ast_operator_type::AST_OP_IF, condExpr, thenStmt, nullptr);
    }
    
    return ifNode;
}

std::any MiniCCSTVisitor::visitWhileStatement(MiniCParser::WhileStatementContext *ctx) 
{
    // 识别文法产生式：whileStatement: T_WHILE T_L_PAREN expr T_R_PAREN statement
    
    // 条件表达式节点
    auto condExpr = std::any_cast<ast_node *>(visitExpr(ctx->expr()));
    
    // 循环体语句
    auto bodyStmt = std::any_cast<ast_node *>(visit(ctx->statement()));
    
    // 创建while语句节点
    auto whileNode = ast_node::New(ast_operator_type::AST_OP_WHILE, condExpr, bodyStmt, nullptr);
    
    return whileNode;
}

std::any MiniCCSTVisitor::visitForStatement(MiniCParser::ForStatementContext *ctx) 
{
    // 识别文法产生式：forStatement: T_FOR T_L_PAREN (expr | varDecl)? T_SEMICOLON expr? T_SEMICOLON expr? T_R_PAREN statement
    
    // 初始化语句/表达式节点（可能为空）
    ast_node *initNode = nullptr;
    if (ctx->expr().size() > 0 && ctx->expr(0)->getStart()->getStartIndex() < ctx->T_SEMICOLON(0)->getSymbol()->getStartIndex()) {
        initNode = std::any_cast<ast_node *>(visitExpr(ctx->expr(0)));
    } else if (ctx->varDecl()) {
        initNode = std::any_cast<ast_node *>(visitVarDecl(ctx->varDecl()));
    }
    
    // 条件表达式节点（可能为空）
    ast_node *condNode = nullptr;
    int condIndex = 0;
    if (initNode && ctx->expr().size() > 0 && ctx->expr(0)->getStart()->getStartIndex() < ctx->T_SEMICOLON(0)->getSymbol()->getStartIndex()) {
        condIndex = 1;
    }
    
    if (ctx->expr().size() > condIndex && 
        ctx->expr(condIndex)->getStart()->getStartIndex() > ctx->T_SEMICOLON(0)->getSymbol()->getStartIndex() && 
        ctx->expr(condIndex)->getStart()->getStartIndex() < ctx->T_SEMICOLON(1)->getSymbol()->getStartIndex()) {
        condNode = std::any_cast<ast_node *>(visitExpr(ctx->expr(condIndex)));
    }
    
    // 步进表达式节点（可能为空）
    ast_node *stepNode = nullptr;
    int stepIndex = condIndex + (condNode ? 1 : 0);
    
    if (ctx->expr().size() > stepIndex && 
        ctx->expr(stepIndex)->getStart()->getStartIndex() > ctx->T_SEMICOLON(1)->getSymbol()->getStartIndex()) {
        stepNode = std::any_cast<ast_node *>(visitExpr(ctx->expr(stepIndex)));
    }
    
    // 循环体语句
    auto bodyStmt = std::any_cast<ast_node *>(visit(ctx->statement()));
    
    // 创建for语句节点
    ast_node *forNode;
    if (initNode && condNode && stepNode) {
        forNode = ast_node::New(ast_operator_type::AST_OP_FOR, initNode, condNode, stepNode, bodyStmt, nullptr);
    } else if (initNode && condNode) {
        forNode = ast_node::New(ast_operator_type::AST_OP_FOR, initNode, condNode, nullptr);
        forNode->insert_son_node(bodyStmt);
    } else if (initNode && stepNode) {
        forNode = ast_node::New(ast_operator_type::AST_OP_FOR, initNode, nullptr, stepNode, bodyStmt, nullptr);
    } else if (condNode && stepNode) {
        forNode = ast_node::New(ast_operator_type::AST_OP_FOR, nullptr, condNode, stepNode, bodyStmt, nullptr);
    } else if (initNode) {
        forNode = ast_node::New(ast_operator_type::AST_OP_FOR, initNode, nullptr, nullptr);
        forNode->insert_son_node(bodyStmt);
    } else if (condNode) {
        forNode = ast_node::New(ast_operator_type::AST_OP_FOR, nullptr, condNode, nullptr);
        forNode->insert_son_node(bodyStmt);
    } else if (stepNode) {
        forNode = ast_node::New(ast_operator_type::AST_OP_FOR, nullptr, nullptr, stepNode);
        forNode->insert_son_node(bodyStmt);
    } else {
        // 无条件循环
        forNode = ast_node::New(ast_operator_type::AST_OP_FOR, nullptr, nullptr, nullptr);
        forNode->insert_son_node(bodyStmt);
    }
    
    return forNode;
}

std::any MiniCCSTVisitor::visitAddExp(MiniCParser::AddExpContext * ctx)
{
    // 识别的文法产生式：addExp : mulExp (addOp mulExp)*;

    if (ctx->addOp().empty()) {
        // 没有addOp运算符，则说明闭包识别为0，只识别了第一个非终结符mulExp
        return visitMulExp(ctx->mulExp()[0]);
    }

    ast_node *left, *right;

    // 存在addOp运算符
    auto opsCtxVec = ctx->addOp();

    // 有操作符，肯定会进循环，使得right设置正确的值
    for (int k = 0; k < (int) opsCtxVec.size(); k++) {
        // 获取运算符
        ast_operator_type op = std::any_cast<ast_operator_type>(visitAddOp(opsCtxVec[k]));

        if (k == 0) {
            // 左操作数
            left = std::any_cast<ast_node *>(visitMulExp(ctx->mulExp()[k]));
        }

        // 右操作数
        right = std::any_cast<ast_node *>(visitMulExp(ctx->mulExp()[k + 1]));

        // 新建结点作为下一个运算符的左操作符
        left = ast_node::New(op, left, right, nullptr);
    }

    return left;
}

std::any MiniCCSTVisitor::visitAddOp(MiniCParser::AddOpContext * ctx)
{
    // 识别的文法产生式：addOp : T_ADD | T_SUB

    if (ctx->T_ADD()) {
        return ast_operator_type::AST_OP_ADD;
    } else {
        return ast_operator_type::AST_OP_SUB;
    }
}

std::any MiniCCSTVisitor::visitMulExp(MiniCParser::MulExpContext * ctx)
{
    // 识别的文法产生式：mulExp : unaryExp (mulOp unaryExp)*;

    if (ctx->mulOp().empty()) {
        // 没有mulOp运算符，则说明闭包识别为0，只解析第一个unaryExp
        // 注意这里改为使用访问器模式，让ANTLR决定调用哪个具体的unaryExp访问器
        return visit(ctx->unaryExp(0));
    }

    ast_node *left, *right;

    // 存在mulOp运算符
    auto opsCtxVec = ctx->mulOp();

    // 有操作符，肯定会进循环，使得right设置正确的值
    for (int k = 0; k < (int) opsCtxVec.size(); k++) {
        // 获取运算符
        ast_operator_type op = std::any_cast<ast_operator_type>(visitMulOp(opsCtxVec[k]));

        if (k == 0) {
            // 左操作数，使用visit模式让ANTLR自动选择合适的访问器
            left = std::any_cast<ast_node *>(visit(ctx->unaryExp(k)));
        }

        // 右操作数，使用visit模式让ANTLR自动选择合适的访问器
        right = std::any_cast<ast_node *>(visit(ctx->unaryExp(k + 1)));

        // 新建结点作为下一个运算符的左操作符
        left = ast_node::New(op, left, right, nullptr);
    }

    return left;
}

std::any MiniCCSTVisitor::visitMulOp(MiniCParser::MulOpContext * ctx)
{
    // 识别的文法产生式：mulOp : T_MUL | T_DIV | T_MOD

    if (ctx->T_MUL()) {
        return ast_operator_type::AST_OP_MUL;
    } else if (ctx->T_DIV()) {
        return ast_operator_type::AST_OP_DIV;
    } else {
        return ast_operator_type::AST_OP_MOD;
    }
}

std::any MiniCCSTVisitor::visitPrimaryUnaryExp(MiniCParser::PrimaryUnaryExpContext *ctx) 
{
    return visitPrimaryExp(ctx->primaryExp());
}

std::any MiniCCSTVisitor::visitNegativeUnaryExp(MiniCParser::NegativeUnaryExpContext *ctx) 
{
    // 获取操作数
    auto operand = std::any_cast<ast_node *>(visit(ctx->unaryExp()));
    
    // 创建一个表示负数的AST节点
    // 如果操作数是整数字面量，可以直接修改值
    if (operand->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        // 直接修改整数字面量的值为负数
        operand->integer_val = -(int32_t)operand->integer_val;
        return operand;
    } else {
        // 创建一个一元负号运算节点
        return ast_node::New(ast_operator_type::AST_OP_SUB, 
                            ast_node::New(digit_int_attr{0, operand->line_no}), 
                            operand, 
                            nullptr);
    }
}

std::any MiniCCSTVisitor::visitFuncCallUnaryExp(MiniCParser::FuncCallUnaryExpContext *ctx) 
{
    // 创建函数调用名终结符节点
    ast_node * funcname_node = ast_node::New(ctx->T_ID()->getText(), 
                                           (int64_t) ctx->T_ID()->getSymbol()->getLine());

    // 实参列表
    ast_node * paramListNode = nullptr;

    // 函数调用
    if (ctx->realParamList()) {
        // 有参数
        paramListNode = std::any_cast<ast_node *>(visitRealParamList(ctx->realParamList()));
    } else {
        // 没有参数，创建空的参数列表节点
        paramListNode = create_contain_node(ast_operator_type::AST_OP_FUNC_REAL_PARAMS);
    }

    // 创建函数调用节点，其孩子为被调用函数名和实参
    return create_func_call(funcname_node, paramListNode);
}

std::any MiniCCSTVisitor::visitPrimaryExp(MiniCParser::PrimaryExpContext * ctx)
{
    // 识别文法产生式 primaryExp: T_L_PAREN expr T_R_PAREN | T_DIGIT | lVal;

    ast_node * node = nullptr;

    if (ctx->T_DIGIT()) {
        // 无符号整型字面量
        std::string digitText = ctx->T_DIGIT()->getText();
        uint32_t val;
        
        // 处理不同进制的数字
        if (digitText.size() >= 2 && digitText[0] == '0') {
            if (digitText.size() >= 3 && (digitText[1] == 'x' || digitText[1] == 'X')) {
                // 十六进制
                val = (uint32_t) stoull(digitText, nullptr, 16);
            } else {
                // 八进制
                val = (uint32_t) stoull(digitText, nullptr, 8);
            }
        } else {
            // 十进制
            val = (uint32_t) stoull(digitText, nullptr, 10);
        }
        
        int64_t lineNo = (int64_t) ctx->T_DIGIT()->getSymbol()->getLine();
        node = ast_node::New(digit_int_attr{val, lineNo});
    } else if (ctx->lVal()) {
        // 具有左值的表达式
        // 识别 primaryExp: lVal
        node = std::any_cast<ast_node *>(visitLVal(ctx->lVal()));
    } else if (ctx->expr()) {
        // 带有括号的表达式
        // primaryExp: T_L_PAREN expr T_R_PAREN
        node = std::any_cast<ast_node *>(visitExpr(ctx->expr()));
    }

    return node;
}

/// @brief 非终结运算符statement中的assignStatement的遍历
std::any MiniCCSTVisitor::visitAssignStatement(MiniCParser::AssignStatementContext* ctx)
{
    // 识别文法产生式：assignStatement: lVal T_ASSIGN expr T_SEMICOLON

    // 赋值左侧左值Lval遍历产生节点
    auto lvalNode = std::any_cast<ast_node*>(visitLVal(ctx->lVal()));

    // 赋值右侧expr遍历
    auto exprNode = std::any_cast<ast_node*>(visitExpr(ctx->expr()));

    // 创建一个AST_OP_ASSIGN类型的中间节点，孩子为Lval和Expr
    return ast_node::New(ast_operator_type::AST_OP_ASSIGN, lvalNode, exprNode, nullptr);
}

std::any MiniCCSTVisitor::visitBlockStatement(MiniCParser::BlockStatementContext * ctx)
{
    // 识别文法产生式 blockStatement: block

    return visitBlock(ctx->block());
}

/// @brief 访问block节点
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitBlock(MiniCParser::BlockContext* ctx) 
{
    // 识别的文法产生式：block: T_L_BRACE blockItemList? T_R_BRACE;
    
    // 创建block节点
    ast_node* blockNode = new ast_node(ast_operator_type::AST_OP_BLOCK);
    
    // 如果有blockItemList，处理它
    if (ctx->blockItemList()) {
        ast_node* blockItemListNode = std::any_cast<ast_node*>(visitBlockItemList(ctx->blockItemList()));
        
        // 将blockItemList的所有子节点添加到block节点
        for (auto child : blockItemListNode->sons) {
            blockNode->insert_son_node(child);
        }
    }
    
    return blockNode;
}

/// @brief 访问blockItemList节点
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitBlockItemList(MiniCParser::BlockItemListContext* ctx) 
{
    // 识别的文法产生式：blockItemList: blockItem+;
    
    // 创建临时容器节点
    ast_node* listNode = new ast_node(ast_operator_type::AST_OP_BLOCK);
    
    // 处理所有blockItem
    for (auto itemCtx : ctx->blockItem()) {
        ast_node* itemNode = std::any_cast<ast_node*>(visitBlockItem(itemCtx));
        
        // 只有当itemNode不为nullptr时才添加
        if (itemNode) {
            listNode->insert_son_node(itemNode);
        }
    }
    
    return listNode;
}

/// @brief 访问blockItem节点
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitBlockItem(MiniCParser::BlockItemContext* ctx) 
{
    // 识别的文法产生式：blockItem: statement | varDecl;
    
    if (ctx->statement()) {
        return visit(ctx->statement());
    } else if (ctx->varDecl()) {
        return visitVarDecl(ctx->varDecl());
    }
    
    // 如果都不是，返回nullptr
    return nullptr;
}

/// @brief 访问expr节点
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitExpr(MiniCParser::ExprContext* ctx) 
{
    // 识别文法产生式：expr: logicOrExp;
    
    // 直接转发到logicOrExp
    return visitLogicOrExp(ctx->logicOrExp());
}

/// @brief 访问基本类型
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitBasicType(MiniCParser::BasicTypeContext* ctx) 
{
    type_attr typeAttr;
    typeAttr.lineno = -1;
    
    if (ctx->T_INT()) {
        typeAttr.type = BasicType::TYPE_INT;
        typeAttr.lineno = (int64_t) ctx->T_INT()->getSymbol()->getLine();
    } else {
        // 目前默认为INT，后续可扩展其他类型
        typeAttr.type = BasicType::TYPE_INT;
    }
    
    return typeAttr;
}

/// @brief 访问return语句
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitReturnStatement(MiniCParser::ReturnStatementContext* ctx) 
{
    // 获取返回值表达式
    ast_node* exprNode = std::any_cast<ast_node*>(visitExpr(ctx->expr()));
    
    // 创建return语句节点
    ast_node* returnNode = new ast_node(ast_operator_type::AST_OP_RETURN);
    
    // 添加返回值表达式作为子节点
    returnNode->insert_son_node(exprNode);
    
    return returnNode;
}

/// @brief 访问表达式语句
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitExpressionStatement(MiniCParser::ExpressionStatementContext* ctx) 
{
    // 如果有表达式，则访问表达式
    if (ctx->expr()) {
        return visitExpr(ctx->expr());
    }
    
    // 否则返回空的语句块
    return new ast_node(ast_operator_type::AST_OP_BLOCK);
}

/// @brief 访问逻辑或表达式
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitLogicOrExp(MiniCParser::LogicOrExpContext* ctx) 
{
    // 如果只有一个逻辑与表达式，直接返回
    if (ctx->T_OR().empty()) {
        return visitLogicAndExp(ctx->logicAndExp(0));
    }
    
    // 存在OR运算符，则创建OR节点
    ast_node* left = std::any_cast<ast_node*>(visitLogicAndExp(ctx->logicAndExp(0)));
    
    for (size_t i = 0; i < ctx->T_OR().size(); i++) {
        ast_node* right = std::any_cast<ast_node*>(visitLogicAndExp(ctx->logicAndExp(i + 1)));
        left = ast_node::New(ast_operator_type::AST_OP_OR, left, right, nullptr);
    }
    
    return left;
}

/// @brief 访问逻辑与表达式
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitLogicAndExp(MiniCParser::LogicAndExpContext* ctx) 
{
    // 如果只有一个相等性表达式，直接返回
    if (ctx->T_AND().empty()) {
        return visitEqualityExp(ctx->equalityExp(0));
    }
    
    // 存在AND运算符，则创建AND节点
    ast_node* left = std::any_cast<ast_node*>(visitEqualityExp(ctx->equalityExp(0)));
    
    for (size_t i = 0; i < ctx->T_AND().size(); i++) {
        ast_node* right = std::any_cast<ast_node*>(visitEqualityExp(ctx->equalityExp(i + 1)));
        left = ast_node::New(ast_operator_type::AST_OP_AND, left, right, nullptr);
    }
    
    return left;
}

/// @brief 访问相等性表达式
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitEqualityExp(MiniCParser::EqualityExpContext* ctx) 
{
    // 如果只有一个关系表达式，直接返回
    if (ctx->equalityOp().empty()) {
        return visitRelationalExp(ctx->relationalExp(0));
    }
    
    // 存在相等性运算符，则创建相应节点
    ast_node* left = std::any_cast<ast_node*>(visitRelationalExp(ctx->relationalExp(0)));
    
    for (size_t i = 0; i < ctx->equalityOp().size(); i++) {
        ast_operator_type op = std::any_cast<ast_operator_type>(visitEqualityOp(ctx->equalityOp(i)));
        ast_node* right = std::any_cast<ast_node*>(visitRelationalExp(ctx->relationalExp(i + 1)));
        left = ast_node::New(op, left, right, nullptr);
    }
    
    return left;
}

/// @brief 访问相等性运算符
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitEqualityOp(MiniCParser::EqualityOpContext* ctx) 
{
    if (ctx->T_EQ()) {
        return ast_operator_type::AST_OP_EQ;
    } else if (ctx->T_NEQ()) {
        return ast_operator_type::AST_OP_NEQ;
    }
    
    // 默认返回等于运算符
    return ast_operator_type::AST_OP_EQ;
}

/// @brief 访问关系表达式
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitRelationalExp(MiniCParser::RelationalExpContext* ctx) 
{
    // 如果只有一个加法表达式，直接返回
    if (ctx->relationalOp().empty()) {
        return visitAddExp(ctx->addExp(0));
    }
    
    // 存在关系运算符，则创建相应节点
    ast_node* left = std::any_cast<ast_node*>(visitAddExp(ctx->addExp(0)));
    
    for (size_t i = 0; i < ctx->relationalOp().size(); i++) {
        ast_operator_type op = std::any_cast<ast_operator_type>(visitRelationalOp(ctx->relationalOp(i)));
        ast_node* right = std::any_cast<ast_node*>(visitAddExp(ctx->addExp(i + 1)));
        left = ast_node::New(op, left, right, nullptr);
    }
    
    return left;
}

/// @brief 访问关系运算符
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitRelationalOp(MiniCParser::RelationalOpContext* ctx) 
{
    if (ctx->T_LT()) {
        return ast_operator_type::AST_OP_LT;
    } else if (ctx->T_GT()) {
        return ast_operator_type::AST_OP_GT;
    } else if (ctx->T_LE()) {
        return ast_operator_type::AST_OP_LE;
    } else if (ctx->T_GE()) {
        return ast_operator_type::AST_OP_GE;
    }
    
    // 默认返回小于运算符
    return ast_operator_type::AST_OP_LT;
}

/// @brief 访问逻辑非一元表达式
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitLogicalNotUnaryExp(MiniCParser::LogicalNotUnaryExpContext* ctx) 
{
    // 获取操作数
    ast_node* operand = std::any_cast<ast_node*>(visit(ctx->unaryExp()));
    
    // 创建逻辑非节点
    return ast_node::New(ast_operator_type::AST_OP_NOT, operand, nullptr);
}

/// @brief 访问实参列表
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitRealParamList(MiniCParser::RealParamListContext* ctx) 
{
    // 创建实参列表节点
    ast_node* paramsNode = new ast_node(ast_operator_type::AST_OP_FUNC_REAL_PARAMS);
    
    // 遍历每个表达式并添加到参数列表
    for (auto exprCtx : ctx->expr()) {
        ast_node* exprNode = std::any_cast<ast_node*>(visitExpr(exprCtx));
        paramsNode->insert_son_node(exprNode);
    }
    
    return paramsNode;
}