///
/// @file Module.cpp
/// @brief 模块类实现
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

#include "Module.h"
#include "Values/ArrayVariable.h"
#include <algorithm>  // 添加这个头文件以使用std::find_if

///
/// @brief 创建函数
/// @param name 函数名
/// @param returnType 返回类型
/// @return 创建的函数，如果函数已存在则返回nullptr
Function * Module::newFunction(std::string name, Type * returnType, bool isBuiltin)
{
    // 查找函数是否已存在
    Function* existingFunc = findFunction(name);
    
    if (existingFunc) {
        // 已存在的内置函数可以被用户函数覆盖，但用户函数不能重复定义
        if (isBuiltin && !existingFunc->isBuiltin()) {
            // 不允许内置函数覆盖用户函数
            return nullptr;
        } else if (!isBuiltin && existingFunc->isBuiltin()) {
            // 允许用户函数覆盖内置函数，从vector中移除现有函数
            auto it = std::find_if(functions.begin(), functions.end(), 
                [&name](Function* f) { return f->getName() == name; });
            if (it != functions.end()) {
                functions.erase(it);
            }
        } else {
            // 同类型函数重复定义
            return nullptr;
        }
    }
    
    std::vector<Type *> paramTypes;
    FunctionType * funcType = new FunctionType(returnType, paramTypes);
    Function * func = new Function(name, funcType, isBuiltin);
    
    // 添加到函数表
    functions.push_back(func);
    
    return func;
}

///
/// @brief 查找函数
/// @param name 函数名
/// @return 函数指针，如果不存在则返回nullptr
Function* Module::findFunction(const std::string& name)
{
    for (auto func : functions) {
        if (func->getName() == name) {
            return func;
        }
    }
    return nullptr;
}

///
/// @brief 创建数组变量
/// @param arrayType 数组类型
/// @param name 变量名
/// @param scopeLevel 范围级别
/// @return 创建的数组变量指针
ArrayVariable* Module::newArrayVariable(ArrayType* arrayType, const std::string& name, int scopeLevel) {
    if (currentFunc) {
        // 在当前函数中创建数组局部变量
        return currentFunc->newArrayVariable(arrayType, name, scopeLevel);
    }
    
    // 在全局创建数组变量 - 可以根据需要实现
    return nullptr;
}

///
/// @brief 创建数组参数变量
/// @param arrayType 数组类型
/// @param name 变量名
/// @return 创建的数组参数变量指针
ArrayParamVariable* Module::newArrayParamVariable(ArrayType* arrayType, const std::string& name) {
    if (currentFunc) {
        // 在当前函数中创建数组参数变量
        return currentFunc->newArrayParamVariable(arrayType, name);
    }
    
    return nullptr;
}