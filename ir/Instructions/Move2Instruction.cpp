///
/// @file Move2Instruction.cpp
/// @brief 二元操作指令
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
#include "Move2Instruction.h"
#include "IntegerType.h"
/// @brief 构造函数
/// @param _op 操作符
/// @param _result 结果操作数
/// @param _srcVal1 源操作数1
/// @param _srcVal2 源操作数2
Move2Instruction::Move2Instruction(Function * _func,
                        Value * _srcVal1)
						: Instruction(_func, IRInstOperator::IRINST_OP_MOVE, IntegerType::getTypeInt())
{
    this->x=0;
    addOperand(_srcVal1);
}
Move2Instruction::Move2Instruction(Function * _func,
	Value * _srcVal1,int x)
	: Instruction(_func, IRInstOperator::IRINST_OP_MOVE, IntegerType::getTypeInt())
{
    this->x=x;
addOperand(_srcVal1);
}
/// @brief 转换成字符串
/// @param str 转换后的字符串
void Move2Instruction::toString(std::string & str)
{

    
	Value *dstVal = getOperand(0);
    if (x == 1) {
		str = getIRName() + " = *" + dstVal->getIRName();
    } else
        
    str = getIRName() + " = " + dstVal->getIRName();
}
