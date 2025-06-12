///
/// @file CondGotoInstruction.cpp
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
#include "CondGotoInstruction.h"
#include "Types/VoidType.h"

/// @brief 构造函数
/// @param _func 所属函数
/// @param _cond 条件值
/// @param _trueLabel 条件为真时跳转的标签
/// @param _falseLabel 条件为假时跳转的标签
CondGotoInstruction::CondGotoInstruction(Function * _func, 
                                         Value * _cond, 
                                         LabelInstruction * _trueLabel, 
                                         LabelInstruction * _falseLabel)
    : Instruction(_func, IRInstOperator::IRINST_OP_COND_GOTO, IntegerType::getTypeBool()),
      trueLabel(_trueLabel), falseLabel(_falseLabel)
{
    // 确保添加操作数 - 这是关键，确保所有操作数都被正确添加
    addOperand(_cond);
    addOperand(_trueLabel);
    addOperand(_falseLabel);
}

/// @brief 转换成字符串
/// @param str 转换后的字符串
void CondGotoInstruction::toString(std::string & str)
{
    Value *condition = getOperand(0);
    
    // 使用布尔值直接作为跳转条件
    str = "bc " + condition->getIRName() + ", label " + trueLabel->getIRName() + 
          ", label " + falseLabel->getIRName();
}

/// @brief 获取真标签
/// @return 真标签
LabelInstruction * CondGotoInstruction::getTrueLabel() const
{
    return trueLabel;
}

/// @brief 获取假标签
/// @return 假标签
LabelInstruction * CondGotoInstruction::getFalseLabel() const
{
    return falseLabel;
}
