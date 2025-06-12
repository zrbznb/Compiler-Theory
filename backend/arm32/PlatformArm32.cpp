///
/// @file PlatformArm32.cpp
/// @brief  ARM32平台相关实现
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
#include "PlatformArm32.h"

#include "../../ir/RegVariable.h"

// 修复静态数组定义
const std::string PlatformArm32::regName[PlatformArm32::maxRegNum] = {
    "r0",  // 用于传参或返回值等，不需要栈保护
    "r1",  // 用于传参或返回值（64位结果时后32位）等，不需要栈保护
    "r2",  // 用于传参等，不需要栈保护
    "r3",  // 用于传参等，不需要栈保护
    "r4",  // 需要栈保护
    "r5",  // 需要栈保护
    "r6",  // 需要栈保护
    "r7",  // 需要栈保护
    "r8",  // 用于加载操作数1,保存表达式结果
    "r9",  // 用于加载操作数2,写回表达式结果,立即数，标签地址
    "r10", // 用于保存乘法结果
    "fp",  // r11,局部变量寻址
    "ip",  // r12，临时寄存器
    "sp",  // r13，堆栈指针寄存器
    "lr",  // r14，链接寄存器
    "pc"   // r15，程序计数器
};

// 初始化寄存器变量数组
RegVariable* PlatformArm32::intRegVal[PlatformArm32::maxRegNum] = {
    new RegVariable(0),  // r0
    new RegVariable(1),  // r1
    new RegVariable(2),  // r2
    new RegVariable(3),  // r3
    new RegVariable(4),  // r4
    new RegVariable(5),  // r5
    new RegVariable(6),  // r6
    new RegVariable(7),  // r7
    new RegVariable(8),  // r8
    new RegVariable(9),  // r9
    new RegVariable(10), // r10
    new RegVariable(11), // r11/fp
    new RegVariable(12), // r12/ip
    new RegVariable(13), // r13/sp
    new RegVariable(14), // r14/lr
    new RegVariable(15)  // r15/pc
};

/// @brief 判断常数表达式是否合法
bool PlatformArm32::constExpr(int num)
{
    // 简化实现：0-255 之间的值是合法的常数表达式
    return num >= 0 && num <= 255;
}

/// @brief 判断是否是合法的偏移
bool PlatformArm32::isDisp(int num)
{
    return (num >= -4095) && (num <= 4095);
}

/// @brief 判断是否是合法的寄存器名
bool PlatformArm32::isReg(std::string name)
{
    for (int i = 0; i < maxRegNum; i++) {
        if (name == regName[i]) {
            return true;
        }
    }
    return false;
}
