///
/// @file ArrayType.cpp
/// @brief 数组类型实现
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

#include "ArrayType.h"

ArrayType::ArrayType(Type* _elementType)
    : elementType(_elementType)
{
    // 设置类型ID为数组类型
    ID = TypeID::ArrayTyID;
}

int32_t ArrayType::getSize() const
{
    // 返回基本元素类型的大小
    // 数组的总大小需要通过 Value 的维度信息来计算
    return elementType->getSize();
}

std::string ArrayType::toString() const
{
    // 只返回基本类型的字符串表示
    // 维度信息现在由 Value 类负责处理
    return elementType->toString() ;
}

ArrayType* ArrayType::getType(Type* elementType)
{
    return new ArrayType(elementType);
}
