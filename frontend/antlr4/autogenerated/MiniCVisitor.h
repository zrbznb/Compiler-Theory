
// Generated from MiniC.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "MiniCParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MiniCParser.
 */
class  MiniCVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MiniCParser.
   */
    virtual std::any visitCompileUnit(MiniCParser::CompileUnitContext *context) = 0;

    virtual std::any visitFuncDef(MiniCParser::FuncDefContext *context) = 0;

    virtual std::any visitReturnType(MiniCParser::ReturnTypeContext *context) = 0;

    virtual std::any visitFormalParams(MiniCParser::FormalParamsContext *context) = 0;

    virtual std::any visitFormalParam(MiniCParser::FormalParamContext *context) = 0;

    virtual std::any visitBlock(MiniCParser::BlockContext *context) = 0;

    virtual std::any visitBlockItemList(MiniCParser::BlockItemListContext *context) = 0;

    virtual std::any visitBlockItem(MiniCParser::BlockItemContext *context) = 0;

    virtual std::any visitVarDecl(MiniCParser::VarDeclContext *context) = 0;

    virtual std::any visitBasicType(MiniCParser::BasicTypeContext *context) = 0;

    virtual std::any visitVarDef(MiniCParser::VarDefContext *context) = 0;

    virtual std::any visitReturnStatement(MiniCParser::ReturnStatementContext *context) = 0;

    virtual std::any visitAssignStatement(MiniCParser::AssignStatementContext *context) = 0;

    virtual std::any visitBlockStatement(MiniCParser::BlockStatementContext *context) = 0;

    virtual std::any visitExpressionStatement(MiniCParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitIfStatement(MiniCParser::IfStatementContext *context) = 0;

    virtual std::any visitWhileStatement(MiniCParser::WhileStatementContext *context) = 0;

    virtual std::any visitForStatement(MiniCParser::ForStatementContext *context) = 0;

    virtual std::any visitBreakStatement(MiniCParser::BreakStatementContext *context) = 0;

    virtual std::any visitContinueStatement(MiniCParser::ContinueStatementContext *context) = 0;

    virtual std::any visitExpr(MiniCParser::ExprContext *context) = 0;

    virtual std::any visitLogicOrExp(MiniCParser::LogicOrExpContext *context) = 0;

    virtual std::any visitLogicAndExp(MiniCParser::LogicAndExpContext *context) = 0;

    virtual std::any visitEqualityExp(MiniCParser::EqualityExpContext *context) = 0;

    virtual std::any visitEqualityOp(MiniCParser::EqualityOpContext *context) = 0;

    virtual std::any visitRelationalExp(MiniCParser::RelationalExpContext *context) = 0;

    virtual std::any visitRelationalOp(MiniCParser::RelationalOpContext *context) = 0;

    virtual std::any visitAddExp(MiniCParser::AddExpContext *context) = 0;

    virtual std::any visitAddOp(MiniCParser::AddOpContext *context) = 0;

    virtual std::any visitMulExp(MiniCParser::MulExpContext *context) = 0;

    virtual std::any visitMulOp(MiniCParser::MulOpContext *context) = 0;

    virtual std::any visitPrimaryUnaryExp(MiniCParser::PrimaryUnaryExpContext *context) = 0;

    virtual std::any visitNegativeUnaryExp(MiniCParser::NegativeUnaryExpContext *context) = 0;

    virtual std::any visitLogicalNotUnaryExp(MiniCParser::LogicalNotUnaryExpContext *context) = 0;

    virtual std::any visitFuncCallUnaryExp(MiniCParser::FuncCallUnaryExpContext *context) = 0;

    virtual std::any visitPrimaryExp(MiniCParser::PrimaryExpContext *context) = 0;

    virtual std::any visitRealParamList(MiniCParser::RealParamListContext *context) = 0;

    virtual std::any visitLVal(MiniCParser::LValContext *context) = 0;


};

