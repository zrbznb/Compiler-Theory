﻿///
/// @file AST.cpp
/// @brief 抽象语法树AST管理的实现
/// @author zenglj (zenglj@live.com)
/// @version 1.1
/// @date 2024-11-23
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>新做
/// <tr><td>2024-11-23 <td>1.1     <td>zenglj  <td>表达式版增强
/// </table>
///
#include <cstdarg>
#include <cstdint>
#include <string>

#include "AST.h"
#include "AttrType.h"
#include "Types/IntegerType.h"
#include "Types/VoidType.h"

/* 整个AST的根节点 */
ast_node * ast_root = nullptr;

/// @brief 创建指定节点类型的节点
/// @param _node_type 节点类型
/// @param _line_no 行号
ast_node::ast_node(ast_operator_type _node_type, Type * _type, int64_t _line_no)
    : node_type(_node_type), line_no(-1), type(_type)
{}

/// @brief 构造函数
/// @param _type 节点值的类型
/// @param line_no 行号
ast_node::ast_node(Type * _type) : ast_node(ast_operator_type::AST_OP_LEAF_TYPE, _type, -1)
{}

/// @brief 针对无符号整数字面量的构造函数
/// @param attr 无符号整数字面量
ast_node::ast_node(digit_int_attr attr)
    : ast_node(ast_operator_type::AST_OP_LEAF_LITERAL_UINT, IntegerType::getTypeInt(), attr.lineno)
{
    integer_val = attr.val;
}

/// @brief 针对标识符ID的叶子构造函数
/// @param attr 字符型字面量
ast_node::ast_node(var_id_attr attr) : ast_node(ast_operator_type::AST_OP_LEAF_VAR_ID, VoidType::getType(), attr.lineno)
{
    name = attr.id;
}

/// @brief 针对标识符ID的叶子构造函数
/// @param _id 标识符ID
/// @param _line_no 行号
ast_node::ast_node(std::string _id, int64_t _line_no)
    : ast_node(ast_operator_type::AST_OP_LEAF_VAR_ID, VoidType::getType(), _line_no)
{
    name = _id;
}

/// @brief 判断是否是叶子节点
/// @return true：是叶子节点 false：内部节点
bool ast_node::isLeafNode()
{
    bool is_leaf;

    switch (this->node_type) {
        case ast_operator_type::AST_OP_LEAF_LITERAL_UINT:
        case ast_operator_type::AST_OP_LEAF_LITERAL_FLOAT:
        case ast_operator_type::AST_OP_LEAF_VAR_ID:
        case ast_operator_type::AST_OP_LEAF_TYPE:
            is_leaf = true;
            break;
        default:
            is_leaf = false;
            break;
    }

    return is_leaf;
}

/// @brief 创建指定节点类型的节点，请注意在指定有效的孩子后必须追加一个空指针nullptr，表明可变参数结束
/// @param type 节点类型
/// @param son_num 孩子节点的个数
/// @param ...
/// 可变参数，可支持插入若干个孩子节点，自左往右的次序，最後一个孩子节点必须指定为nullptr。如果没有孩子，则指定为nullptr
/// @return 创建的节点
ast_node * ast_node::New(ast_operator_type type, ...)
{
    ast_node * parent_node = new ast_node(type);

    va_list valist;

    /* valist指向传入的第一个可选参数 */
    va_start(valist, type);

    for (;;) {

        // 获取节点对象。如果最后一个对象为空指针，则说明结束
        ast_node * node = va_arg(valist, ast_node *);
        if (nullptr == node) {
            break;
        }

        // 插入到父节点中
        parent_node->insert_son_node(node);
    }

    /* 清理为 valist 保留的内存 */
    va_end(valist);

    return parent_node;
}

/// @brief 向父节点插入一个节点
/// @param parent 父节点
/// @param node 节点
ast_node * ast_node::insert_son_node(ast_node * node)
{
    if (node) {

        // 孩子节点有效时加入，主要为了避免空语句等时会返回空指针
        node->parent = this;
        this->sons.push_back(node);
    }

    return this;
}

/// @brief 创建无符号整数的叶子节点
/// @param attr 无符号整数字面量
ast_node * ast_node::New(digit_int_attr attr)
{
    ast_node * node = new ast_node(attr);

    return node;
}

/// @brief 创建标识符的叶子节点
/// @param attr 字符型字面量
ast_node * ast_node::New(var_id_attr attr)
{
    ast_node * node = new ast_node(attr);

    return node;
}

/// @brief 创建标识符的叶子节点
/// @param id 词法值
/// @param line_no 行号
ast_node * ast_node::New(std::string id, int64_t lineno)
{
    ast_node * node = new ast_node(id, lineno);

    return node;
}

