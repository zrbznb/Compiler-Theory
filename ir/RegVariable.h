///
/// @file RegVariable.h
/// @brief 寄存器变量定义
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

#include "Value.h"
#include "Types/IntegerType.h"

/// @brief 寄存器变量类，表示在寄存器中的变量
class RegVariable : public Value {
    
private:
    /// @brief 寄存器编号
    int32_t regId;
    
public:
    /// @brief 构造函数
    /// @param _regId 寄存器编号
    RegVariable(int32_t _regId) 
        : Value(IntegerType::getTypeInt()), regId(_regId) 
    {
        setName("r" + std::to_string(_regId));
        setIRName("r" + std::to_string(_regId));
    }
    
    /// @brief 获取寄存器编号
    /// @return 寄存器编号
    int32_t getRegId() override {
        return regId;
    }
};
