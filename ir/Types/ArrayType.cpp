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
#include <numeric>
#include <functional>

ArrayType::ArrayType(Type* _elementType, const std::vector<int>& _dimensions)
    : elementType(_elementType), dimensions(_dimensions)
{
    // 设置类型ID为数组类型
    ID = TypeID::ArrayTyID;
}

int32_t ArrayType::getSize() const
{
    // 计算数组总大小：元素类型大小 * 总元素数量
    return elementType->getSize() * getTotalElements();
}

int ArrayType::getTotalElements() const
{
    // 如果数组是形参（第一维为0），则只返回指针大小
    if (!dimensions.empty() && dimensions[0] == 0) {
        return 4;  // 指针大小，ARM32架构为4字节
    }
    
    // 计算所有维度的乘积
    return std::accumulate(dimensions.begin(), dimensions.end(), 1, std::multiplies<int>());
}

std::string ArrayType::toString() const
{
    std::string result = elementType->toString();
    
    for (int dim : dimensions) {
        result += "[" + std::to_string(dim) + "]";
    }
    
    return result;
}

ArrayType* ArrayType::getType(Type* elementType, const std::vector<int>& dimensions)
{
    return new ArrayType(elementType, dimensions);
}
