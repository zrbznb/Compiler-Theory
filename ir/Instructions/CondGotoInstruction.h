///
/// @file CondGotoInstruction.h
/// @brief 条件分支指令
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
#include "LabelInstruction.h"
#include "IntegerType.h"

///
/// @brief 条件分支指令
///
class CondGotoInstruction : public Instruction {
private:
    LabelInstruction * trueLabel;
    LabelInstruction * falseLabel;

public:
    /// @brief 构造函数
    /// @param _func 所属函数
    /// @param _cond 条件
    /// @param _trueLabel 条件为真时跳转的目标Label
    /// @param _falseLabel 条件为假时跳转的目标Label
    CondGotoInstruction(Function * _func, Value * _cond, LabelInstruction * _trueLabel, LabelInstruction * _falseLabel);

    /// @brief 转换成字符串
    void toString(std::string & str) override;

    /// @brief 获取真标签
    LabelInstruction * getTrueLabel() const;

    /// @brief 获取假标签
    LabelInstruction * getFalseLabel() const;
};
