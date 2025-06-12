
// Generated from MiniC.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  MiniCParser : public antlr4::Parser {
public:
  enum {
    T_L_PAREN = 1, T_R_PAREN = 2, T_SEMICOLON = 3, T_L_BRACE = 4, T_R_BRACE = 5, 
    T_L_BRACKET = 6, T_R_BRACKET = 7, T_ASSIGN = 8, T_COMMA = 9, T_ADD = 10, 
    T_SUB = 11, T_MUL = 12, T_DIV = 13, T_MOD = 14, T_LT = 15, T_GT = 16, 
    T_LE = 17, T_GE = 18, T_EQ = 19, T_NEQ = 20, T_AND = 21, T_OR = 22, 
    T_NOT = 23, T_RETURN = 24, T_INT = 25, T_VOID = 26, T_IF = 27, T_ELSE = 28, 
    T_WHILE = 29, T_FOR = 30, T_BREAK = 31, T_CONTINUE = 32, T_ID = 33, 
    T_DIGIT = 34, WS = 35, SINGLE_LINE_COMMENT = 36, MULTI_LINE_COMMENT = 37
  };

  enum {
    RuleCompileUnit = 0, RuleFuncDef = 1, RuleReturnType = 2, RuleFormalParams = 3, 
    RuleFormalParam = 4, RuleBlock = 5, RuleBlockItemList = 6, RuleBlockItem = 7, 
    RuleVarDecl = 8, RuleBasicType = 9, RuleVarDef = 10, RuleStatement = 11, 
    RuleExpr = 12, RuleLogicOrExp = 13, RuleLogicAndExp = 14, RuleEqualityExp = 15, 
    RuleEqualityOp = 16, RuleRelationalExp = 17, RuleRelationalOp = 18, 
    RuleAddExp = 19, RuleAddOp = 20, RuleMulExp = 21, RuleMulOp = 22, RuleUnaryExp = 23, 
    RulePrimaryExp = 24, RuleRealParamList = 25, RuleLVal = 26
  };

  explicit MiniCParser(antlr4::TokenStream *input);

  MiniCParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~MiniCParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CompileUnitContext;
  class FuncDefContext;
  class ReturnTypeContext;
  class FormalParamsContext;
  class FormalParamContext;
  class BlockContext;
  class BlockItemListContext;
  class BlockItemContext;
  class VarDeclContext;
  class BasicTypeContext;
  class VarDefContext;
  class StatementContext;
  class ExprContext;
  class LogicOrExpContext;
  class LogicAndExpContext;
  class EqualityExpContext;
  class EqualityOpContext;
  class RelationalExpContext;
  class RelationalOpContext;
  class AddExpContext;
  class AddOpContext;
  class MulExpContext;
  class MulOpContext;
  class UnaryExpContext;
  class PrimaryExpContext;
  class RealParamListContext;
  class LValContext; 

  class  CompileUnitContext : public antlr4::ParserRuleContext {
  public:
    CompileUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<FuncDefContext *> funcDef();
    FuncDefContext* funcDef(size_t i);
    std::vector<VarDeclContext *> varDecl();
    VarDeclContext* varDecl(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompileUnitContext* compileUnit();

  class  FuncDefContext : public antlr4::ParserRuleContext {
  public:
    FuncDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ReturnTypeContext *returnType();
    antlr4::tree::TerminalNode *T_ID();
    antlr4::tree::TerminalNode *T_L_PAREN();
    antlr4::tree::TerminalNode *T_R_PAREN();
    BlockContext *block();
    FormalParamsContext *formalParams();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncDefContext* funcDef();

  class  ReturnTypeContext : public antlr4::ParserRuleContext {
  public:
    ReturnTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_INT();
    antlr4::tree::TerminalNode *T_VOID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnTypeContext* returnType();

  class  FormalParamsContext : public antlr4::ParserRuleContext {
  public:
    FormalParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FormalParamContext *> formalParam();
    FormalParamContext* formalParam(size_t i);
    std::vector<antlr4::tree::TerminalNode *> T_COMMA();
    antlr4::tree::TerminalNode* T_COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalParamsContext* formalParams();

  class  FormalParamContext : public antlr4::ParserRuleContext {
  public:
    FormalParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BasicTypeContext *basicType();
    antlr4::tree::TerminalNode *T_ID();
    std::vector<antlr4::tree::TerminalNode *> T_L_BRACKET();
    antlr4::tree::TerminalNode* T_L_BRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> T_R_BRACKET();
    antlr4::tree::TerminalNode* T_R_BRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> T_DIGIT();
    antlr4::tree::TerminalNode* T_DIGIT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalParamContext* formalParam();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_L_BRACE();
    antlr4::tree::TerminalNode *T_R_BRACE();
    BlockItemListContext *blockItemList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  BlockItemListContext : public antlr4::ParserRuleContext {
  public:
    BlockItemListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BlockItemContext *> blockItem();
    BlockItemContext* blockItem(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockItemListContext* blockItemList();

  class  BlockItemContext : public antlr4::ParserRuleContext {
  public:
    BlockItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    VarDeclContext *varDecl();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockItemContext* blockItem();

  class  VarDeclContext : public antlr4::ParserRuleContext {
  public:
    VarDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BasicTypeContext *basicType();
    std::vector<VarDefContext *> varDef();
    VarDefContext* varDef(size_t i);
    antlr4::tree::TerminalNode *T_SEMICOLON();
    std::vector<antlr4::tree::TerminalNode *> T_COMMA();
    antlr4::tree::TerminalNode* T_COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDeclContext* varDecl();

  class  BasicTypeContext : public antlr4::ParserRuleContext {
  public:
    BasicTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_INT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BasicTypeContext* basicType();

  class  VarDefContext : public antlr4::ParserRuleContext {
  public:
    VarDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_ID();
    std::vector<antlr4::tree::TerminalNode *> T_L_BRACKET();
    antlr4::tree::TerminalNode* T_L_BRACKET(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> T_R_BRACKET();
    antlr4::tree::TerminalNode* T_R_BRACKET(size_t i);
    antlr4::tree::TerminalNode *T_ASSIGN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDefContext* varDef();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  WhileStatementContext : public StatementContext {
  public:
    WhileStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *T_WHILE();
    antlr4::tree::TerminalNode *T_L_PAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *T_R_PAREN();
    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockStatementContext : public StatementContext {
  public:
    BlockStatementContext(StatementContext *ctx);

    BlockContext *block();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignStatementContext : public StatementContext {
  public:
    AssignStatementContext(StatementContext *ctx);

    LValContext *lVal();
    antlr4::tree::TerminalNode *T_ASSIGN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *T_SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ForStatementContext : public StatementContext {
  public:
    ForStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *T_FOR();
    antlr4::tree::TerminalNode *T_L_PAREN();
    std::vector<antlr4::tree::TerminalNode *> T_SEMICOLON();
    antlr4::tree::TerminalNode* T_SEMICOLON(size_t i);
    antlr4::tree::TerminalNode *T_R_PAREN();
    StatementContext *statement();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    VarDeclContext *varDecl();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BreakStatementContext : public StatementContext {
  public:
    BreakStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *T_BREAK();
    antlr4::tree::TerminalNode *T_SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExpressionStatementContext : public StatementContext {
  public:
    ExpressionStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *T_SEMICOLON();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ContinueStatementContext : public StatementContext {
  public:
    ContinueStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *T_CONTINUE();
    antlr4::tree::TerminalNode *T_SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReturnStatementContext : public StatementContext {
  public:
    ReturnStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *T_RETURN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *T_SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfStatementContext : public StatementContext {
  public:
    IfStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *T_IF();
    antlr4::tree::TerminalNode *T_L_PAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *T_R_PAREN();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *T_ELSE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatementContext* statement();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicOrExpContext *logicOrExp();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();

  class  LogicOrExpContext : public antlr4::ParserRuleContext {
  public:
    LogicOrExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LogicAndExpContext *> logicAndExp();
    LogicAndExpContext* logicAndExp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> T_OR();
    antlr4::tree::TerminalNode* T_OR(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicOrExpContext* logicOrExp();

  class  LogicAndExpContext : public antlr4::ParserRuleContext {
  public:
    LogicAndExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EqualityExpContext *> equalityExp();
    EqualityExpContext* equalityExp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> T_AND();
    antlr4::tree::TerminalNode* T_AND(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicAndExpContext* logicAndExp();

  class  EqualityExpContext : public antlr4::ParserRuleContext {
  public:
    EqualityExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RelationalExpContext *> relationalExp();
    RelationalExpContext* relationalExp(size_t i);
    std::vector<EqualityOpContext *> equalityOp();
    EqualityOpContext* equalityOp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqualityExpContext* equalityExp();

  class  EqualityOpContext : public antlr4::ParserRuleContext {
  public:
    EqualityOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_EQ();
    antlr4::tree::TerminalNode *T_NEQ();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqualityOpContext* equalityOp();

  class  RelationalExpContext : public antlr4::ParserRuleContext {
  public:
    RelationalExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AddExpContext *> addExp();
    AddExpContext* addExp(size_t i);
    std::vector<RelationalOpContext *> relationalOp();
    RelationalOpContext* relationalOp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelationalExpContext* relationalExp();

  class  RelationalOpContext : public antlr4::ParserRuleContext {
  public:
    RelationalOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_LT();
    antlr4::tree::TerminalNode *T_GT();
    antlr4::tree::TerminalNode *T_LE();
    antlr4::tree::TerminalNode *T_GE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelationalOpContext* relationalOp();

  class  AddExpContext : public antlr4::ParserRuleContext {
  public:
    AddExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MulExpContext *> mulExp();
    MulExpContext* mulExp(size_t i);
    std::vector<AddOpContext *> addOp();
    AddOpContext* addOp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AddExpContext* addExp();

  class  AddOpContext : public antlr4::ParserRuleContext {
  public:
    AddOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_ADD();
    antlr4::tree::TerminalNode *T_SUB();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AddOpContext* addOp();

  class  MulExpContext : public antlr4::ParserRuleContext {
  public:
    MulExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExpContext *> unaryExp();
    UnaryExpContext* unaryExp(size_t i);
    std::vector<MulOpContext *> mulOp();
    MulOpContext* mulOp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MulExpContext* mulExp();

  class  MulOpContext : public antlr4::ParserRuleContext {
  public:
    MulOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_MUL();
    antlr4::tree::TerminalNode *T_DIV();
    antlr4::tree::TerminalNode *T_MOD();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MulOpContext* mulOp();

  class  UnaryExpContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryExpContext() = default;
    void copyFrom(UnaryExpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LogicalNotUnaryExpContext : public UnaryExpContext {
  public:
    LogicalNotUnaryExpContext(UnaryExpContext *ctx);

    antlr4::tree::TerminalNode *T_NOT();
    UnaryExpContext *unaryExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FuncCallUnaryExpContext : public UnaryExpContext {
  public:
    FuncCallUnaryExpContext(UnaryExpContext *ctx);

    antlr4::tree::TerminalNode *T_ID();
    antlr4::tree::TerminalNode *T_L_PAREN();
    antlr4::tree::TerminalNode *T_R_PAREN();
    RealParamListContext *realParamList();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PrimaryUnaryExpContext : public UnaryExpContext {
  public:
    PrimaryUnaryExpContext(UnaryExpContext *ctx);

    PrimaryExpContext *primaryExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NegativeUnaryExpContext : public UnaryExpContext {
  public:
    NegativeUnaryExpContext(UnaryExpContext *ctx);

    antlr4::tree::TerminalNode *T_SUB();
    UnaryExpContext *unaryExp();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryExpContext* unaryExp();

  class  PrimaryExpContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_L_PAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *T_R_PAREN();
    antlr4::tree::TerminalNode *T_DIGIT();
    LValContext *lVal();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExpContext* primaryExp();

  class  RealParamListContext : public antlr4::ParserRuleContext {
  public:
    RealParamListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> T_COMMA();
    antlr4::tree::TerminalNode* T_COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RealParamListContext* realParamList();

  class  LValContext : public antlr4::ParserRuleContext {
  public:
    LValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *T_ID();
    std::vector<antlr4::tree::TerminalNode *> T_L_BRACKET();
    antlr4::tree::TerminalNode* T_L_BRACKET(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> T_R_BRACKET();
    antlr4::tree::TerminalNode* T_R_BRACKET(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LValContext* lVal();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

