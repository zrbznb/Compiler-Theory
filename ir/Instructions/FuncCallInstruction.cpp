///
/// @file FuncCallInstruction.cpp
/// @brief 函数调用指令实现
///
/// @author zenglj (zenglj@live.com)
/// @version 1.1
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// <tr><td>2024-12-05 <td>1.1     <td>student <td>支持多参数函数调用
/// </table>
///
#include <string>
#include "FuncCallInstruction.h"
#include "VoidType.h"

/// @brief 函数调用指令构造函数
/// @param _func 调用函数的父函数 
/// @param _callee 被调用的函数
/// @param _args 函数参数列表
/// @param _returnType 返回值类型
FuncCallInstruction::FuncCallInstruction(Function * _func, Function * _callee, 
                                     std::vector<Value *>& _args, Type * _returnType)
    : Instruction(_func, IRInstOperator::IRINST_OP_FUNC_CALL, _returnType), 
      callee(_callee), args(_args)
{
    // 将所有参数作为操作数添加到指令中
    for (auto& arg : args) {
        this->addOperand(arg);
    }
}

/// @brief 转换成字符串
void FuncCallInstruction::toString(std::string & str)
{
    // 如果有返回值，生成赋值语句
    if (!type->isVoidType()) {
        str = getIRName() + " = ";
    } else {
        str = "";
    }
    
    // 添加函数名和参数列表
    str += "call " +callee->getType()->toString()+ " "+callee->getIRName() + "(";
    
    // 添加所有参数
    for (size_t i = 0; i < args.size(); i++) {
        if (i > 0) {
            str += ", ";
        }
        str += args[i]->getType()->toString()+' ' +args[i]->getIRName();
    }
    str += ")";
    
    // 添加调试信息
    if (getRegId() != -1) {
        str += " ; " + std::to_string(getRegId());
    }
}
