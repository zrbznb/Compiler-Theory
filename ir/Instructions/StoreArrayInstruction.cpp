///
/// @file StoreArrayInstruction.cpp
/// @brief 存储值到数组指令实现
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

#include "StoreArrayInstruction.h"

StoreArrayInstruction::StoreArrayInstruction(Function* _func, Value* _arrayPtr, Value* _value)
    : Instruction(_func, IRInstOperator::IRINST_OP_STORE_ARRAY, VoidType::getType())
{
    // 数组元素指针作为第一个操作数
    addOperand(_arrayPtr);
    // 要存储的值作为第二个操作数
    addOperand(_value);
}

void StoreArrayInstruction::toString(std::string& str)
{
    Value* arrayPtr = getOperand(0);
    Value* value = getOperand(1);
    str = "*" + arrayPtr->getIRName() + " = " + value->getIRName(); // 解引用赋值操作
}
