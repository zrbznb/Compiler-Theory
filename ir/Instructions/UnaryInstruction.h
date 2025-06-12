///
/// @file UnaryInstruction.h
/// @brief 一元操作指令
///
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-23
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-23 <td>1.0     <td>zenglj  <td>新建
/// </table>
///
#pragma once

#include "Instruction.h"

///
/// @brief 一元运算指令
///
class UnaryInstruction : public Instruction {

public:
    /// @brief 构造函数
    /// @param _func 所属函数
    /// @param _op 操作符 
    /// @param _operand 操作数
    /// @param _type 结果类型
    UnaryInstruction(Function * _func, IRInstOperator _op, Value * _operand, Type * _type);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};
