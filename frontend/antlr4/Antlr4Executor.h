///
/// @file Antlr4Executor.h
/// @brief antlr4的词法与语法分析解析器
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

#include <vector>
#include "FrontEndExecutor.h"
#include "AttrType.h"

class Antlr4Executor : public FrontEndExecutor {
public:
    Antlr4Executor(std::string filename) : FrontEndExecutor(filename)
    {}
    
    virtual ~Antlr4Executor()
    {}

    /// @brief 前端词法与语法解析生成AST
    /// @return true: 成功 false：错误
    bool run() override;
    
private:
    /// @brief 添加内置库函数到AST
    void addBuiltinFunctions();
    
    /// @brief 添加内置库函数
    /// @param name 函数名
    /// @param returnType 返回类型
    /// @param paramTypes 参数类型列表
    void addBuiltinFunction(const std::string& name, BasicType returnType, 
                         const std::vector<BasicType>& paramTypes);
};
