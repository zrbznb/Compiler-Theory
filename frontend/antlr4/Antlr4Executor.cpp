///
/// @file Antlr4Executor.cpp
/// @brief antlr4的词法与语法分析解析器
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// </table>
///
#include <iostream>

#include "AST.h"
#include "Antlr4Executor.h"
#include "Antlr4CSTVisitor.h"
#include "MiniCLexer.h"
#include "Common.h"

/// @brief 前端词法与语法解析生成AST
/// @return true: 成功 false：错误
bool Antlr4Executor::run()
{
    std::ifstream ifs;
    ifs.open(filename);
    if (!ifs.is_open()) {
        minic_log(LOG_ERROR, "文件(%s)不能打开，可能不存在", filename.c_str());
        return false;
    }

    // antlr4的输入流类实例
    antlr4::ANTLRInputStream input{ifs};

    // 词法分析器实例
    MiniCLexer lexer{&input};

    // 词法分析器实例转化成记号(Token)流
    antlr4::CommonTokenStream tokenStream{&lexer};

    // 利用antlr4进行分析，从compileUnit开始分析输入字符串
    MiniCParser parser{&tokenStream};

    // 从具体语法树的根结点进行深度优先遍历，生成抽象语法树
    auto cstRoot = parser.compileUnit();
    if (!cstRoot) {
        minic_log(LOG_ERROR, "Antlr4的词语与语法分析错误");
        return false;
    }

    /// 新建遍历器对具体语法树进行分析，产生抽象语法树
    MiniCCSTVisitor visitor;

    // 遍历产生抽象语法树
    astRoot = visitor.run(cstRoot);

    // 添加内置库函数到AST
    addBuiltinFunctions();

    return true;
}

/// @brief 添加内置库函数到AST
void Antlr4Executor::addBuiltinFunctions()
{
    // 如果没有根节点，无法添加内置函数
    if (!astRoot) return;
    
    // 添加getint函数
    // addBuiltinFunction("getint", BasicType::TYPE_INT, {});
    
    // // 添加getch函数
    // addBuiltinFunction("getch", BasicType::TYPE_INT, {});
    
    // // 添加getarray函数 - 读取数组函数
    // addBuiltinFunction("getarray", BasicType::TYPE_INT, {BasicType::TYPE_INT});
    
    // // 添加putint函数
    // addBuiltinFunction("putint", BasicType::TYPE_VOID, {BasicType::TYPE_INT});
    
    // // 添加putch函数
    // addBuiltinFunction("putch", BasicType::TYPE_VOID, {BasicType::TYPE_INT});
    
    // // 添加putarray函数 - 输出数组函数
    // addBuiltinFunction("putarray", BasicType::TYPE_VOID, {BasicType::TYPE_INT, BasicType::TYPE_INT});
    
    // // 添加putstr函数
    // addBuiltinFunction("putstr", BasicType::TYPE_VOID, {BasicType::TYPE_INT});
    
    // // 添加starttime函数
    // addBuiltinFunction("starttime", BasicType::TYPE_VOID, {});
    
    // // 添加stoptime函数
    // addBuiltinFunction("stoptime", BasicType::TYPE_VOID, {});
}

/// @brief 添加内置库函数
/// @param name 函数名
/// @param returnType 返回类型
/// @param paramTypes 参数类型列表
void Antlr4Executor::addBuiltinFunction(const std::string& name, BasicType returnType, 
                                      const std::vector<BasicType>& paramTypes)
{
    // 创建返回类型
    type_attr retType{returnType, -1};
    ast_node* returnTypeNode = create_type_node(retType);
    
    // 创建函数名
    ast_node* nameNode = ast_node::New(name, -1);
    
    // 创建形参列表
    ast_node* paramsNode = new ast_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS);
    for (size_t i = 0; i < paramTypes.size(); i++) {
        type_attr paramType{paramTypes[i], -1};
        std::string paramName = "param" + std::to_string(i);
        ast_node* paramNode = create_func_formal_param(paramType, paramName, -1);
        paramsNode->insert_son_node(paramNode);
    }
    
    // 创建空的函数体
    ast_node* blockNode = new ast_node(ast_operator_type::AST_OP_BLOCK);
    
    // 创建函数节点
    ast_node* funcNode = ast_node::New(ast_operator_type::AST_OP_FUNC_DEF, returnTypeNode, nameNode, paramsNode, blockNode, nullptr);
    
    // 设置函数名称
    funcNode->name = name;
    
    // 设置为内置函数
    funcNode->val = (Value*)1; // 使用val字段标记为内置函数，后续IR生成时可以识别
    
    // 添加到编译单元
    astRoot->insert_son_node(funcNode);
}
