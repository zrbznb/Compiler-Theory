///
/// @file IRGenerator.h
/// @brief AST遍历产生线性IR的头文件
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
#pragma once

#include <unordered_map>
#include <vector>

#include "AST.h"
#include "Module.h"
#include "LabelInstruction.h" // 添加这个头文件引入
#include "Values/ArrayVariable.h"
#include "Instructions/ArrayAccessInstruction.h"
#include "Instructions/LoadArrayInstruction.h"
#include "Instructions/StoreArrayInstruction.h"

/// @brief AST遍历产生线性IR类
class IRGenerator {

public:
    /// @brief 构造函数
    /// @param root
    /// @param _module
    IRGenerator(ast_node * root, Module * _module);

    /// @brief 析构函数
    ~IRGenerator() = default;

    /// @brief 运行产生IR
    bool run();

protected:
    /// @brief 编译单元AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_compile_unit(ast_node * node);

    /// @brief 函数定义AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_function_define(ast_node * node);

    /// @brief 形式参数AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_function_formal_params(ast_node * node);

    /// @brief 函数调用AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_function_call(ast_node * node);

    /// @brief 语句块（含函数体）AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_block(ast_node * node);

    /// @brief 整数加法AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_add(ast_node * node);

    /// @brief 整数减法AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_sub(ast_node * node);

    /// @brief 整数乘法AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_mul(ast_node * node);

    /// @brief 整数除法AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_div(ast_node * node);

    /// @brief 整数求余AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_mod(ast_node * node);

    /// @brief 赋值AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_assign(ast_node * node);

    /// @brief return节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_return(ast_node * node);

    /// @brief 类型叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_type(ast_node * node);

    /// @brief 标识符叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_var_id(ast_node * node);

    /// @brief 无符号整数字面量叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_uint(ast_node * node);

    /// @brief float数字面量叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_float(ast_node * node);

    /// @brief 变量声明语句节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_declare_statment(ast_node * node);

    /// @brief 变量定声明节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_variable_declare(ast_node * node);

    /// @brief 未知节点类型的节点处理
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_default(ast_node * node);

    /// @brief 根据AST的节点运算符查找对应的翻译函数并执行翻译动作
    /// @param node AST节点
    /// @return 成功返回node节点，否则返回nullptr
    ast_node * ir_visit_ast_node(ast_node * node);

    /// @brief AST的节点操作函数
    typedef bool (IRGenerator::*ast2ir_handler_t)(ast_node *);

    /// @brief AST节点运算符与动作函数关联的映射表
    std::unordered_map<ast_operator_type, ast2ir_handler_t> ast2ir_handlers;

    /// @brief 关系表达式处理方法
    bool ir_lt(ast_node * node);
    bool ir_gt(ast_node * node);
    bool ir_le(ast_node * node);
    bool ir_ge(ast_node * node);
    bool ir_eq(ast_node * node);
    bool ir_neq(ast_node * node);

    /// @brief 逻辑表达式处理方法
    bool ir_and(ast_node * node);
    bool ir_or(ast_node * node);
    bool ir_not(ast_node * node);

    /// @brief 控制流语句处理方法
    bool ir_if(ast_node * node);
    bool ir_if_else(ast_node * node);
    bool ir_while(ast_node * node);
    bool ir_for(ast_node * node);
    bool ir_break(ast_node * node);
    bool ir_continue(ast_node * node);

    /// @brief 创建新的标签指令
    LabelInstruction * createLabel();

    /// @brief 控制流上下文管理
    struct LoopContext {
        LabelInstruction *continueLabel;  // continue跳转的目标
        LabelInstruction *breakLabel;     // break跳转的目标
        
        // 默认构造函数，初始化标签为空
        LoopContext() : continueLabel(nullptr), breakLabel(nullptr) {}
    };

    /// @brief 当前循环上下文栈
    std::vector<LoopContext> loopStack;

    /// @brief 条件表达式上下文，用于管理真假出口标签
    struct CondContext {
        LabelInstruction *trueLabel;  // 条件为真时跳转的标签
        LabelInstruction *falseLabel; // 条件为假时跳转的标签
        
        // 默认构造函数
        CondContext() : trueLabel(nullptr), falseLabel(nullptr) {}
        
        // 带参数的构造函数
        CondContext(LabelInstruction *t, LabelInstruction *f) : trueLabel(t), falseLabel(f) {}
        
        // 翻转真假标签
        CondContext flip() {
            return CondContext(falseLabel, trueLabel);
        }
    };

    /// @brief 数组类型节点翻译
    bool ir_array_type(ast_node* node);

    /// @brief 数组变量声明节点翻译
    bool ir_array_decl(ast_node* node);

    /// @brief 数组访问节点翻译
    bool ir_array_access(ast_node* node);

    /// @brief 处理getarray内置函数调用
    bool processGetArrayCall(ast_node* node);

    /// @brief 处理putarray内置函数调用
    bool processPutArrayCall(ast_node* node);

private:
    /// @brief 抽象语法树的根
    ast_node * root;

    /// @brief 符号表:模块
    Module * module;
};