/// @brief 创建具备指定类型的节点
/// @param type 节点值类型
/// @param line_no 行号
/// @return 创建的节点
ast_node * ast_node::New(Type * type)
{
    ast_node * node = new ast_node(type);

    return node;
}

/// @brief 递归清理抽象语法树
/// @param node AST的节点
void ast_node::Delete(ast_node * node)
{
    if (node && !node->isLeafNode()) {

        for (auto child: node->sons) {
            ast_node::Delete(child);
        }

        // 这里没有必要清理孩子，由于下面就要删除该节点
        // node->sons.clear();
    }

    // 清理node资源
    delete node;
}

///
/// @brief AST资源清理
///
void free_ast(ast_node * root)
{
    ast_node::Delete(root);
}

/// @brief 创建函数定义类型的内部AST节点
/// @param type_node 类型节点
/// @param name_node 函数名字节点
/// @param block_node 函数体语句块节点
/// @param params_node 函数形参，可以没有参数
/// @return 创建的节点
ast_node * create_func_def(ast_node * type_node, ast_node * name_node, ast_node * block_node, ast_node * params_node)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_FUNC_DEF, type_node->type, name_node->line_no);

    // 设置函数名
    node->name = name_node->name;

    // 如果没有参数，则创建参数节点
    if (!params_node) {
        params_node = new ast_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS);
    }

    // 如果没有函数体，则创建函数体，也就是语句块
    if (!block_node) {
        block_node = new ast_node(ast_operator_type::AST_OP_BLOCK);
    }

    (void) node->insert_son_node(type_node);
    (void) node->insert_son_node(name_node);
    (void) node->insert_son_node(params_node);
    (void) node->insert_son_node(block_node);

    return node;
}

/// @brief 创建函数定义类型的内部AST节点
/// @param type 返回值类型
/// @param id 函数名字
/// @param block_node 函数体语句块节点
/// @param params_node 函数形参，可以没有参数
/// @return 创建的节点
ast_node * create_func_def(type_attr & type, var_id_attr & id, ast_node * block_node, ast_node * params_node)
{
    // 创建整型类型节点的终结符节点
    ast_node * type_node = create_type_node(type);

    // 创建标识符终结符节点
    ast_node * id_node = ast_node::New(id.id, id.lineno);

    // 对于字符型字面量的字符串空间需要释放，因词法用到了strdup进行了字符串复制
    free(id.id);
    id.id = nullptr;

    return create_func_def(type_node, id_node, block_node, params_node);
}

/// @brief 创建AST的内部节点
/// @param node_type 节点类型
/// @param first_child 第一个孩子节点
/// @param second_child 第一个孩子节点
/// @param third_child 第一个孩子节点
/// @return 创建的节点
ast_node * create_contain_node(ast_operator_type node_type,
                               ast_node * first_child,
                               ast_node * second_child,
                               ast_node * third_child)
{
    ast_node * node = new ast_node(node_type);

    if (first_child) {
        (void) node->insert_son_node(first_child);
    }

    if (second_child) {
        (void) node->insert_son_node(second_child);
    }

    if (third_child) {
        (void) node->insert_son_node(third_child);
    }

    return node;
}

Type * typeAttr2Type(type_attr & attr)
{
    if (attr.type == BasicType::TYPE_INT) {
        return IntegerType::getTypeInt();
    } else {
        return VoidType::getType();
    }
}

/// @brief 创建类型节点
/// @param type 类型信息
/// @return 创建的节点
ast_node * create_type_node(type_attr & attr)
{
    Type * type = typeAttr2Type(attr);

    ast_node * type_node = ast_node::New(type);

    return type_node;
}

/// @brief 创建函数调用的节点
/// @param funcname_node 函数名节点
/// @param params_node 实参节点
/// @return 创建的节点
ast_node * create_func_call(ast_node * funcname_node, ast_node * params_node)
{
    ast_node * node = new ast_node(ast_operator_type::AST_OP_FUNC_CALL);

    // 设置调用函数名
    node->name = funcname_node->name;

    // 如果没有参数，则创建参数节点
    if (!params_node) {
        params_node = new ast_node(ast_operator_type::AST_OP_FUNC_REAL_PARAMS);
    }

    (void) node->insert_son_node(funcname_node);
    (void) node->insert_son_node(params_node);

    return node;
}

