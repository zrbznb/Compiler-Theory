///
/// @file BinaryInstruction.h
/// @brief 二元操作指令，如加和减
///
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
#pragma once

#include "Instruction.h"

///
/// @brief 二元运算指令
///
class Move2Instruction : public Instruction {

public:
    /// @brief 构造函数
    /// @param _func 所属函数
    /// @param _op 操作符
    /// @param _srcVal1 源操作数1
    /// @param _srcVal2 源操作数2
    /// @param _type 结果类型
    int x;
    Move2Instruction(Function * _func, Value * _srcVal1);
    Move2Instruction(Function * _func,  Value * _srcVal1,int x);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};
