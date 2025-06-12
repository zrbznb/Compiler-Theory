///
/// @file StoreArrayInstruction.h
/// @brief 存储值到数组指令
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

#include "VoidType.h"
#include "Instruction.h"

/// @brief 存储值到数组指令
class StoreArrayInstruction : public Instruction {
public:
    /// @brief 构造函数
    /// @param _func 所属函数
    /// @param _arrayPtr 数组元素指针（由ArrayAccessInstruction生成）
    /// @param _value 要存储的值
    StoreArrayInstruction(Function* _func, Value* _arrayPtr, Value* _value);

    /// @brief 转换成字符串
    void toString(std::string& str) override;
};
