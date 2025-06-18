///
/// @file Module.h
/// @brief 模块头文件
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>新做
/// </table>
///
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Function.h"
#include "Values/ArrayVariable.h"
#include "Values/GlobalVariable.h"

///
/// @brief 模块类，管理所有的全局变量、函数等信息
///
class Module {

public:
    /// @brief 构造函数
    Module();

    /// @brief 析构函数
    ~Module();

    /// @brief 获取当前处理的函数
    /// @return 当前函数
    Function * getCurrentFunction();

    /// @brief 设置当前处理的函数
    /// @param func 函数
    void setCurrentFunction(Function * func);

    /// @brief 查找函数
    /// @param name 函数名
    /// @return 找到的函数，未找到则返回nullptr
    Function * findFunction(const std::string& name);

    /// @brief 创建函数
    /// @param name 函数名
    /// @param returnType 返回类型
    /// @param isBuiltin 是否是内置函数，默认不是
    /// @return 创建的函数，如果函数已存在则返回nullptr
    Function * newFunction(std::string name, Type * returnType, bool isBuiltin = false);

    /// @brief 进入作用域
    void enterScope();

    /// @brief 离开作用域
    void leaveScope();

    /// @brief 添加全局变量
    /// @param var 全局变量
    void addGlobalValue(GlobalValue * var);

    /// @brief 获取全局变量
    /// @param name 变量名
    /// @return 找到的变量，未找到则返回nullptr
    GlobalValue * getGlobalValue(std::string name);

    /// @brief 模块指令信息输出
    /// @param str 输出的指令
    void toString(std::string & str);

    /// @brief 删除所有指令
    void Delete();

    /// @brief 新建数组变量
    /// @param arrayType 数组类型
    /// @param name 变量名
    /// @param scopeLevel 作用域层级
    /// @return 创建的数组变量
    ArrayVariable* newArrayVariable(ArrayType* arrayType, const std::string& name = "", int scopeLevel = 1);

    /// @brief 新建数组参数变量
    /// @param arrayType 数组类型
    /// @param name 变量名
    /// @return 创建的数组参数变量
    ArrayParamVariable* newArrayParamVariable(ArrayType* arrayType, const std::string& name = "");

    /// @brief 新建全局变量
    /// @param type 变量类型
    /// @param name 变量名
    /// @return 全局变量指针
    GlobalVariable* newGlobalVariable(Type* type, const std::string& name = "");

    /// @brief 新建全局数组变量
    /// @param arrayType 数组类型
    /// @param name 变量名
    /// @return 全局数组变量指针
    GlobalVariable* newGlobalArrayVariable(ArrayType* arrayType, const std::string& name = "");

    /// @brief 查找全局变量
    /// @param name 变量名
    /// @return 全局变量指针，未找到返回nullptr
    GlobalVariable* findGlobalVariable(const std::string& name) const;

    /// @brief 输出IR到文件
    /// @param filename 文件名
    void outputIR(const std::string& filename);

private:
    ///
    /// @brief 当前处理的函数
    ///
    Function * currentFunc = nullptr;

    ///
    /// @brief 全局变量表
    ///
    std::unordered_map<std::string, GlobalValue *> globalValueMap;

    ///
    /// @brief 函数表，存储模块中定义的所有函数
    ///
    std::vector<Function *> functions;

    ///
    /// @brief 当前作用域的层级
    ///
    int32_t scopeLevel = 0;

    ///
    /// @brief 全局变量列表
    ///
    std::vector<GlobalVariable*> globalVarsVector;
};