///
/// @brief 根据第一个变量定义创建变量声明语句节点
/// @param first_child 第一个变量定义节点，其类型为AST_OP_VAR_DECL
/// @return ast_node* 变量声明语句节点
///
ast_node * create_var_decl_stmt_node(ast_node * first_child)
{
    // 创建变量声明语句
    ast_node * stmt_node = create_contain_node(ast_operator_type::AST_OP_DECL_STMT);

    if (first_child) {

        stmt_node->type = first_child->type;

        // 插入到变量声明语句
        (void) stmt_node->insert_son_node(first_child);
    }

    return stmt_node;
}

ast_node * createVarDeclNode(Type * type, var_id_attr & id)
{
    // 创建整型类型节点的终结符节点
    ast_node * type_node = ast_node::New(type);

    // 创建标识符终结符节点
    ast_node * id_node = ast_node::New(id.id, id.lineno);

    // 对于字符型字面量的字符串空间需要释放，因词法用到了strdup进行了字符串复制
    free(id.id);
    id.id = nullptr;

    // 创建变量定义节点
    ast_node * decl_node = create_contain_node(ast_operator_type::AST_OP_VAR_DECL, type_node, id_node);

    // 暂存类型
    decl_node->type = type;

    return decl_node;
}

ast_node * createVarDeclNode(type_attr & type, var_id_attr & id)
{
    return createVarDeclNode(typeAttr2Type(type), id);
}

///
/// @brief 根据变量的类型和属性创建变量声明语句节点
/// @param type 变量的类型
/// @param id 变量的名字
/// @return ast_node* 变量声明语句节点
///
ast_node * create_var_decl_stmt_node(type_attr & type, var_id_attr & id)
{
    // 创建变量定义节点
    ast_node * decl_node = createVarDeclNode(type, id);

    // 创建变量声明语句
    ast_node * stmt_node = create_contain_node(ast_operator_type::AST_OP_DECL_STMT);

    stmt_node->type = decl_node->type;

    // 插入到变量声明语句
    (void) stmt_node->insert_son_node(decl_node);

    return stmt_node;
}

///
/// @brief 向变量声明语句中追加变量声明
/// @param stmt_node 变量声明语句
/// @param id 变量的名字
/// @return ast_node* 变量声明语句节点
///
ast_node * add_var_decl_node(ast_node * stmt_node, var_id_attr & id)
{
    // 创建变量定义节点
    ast_node * decl_node = createVarDeclNode(stmt_node->type, id);

    // 插入到变量声明语句
    (void) stmt_node->insert_son_node(decl_node);

    return stmt_node;
}

///
/// @brief 创建带初始值的变量声明节点
/// @param type 类型
/// @param id 变量标识符
/// @param init_expr 初始值表达式
/// @return 变量声明节点
///
ast_node* createVarDeclNodeWithInit(Type* type, var_id_attr& id, ast_node* init_expr)
{
    // 创建类型节点
    ast_node* type_node = ast_node::New(type);
    
    // 创建标识符节点
    ast_node* id_node = ast_node::New(id.id, id.lineno);
    
    // 释放ID字符串
    free(id.id);
    id.id = nullptr;
    
    // 创建变量声明节点
    ast_node* decl_node;
    if (init_expr) {
        decl_node = create_contain_node(ast_operator_type::AST_OP_VAR_DECL, type_node, id_node, init_expr);
    } else {
        decl_node = create_contain_node(ast_operator_type::AST_OP_VAR_DECL, type_node, id_node);
    }
    
    // 设置类型
    decl_node->type = type;
    
    return decl_node;
}

///
/// @brief 创建带初始值的变量声明节点
/// @param type 类型属性
/// @param id 变量标识符
/// @param init_expr 初始值表达式
/// @return 变量声明节点
///
ast_node* createVarDeclNodeWithInit(type_attr& type, var_id_attr& id, ast_node* init_expr)
{
    return createVarDeclNodeWithInit(typeAttr2Type(type), id, init_expr);
}

///
/// @brief 创建带初始值的变量声明语句节点
/// @param type 变量类型
/// @param id 变量标识符
/// @param init_expr 初始值表达式
/// @return 变量声明语句节点
///
ast_node* create_var_decl_stmt_node_with_init(type_attr& type, var_id_attr& id, ast_node* init_expr)
{
    // 创建变量定义节点
    ast_node* decl_node = createVarDeclNodeWithInit(type, id, init_expr);
    
    // 创建变量声明语句节点
    ast_node* stmt_node = create_contain_node(ast_operator_type::AST_OP_DECL_STMT);
    stmt_node->type = decl_node->type;
    
    // 插入到变量声明语句
    (void)stmt_node->insert_son_node(decl_node);
    
    return stmt_node;
}

