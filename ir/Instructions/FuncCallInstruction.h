///
/// @file FuncCallInstruction.h
/// @brief 函数调用指令
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
#pragma once

#include "Instruction.h"
#include "Function.h"

///
/// @brief 函数调用指令
///
class FuncCallInstruction : public Instruction {

public:
    ///
    /// @brief 构造函数
    /// @param _func 调用函数的父函数
    /// @param _callee 被调用的函数
    /// @param _args 函数参数列表
    /// @param _returnType 返回值类型
    ///
    FuncCallInstruction(Function * _func, Function * _callee, 
                      std::vector<Value *>& _args, Type * _returnType);

    ///
    /// @brief 转换成IR指令字符串
    ///
    void toString(std::string & str) override;
    
    ///
    /// @brief 获取被调用函数
    /// @return 被调用函数
    ///
    Function* getCallee() const { return callee; }
    
    ///
    /// @brief 获取参数列表
    /// @return 参数列表
    ///
    const std::vector<Value*>& getArgs() const { return args; }

private:
    ///
    /// @brief 被调用的函数
    ///
    Function* callee;
    
    ///
    /// @brief 参数列表
    ///
    std::vector<Value*> args;
};
