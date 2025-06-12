///
/// @file LoadArrayInstruction.cpp
/// @brief 从数组加载值指令实现
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

#include "LoadArrayInstruction.h"

LoadArrayInstruction::LoadArrayInstruction(Function* _func, Value* _arrayPtr, Type* _elementType)
    : Instruction(_func, IRInstOperator::IRINST_OP_LOAD_ARRAY, _elementType)
{
    // 数组元素指针作为操作数
    addOperand(_arrayPtr);
}

void LoadArrayInstruction::toString(std::string& str)
{
    Value* arrayPtr = getOperand(0);
    str = getIRName() + " = *" + arrayPtr->getIRName(); // 解引用操作
}
