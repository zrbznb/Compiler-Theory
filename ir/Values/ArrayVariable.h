///
/// @file ArrayVariable.h
/// @brief 数组变量类定义
/// @author 
/// @version 1.0
/// @date 2024-12-06
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-12-06 <td>1.0     <td>        <td>新建
/// </table>
///

#pragma once

#include "Values/LocalVariable.h"
#include "Types/ArrayType.h"

/// @brief 数组变量类，表示数组型局部变量
class ArrayVariable : public LocalVariable {
public:
    /// @brief 构造函数
    /// @param _type 数组类型
    /// @param _name 变量名
    /// @param _scopeLevel 作用域层级
    ArrayVariable(ArrayType* _type, const std::string& _name = "", int32_t _scopeLevel = 1)
        : LocalVariable(_type, _name, _scopeLevel) {}

    /// @brief 是否是数组变量
    /// @return 始终返回true
    bool isArrayVariable() const { return true; }
    
    /// @brief 获取数组类型
    /// @return 数组类型
    ArrayType* getArrayType() const { 
        return static_cast<ArrayType*>(type); 
    }
};

/// @brief 形参数组变量类，表示作为函数形参的数组
class ArrayParamVariable : public ArrayVariable {
public:
    /// @brief 构造函数
    /// @param _type 数组类型
    /// @param _name 变量名
    ArrayParamVariable(ArrayType* _type, const std::string& _name = "")
        : ArrayVariable(_type, _name, 1) {
        isParameter = true;
    }

    /// @brief 是否是形参
    bool isParam() const { return isParameter; }

private:
    bool isParameter = true;
};
