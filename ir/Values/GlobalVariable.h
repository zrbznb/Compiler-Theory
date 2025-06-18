///
/// @file GlobalVariable.h
/// @brief 全局变量类
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

#include "../GlobalValue.h"
#include "../Types/ArrayType.h"

/// @brief 全局变量类
class GlobalVariable : public GlobalValue {
public:
    /// @brief 构造函数
    /// @param _type 类型
    /// @param _name 变量名
    GlobalVariable(Type* _type, const std::string& _name = "")
        : GlobalValue(_type, _name), inBSSSection(true) {}

    /// @brief 检查是否是全局变量
    /// @return true 是全局变量
    /// @return false 不是全局变量
    bool isGlobalVarible() const override {
        return true;
    }

    /// @brief 检查全局变量是否在 BSS 段中
    /// @return true 在 BSS 段中
    /// @return false 不在 BSS 段中
    bool isInBSSSection() const {
        return inBSSSection;
    }
    
    /// @brief 设置全局变量是否在 BSS 段中
    /// @param inBSS 是否在 BSS 段中
    void setInBSSSection(bool inBSS) {
        inBSSSection = inBSS;
    }

    /// @brief 获取变量声明字符串表示
    /// @return 声明字符串
    std::string toDeclareString() const {
        std::string result ="declare "+ type->toString() + " " + getIRName();
        
        // 检查是否为数组类型
        if (type->isArrayType()) {

            for (auto & child: dimensions) {
				result += "[" + std::to_string(child) + "]";
			}
			
        }
        
        return result;
    }
    
    /// @brief 获取变量声明字符串表示并存储到参数中
    /// @param str 输出参数，用于存储结果
    void toDeclareString(std::string& str) const {
        str = toDeclareString();
    }

private:
    bool inBSSSection; // 标记变量是否在 BSS 段中
};
