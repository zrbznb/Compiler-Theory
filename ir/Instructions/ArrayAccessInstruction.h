///
/// @file ArrayAccessInstruction.h
/// @brief 数组访问指令
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

#include "Instruction.h"
#include <vector>

/// @brief 数组访问指令，用于计算数组元素地址
class ArrayAccessInstruction : public Instruction {
public:
    /// @brief 构造函数
    /// @param _func 所属函数
    /// @param _array 数组变量
    /// @param _indices 索引表达式列表
    /// @param _type 结果类型（指向元素类型的指针）
    ArrayAccessInstruction(Function* _func, Value* _array, const std::vector<Value*>& _indices, Type* _type);

    /// @brief 转换成字符串
    void toString(std::string& str) override;
};