///
/// @brief 向变量声明语句中追加带初始值的变量声明
/// @param stmt_node 变量声明语句
/// @param id 变量的名字
/// @param init_expr 初始值表达式
/// @return ast_node* 变量声明语句节点
///
ast_node* add_var_decl_node_with_init(ast_node* stmt_node, var_id_attr& id, ast_node* init_expr)
{
    // 创建变量定义节点
    ast_node* decl_node = createVarDeclNodeWithInit(stmt_node->type, id, init_expr);
    
    // 插入到变量声明语句
    (void)stmt_node->insert_son_node(decl_node);
    
    return stmt_node;
}

/// @brief 创建函数形式参数的节点
/// @param type 参数类型
/// @param param_name 形式参数名
/// @param line_no 行号
/// @return 创建的节点
ast_node * create_func_formal_param(Type * type, const std::string & param_name, int64_t line_no)
{
    // 创建类型节点
    ast_node * type_node = ast_node::New(type);
    
    // 创建标识符节点
    ast_node * id_node = ast_node::New(param_name, line_no);
    
    // 创建形参节点
    ast_node * param_node = new ast_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAM);
    param_node->type = type;
    param_node->line_no = line_no;
    
    // 添加类型和名字作为孩子节点
    (void) param_node->insert_son_node(type_node);
    (void) param_node->insert_son_node(id_node);
    
    return param_node;
}

/// @brief 创建函数形式参数的节点
/// @param type_attr 参数类型属性
/// @param param_name 形式参数名
/// @param line_no 行号
/// @return 创建的节点
ast_node * create_func_formal_param(type_attr & type, const std::string & param_name, int64_t line_no)
{
    // 转换类型属性为Type指针
    Type * typePtr = typeAttr2Type(type);
    
    // 调用已有函数实现
    return create_func_formal_param(typePtr, param_name, line_no);
}

/// @brief 创建数组类型节点
/// @param baseType 基本类型
/// @param dimensions 维度列表
/// @return 创建的节点
ast_node* create_array_type_node(BasicType baseType, const std::vector<int>& dimensions) 
{
    // 创建数组类型节点
    ast_node* arrayTypeNode = new ast_node(ast_operator_type::AST_OP_ARRAY_TYPE);
    
    // 设置基本类型
    // TODO: 为数组类型创建适当的Type对象
    if (baseType == BasicType::TYPE_INT) {
        arrayTypeNode->type = IntegerType::getTypeInt();
    } else {
        arrayTypeNode->type = VoidType::getType();
    }
    
    // 存储维度信息
    for (int dim : dimensions) {
        // 为每个维度创建整数字面量节点
        digit_int_attr dimAttr = {(uint32_t)dim, -1};
        ast_node* dimNode = ast_node::New(dimAttr);
        arrayTypeNode->insert_son_node(dimNode);
    }
    
    return arrayTypeNode;
}

/// @brief 创建数组变量定义节点
/// @param typeNode 类型节点
/// @param idNode 标识符节点
/// @param dimsNodes 维度表达式节点列表
/// @param initExpr 可选的初始化表达式
/// @return 创建的节点
ast_node* create_array_decl_node(ast_node* typeNode, ast_node* idNode, 
                               const std::vector<ast_node*>& dimsNodes, 
                               ast_node* initExpr)
{
    // 创建数组声明节点
    ast_node* arrayDeclNode = new ast_node(ast_operator_type::AST_OP_ARRAY_DECL);
    
    // 设置类型
    arrayDeclNode->type = typeNode->type;
    
    // 添加类型节点
    arrayDeclNode->insert_son_node(typeNode);
    
    // 添加标识符节点
    arrayDeclNode->name = idNode->name;
    arrayDeclNode->insert_son_node(idNode);
    
    // 添加维度节点
    for (ast_node* dimNode : dimsNodes) {
        arrayDeclNode->insert_son_node(dimNode);
    }
    
    // 如果有初始化表达式，添加它
    if (initExpr) {
        arrayDeclNode->insert_son_node(initExpr);
    }
    
    return arrayDeclNode;
}

/// @brief 创建数组访问节点
/// @param arrayNode 数组变量节点
/// @param indexNodes 下标表达式节点列表
/// @return 创建的节点
ast_node* create_array_access_node(ast_node* arrayNode, const std::vector<ast_node*>& indexNodes)
{
    // 创建数组访问节点
    ast_node* accessNode = new ast_node(ast_operator_type::AST_OP_ARRAY_ACCESS);
    
    // 设置数组名
    accessNode->name = arrayNode->name;
    
    // 添加数组变量节点作为第一个子节点
    accessNode->insert_son_node(arrayNode);
    
    // 添加所有索引节点
    for (ast_node* indexNode : indexNodes) {
        accessNode->insert_son_node(indexNode);
    }
    
    return accessNode;
}
