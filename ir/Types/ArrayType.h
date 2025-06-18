///
/// @file ArrayType.h
/// @brief 数组类型定义
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

#include "Types/IntegerType.h"
#include "../Type.h"

/// @brief 数组类型
class ArrayType : public Type {
private:
    /// @brief 基本类型
    Type* elementType;
    
    /// @brief 私有构造函数，通过静态方法创建
    ArrayType(Type* _elementType);
    
public:
    /// @brief 获取数组元素类型
    /// @return 元素类型
    Type* getElementType() const { return elementType; }
    
    /// @brief 获取类型大小（基本元素类型的大小）
    /// @return 类型占用的字节数
    int32_t getSize() const override;
    
    /// @brief 获取字符串表示
    /// @return 类型的字符串表示
    std::string toString() const override;
    
    /// @brief 创建数组类型
    /// @param elementType 元素类型
    /// @return 数组类型指针
    static ArrayType* getType(Type* elementType);
};
