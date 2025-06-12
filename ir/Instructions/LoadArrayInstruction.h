///
/// @file LoadArrayInstruction.h
/// @brief 从数组加载值指令
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

#pragma once

#include "Instruction.h"

/// @brief 从数组加载值指令
class LoadArrayInstruction : public Instruction {
public:
    /// @brief 构造函数
    /// @param _func 所属函数
    /// @param _arrayPtr 数组元素指针（由ArrayAccessInstruction生成）
    /// @param _elementType 元素类型
    LoadArrayInstruction(Function* _func, Value* _arrayPtr, Type* _elementType);

    /// @brief 转换成字符串
    void toString(std::string& str) override;
};
