///
/// @file PlatformArm32.h
/// @brief  ARM32平台相关头文件
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>新做
/// </table>
///
#pragma once

#include <string>

#include "../../ir/RegVariable.h"

// 在操作过程中临时借助的寄存器为ARM32_TMP_REG_NO
#define ARM32_TMP_REG_NO 10

// 栈寄存器SP和FP
#define ARM32_SP_REG_NO 13
#define ARM32_FP_REG_NO 11

// 函数跳转寄存器LX
#define ARM32_LX_REG_NO 14

/// @brief  ARM32平台相关类
class PlatformArm32 {
public:
    /// @brief ARM32平台最大寄存器数量
    static const int maxRegNum = 16;
    
    /// @brief ARM32平台可用寄存器数量
    static const int maxUsableRegNum = 8;  // r0-r7是我们可使用的寄存器

    /// @brief ARM32平台寄存器名称
    static const std::string regName[maxRegNum];
    
    /// @brief ARM32平台寄存器变量
    static RegVariable* intRegVal[maxRegNum];
    
    /// @brief 判断常数表达式是否合法
    /// @param num 常数值
    /// @return 是否合法
    static bool constExpr(int num);
    
    /// @brief 判断是否是合法的偏移
    /// @param num 偏移值
    /// @return 是否合法
    static bool isDisp(int num);
    
    /// @brief 判断是否是合法的寄存器名
    /// @param name 寄存器名
    /// @return 是否合法
    static bool isReg(std::string name);
};
