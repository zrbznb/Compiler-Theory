///
/// @file ArrayAccessInstruction.cpp
/// @brief 数组访问指令实现
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

#include "ArrayAccessInstruction.h"
#include <sstream>

ArrayAccessInstruction::ArrayAccessInstruction(Function* _func, Value* _array, 
                                             const std::vector<Value*>& _indices, Type* _type)
    : Instruction(_func, IRInstOperator::IRINST_OP_ARRAY_ACCESS, _type)
{
    // 添加数组作为操作数
    addOperand(_array);
    
    // 添加所有索引作为操作数
    for (Value* index : _indices) {
        addOperand(index);
    }
}

void ArrayAccessInstruction::toString(std::string& str)
{
    std::stringstream ss;
    
    // 获取数组变量
    Value* arrayVar = getOperand(0);
    
    ss << getIRName() << " = array_access " << arrayVar->getIRName();
    
    // 添加所有索引
    for (size_t i = 1; i < getNumOperands(); i++) {
        ss << ", " << getOperand(i)->getIRName();
    }
    
    str = ss.str();
}
