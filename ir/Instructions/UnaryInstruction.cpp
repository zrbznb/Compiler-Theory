///
/// @file UnaryInstruction.cpp
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
#include "UnaryInstruction.h"

/// @brief 构造函数
/// @param _func 所属函数
/// @param _op 操作符
/// @param _operand 操作数
/// @param _type 结果类型
UnaryInstruction::UnaryInstruction(Function * _func, IRInstOperator _op, Value * _operand, Type * _type)
    : Instruction(_func, _op, _type)
{
    addOperand(_operand);
}

/// @brief 转换成字符串
void UnaryInstruction::toString(std::string & str)
{
    Value *operand = getOperand(0);
    
    switch (op) {
        case IRInstOperator::IRINST_OP_NOT:
            str = getIRName() + " = not " + operand->getIRName();
            break;
        default:
            Instruction::toString(str);
            break;
    }
}
