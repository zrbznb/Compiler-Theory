
// Generated from MiniC.g4 by ANTLR 4.12.0


#include "MiniCVisitor.h"

#include "MiniCParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MiniCParserStaticData final {
  MiniCParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MiniCParserStaticData(const MiniCParserStaticData&) = delete;
  MiniCParserStaticData(MiniCParserStaticData&&) = delete;
  MiniCParserStaticData& operator=(const MiniCParserStaticData&) = delete;
  MiniCParserStaticData& operator=(MiniCParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag minicParserOnceFlag;
MiniCParserStaticData *minicParserStaticData = nullptr;

void minicParserInitialize() {
  assert(minicParserStaticData == nullptr);
  auto staticData = std::make_unique<MiniCParserStaticData>(
    std::vector<std::string>{
      "compileUnit", "funcDef", "returnType", "formalParams", "formalParam", 
      "block", "blockItemList", "blockItem", "varDecl", "basicType", "varDef", 
      "statement", "expr", "logicOrExp", "logicAndExp", "equalityExp", "equalityOp", 
      "relationalExp", "relationalOp", "addExp", "addOp", "mulExp", "mulOp", 
      "unaryExp", "primaryExp", "realParamList", "lVal"
    },
    std::vector<std::string>{
      "", "'('", "')'", "';'", "'{'", "'}'", "'['", "']'", "'='", "','", 
      "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "'<='", "'>='", "'=='", 
      "'!='", "'&&'", "'||'", "'!'", "'return'", "'int'", "'void'", "'if'", 
      "'else'", "'while'", "'for'", "'break'", "'continue'"
    },
    std::vector<std::string>{
      "", "T_L_PAREN", "T_R_PAREN", "T_SEMICOLON", "T_L_BRACE", "T_R_BRACE", 
      "T_L_BRACKET", "T_R_BRACKET", "T_ASSIGN", "T_COMMA", "T_ADD", "T_SUB", 
      "T_MUL", "T_DIV", "T_MOD", "T_LT", "T_GT", "T_LE", "T_GE", "T_EQ", 
      "T_NEQ", "T_AND", "T_OR", "T_NOT", "T_RETURN", "T_INT", "T_VOID", 
      "T_IF", "T_ELSE", "T_WHILE", "T_FOR", "T_BREAK", "T_CONTINUE", "T_ID", 
      "T_DIGIT", "WS", "SINGLE_LINE_COMMENT", "MULTI_LINE_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,37,291,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,1,0,1,0,5,0,57,8,
  	0,10,0,12,0,60,9,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,68,8,1,1,1,1,1,1,1,1,2,
  	1,2,1,3,1,3,1,3,5,3,78,8,3,10,3,12,3,81,9,3,1,4,1,4,1,4,1,4,1,4,1,4,1,
  	4,5,4,90,8,4,10,4,12,4,93,9,4,3,4,95,8,4,1,5,1,5,3,5,99,8,5,1,5,1,5,1,
  	6,4,6,104,8,6,11,6,12,6,105,1,7,1,7,3,7,110,8,7,1,8,1,8,1,8,1,8,5,8,116,
  	8,8,10,8,12,8,119,9,8,1,8,1,8,1,9,1,9,1,10,1,10,1,10,1,10,1,10,5,10,130,
  	8,10,10,10,12,10,133,9,10,1,10,1,10,3,10,137,8,10,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,150,8,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,3,11,160,8,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,3,11,172,8,11,1,11,1,11,3,11,176,8,11,1,11,1,11,3,11,180,
  	8,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,188,8,11,1,12,1,12,1,13,1,13,
  	1,13,5,13,195,8,13,10,13,12,13,198,9,13,1,14,1,14,1,14,5,14,203,8,14,
  	10,14,12,14,206,9,14,1,15,1,15,1,15,1,15,5,15,212,8,15,10,15,12,15,215,
  	9,15,1,16,1,16,1,17,1,17,1,17,1,17,5,17,223,8,17,10,17,12,17,226,9,17,
  	1,18,1,18,1,19,1,19,1,19,1,19,5,19,234,8,19,10,19,12,19,237,9,19,1,20,
  	1,20,1,21,1,21,1,21,1,21,5,21,245,8,21,10,21,12,21,248,9,21,1,22,1,22,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,260,8,23,1,23,3,23,263,8,
  	23,1,24,1,24,1,24,1,24,1,24,1,24,3,24,271,8,24,1,25,1,25,1,25,5,25,276,
  	8,25,10,25,12,25,279,9,25,1,26,1,26,1,26,1,26,1,26,5,26,286,8,26,10,26,
  	12,26,289,9,26,1,26,0,0,27,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
  	32,34,36,38,40,42,44,46,48,50,52,0,5,1,0,25,26,1,0,19,20,1,0,15,18,1,
  	0,10,11,1,0,12,14,303,0,58,1,0,0,0,2,63,1,0,0,0,4,72,1,0,0,0,6,74,1,0,
  	0,0,8,82,1,0,0,0,10,96,1,0,0,0,12,103,1,0,0,0,14,109,1,0,0,0,16,111,1,
  	0,0,0,18,122,1,0,0,0,20,124,1,0,0,0,22,187,1,0,0,0,24,189,1,0,0,0,26,
  	191,1,0,0,0,28,199,1,0,0,0,30,207,1,0,0,0,32,216,1,0,0,0,34,218,1,0,0,
  	0,36,227,1,0,0,0,38,229,1,0,0,0,40,238,1,0,0,0,42,240,1,0,0,0,44,249,
  	1,0,0,0,46,262,1,0,0,0,48,270,1,0,0,0,50,272,1,0,0,0,52,280,1,0,0,0,54,
  	57,3,2,1,0,55,57,3,16,8,0,56,54,1,0,0,0,56,55,1,0,0,0,57,60,1,0,0,0,58,
  	56,1,0,0,0,58,59,1,0,0,0,59,61,1,0,0,0,60,58,1,0,0,0,61,62,5,0,0,1,62,
  	1,1,0,0,0,63,64,3,4,2,0,64,65,5,33,0,0,65,67,5,1,0,0,66,68,3,6,3,0,67,
  	66,1,0,0,0,67,68,1,0,0,0,68,69,1,0,0,0,69,70,5,2,0,0,70,71,3,10,5,0,71,
  	3,1,0,0,0,72,73,7,0,0,0,73,5,1,0,0,0,74,79,3,8,4,0,75,76,5,9,0,0,76,78,
  	3,8,4,0,77,75,1,0,0,0,78,81,1,0,0,0,79,77,1,0,0,0,79,80,1,0,0,0,80,7,
  	1,0,0,0,81,79,1,0,0,0,82,83,3,18,9,0,83,94,5,33,0,0,84,85,5,6,0,0,85,
  	91,5,7,0,0,86,87,5,6,0,0,87,88,5,34,0,0,88,90,5,7,0,0,89,86,1,0,0,0,90,
  	93,1,0,0,0,91,89,1,0,0,0,91,92,1,0,0,0,92,95,1,0,0,0,93,91,1,0,0,0,94,
  	84,1,0,0,0,94,95,1,0,0,0,95,9,1,0,0,0,96,98,5,4,0,0,97,99,3,12,6,0,98,
  	97,1,0,0,0,98,99,1,0,0,0,99,100,1,0,0,0,100,101,5,5,0,0,101,11,1,0,0,
  	0,102,104,3,14,7,0,103,102,1,0,0,0,104,105,1,0,0,0,105,103,1,0,0,0,105,
  	106,1,0,0,0,106,13,1,0,0,0,107,110,3,22,11,0,108,110,3,16,8,0,109,107,
  	1,0,0,0,109,108,1,0,0,0,110,15,1,0,0,0,111,112,3,18,9,0,112,117,3,20,
  	10,0,113,114,5,9,0,0,114,116,3,20,10,0,115,113,1,0,0,0,116,119,1,0,0,
  	0,117,115,1,0,0,0,117,118,1,0,0,0,118,120,1,0,0,0,119,117,1,0,0,0,120,
  	121,5,3,0,0,121,17,1,0,0,0,122,123,5,25,0,0,123,19,1,0,0,0,124,131,5,
  	33,0,0,125,126,5,6,0,0,126,127,3,24,12,0,127,128,5,7,0,0,128,130,1,0,
  	0,0,129,125,1,0,0,0,130,133,1,0,0,0,131,129,1,0,0,0,131,132,1,0,0,0,132,
  	136,1,0,0,0,133,131,1,0,0,0,134,135,5,8,0,0,135,137,3,24,12,0,136,134,
  	1,0,0,0,136,137,1,0,0,0,137,21,1,0,0,0,138,139,5,24,0,0,139,140,3,24,
  	12,0,140,141,5,3,0,0,141,188,1,0,0,0,142,143,3,52,26,0,143,144,5,8,0,
  	0,144,145,3,24,12,0,145,146,5,3,0,0,146,188,1,0,0,0,147,188,3,10,5,0,
  	148,150,3,24,12,0,149,148,1,0,0,0,149,150,1,0,0,0,150,151,1,0,0,0,151,
  	188,5,3,0,0,152,153,5,27,0,0,153,154,5,1,0,0,154,155,3,24,12,0,155,156,
  	5,2,0,0,156,159,3,22,11,0,157,158,5,28,0,0,158,160,3,22,11,0,159,157,
  	1,0,0,0,159,160,1,0,0,0,160,188,1,0,0,0,161,162,5,29,0,0,162,163,5,1,
  	0,0,163,164,3,24,12,0,164,165,5,2,0,0,165,166,3,22,11,0,166,188,1,0,0,
  	0,167,168,5,30,0,0,168,171,5,1,0,0,169,172,3,24,12,0,170,172,3,16,8,0,
  	171,169,1,0,0,0,171,170,1,0,0,0,171,172,1,0,0,0,172,173,1,0,0,0,173,175,
  	5,3,0,0,174,176,3,24,12,0,175,174,1,0,0,0,175,176,1,0,0,0,176,177,1,0,
  	0,0,177,179,5,3,0,0,178,180,3,24,12,0,179,178,1,0,0,0,179,180,1,0,0,0,
  	180,181,1,0,0,0,181,182,5,2,0,0,182,188,3,22,11,0,183,184,5,31,0,0,184,
  	188,5,3,0,0,185,186,5,32,0,0,186,188,5,3,0,0,187,138,1,0,0,0,187,142,
  	1,0,0,0,187,147,1,0,0,0,187,149,1,0,0,0,187,152,1,0,0,0,187,161,1,0,0,
  	0,187,167,1,0,0,0,187,183,1,0,0,0,187,185,1,0,0,0,188,23,1,0,0,0,189,
  	190,3,26,13,0,190,25,1,0,0,0,191,196,3,28,14,0,192,193,5,22,0,0,193,195,
  	3,28,14,0,194,192,1,0,0,0,195,198,1,0,0,0,196,194,1,0,0,0,196,197,1,0,
  	0,0,197,27,1,0,0,0,198,196,1,0,0,0,199,204,3,30,15,0,200,201,5,21,0,0,
  	201,203,3,30,15,0,202,200,1,0,0,0,203,206,1,0,0,0,204,202,1,0,0,0,204,
  	205,1,0,0,0,205,29,1,0,0,0,206,204,1,0,0,0,207,213,3,34,17,0,208,209,
  	3,32,16,0,209,210,3,34,17,0,210,212,1,0,0,0,211,208,1,0,0,0,212,215,1,
  	0,0,0,213,211,1,0,0,0,213,214,1,0,0,0,214,31,1,0,0,0,215,213,1,0,0,0,
  	216,217,7,1,0,0,217,33,1,0,0,0,218,224,3,38,19,0,219,220,3,36,18,0,220,
  	221,3,38,19,0,221,223,1,0,0,0,222,219,1,0,0,0,223,226,1,0,0,0,224,222,
  	1,0,0,0,224,225,1,0,0,0,225,35,1,0,0,0,226,224,1,0,0,0,227,228,7,2,0,
  	0,228,37,1,0,0,0,229,235,3,42,21,0,230,231,3,40,20,0,231,232,3,42,21,
  	0,232,234,1,0,0,0,233,230,1,0,0,0,234,237,1,0,0,0,235,233,1,0,0,0,235,
  	236,1,0,0,0,236,39,1,0,0,0,237,235,1,0,0,0,238,239,7,3,0,0,239,41,1,0,
  	0,0,240,246,3,46,23,0,241,242,3,44,22,0,242,243,3,46,23,0,243,245,1,0,
  	0,0,244,241,1,0,0,0,245,248,1,0,0,0,246,244,1,0,0,0,246,247,1,0,0,0,247,
  	43,1,0,0,0,248,246,1,0,0,0,249,250,7,4,0,0,250,45,1,0,0,0,251,263,3,48,
  	24,0,252,253,5,11,0,0,253,263,3,46,23,0,254,255,5,23,0,0,255,263,3,46,
  	23,0,256,257,5,33,0,0,257,259,5,1,0,0,258,260,3,50,25,0,259,258,1,0,0,
  	0,259,260,1,0,0,0,260,261,1,0,0,0,261,263,5,2,0,0,262,251,1,0,0,0,262,
  	252,1,0,0,0,262,254,1,0,0,0,262,256,1,0,0,0,263,47,1,0,0,0,264,265,5,
  	1,0,0,265,266,3,24,12,0,266,267,5,2,0,0,267,271,1,0,0,0,268,271,5,34,
  	0,0,269,271,3,52,26,0,270,264,1,0,0,0,270,268,1,0,0,0,270,269,1,0,0,0,
  	271,49,1,0,0,0,272,277,3,24,12,0,273,274,5,9,0,0,274,276,3,24,12,0,275,
  	273,1,0,0,0,276,279,1,0,0,0,277,275,1,0,0,0,277,278,1,0,0,0,278,51,1,
  	0,0,0,279,277,1,0,0,0,280,287,5,33,0,0,281,282,5,6,0,0,282,283,3,24,12,
  	0,283,284,5,7,0,0,284,286,1,0,0,0,285,281,1,0,0,0,286,289,1,0,0,0,287,
  	285,1,0,0,0,287,288,1,0,0,0,288,53,1,0,0,0,289,287,1,0,0,0,29,56,58,67,
  	79,91,94,98,105,109,117,131,136,149,159,171,175,179,187,196,204,213,224,
  	235,246,259,262,270,277,287
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  minicParserStaticData = staticData.release();
}

}

MiniCParser::MiniCParser(TokenStream *input) : MiniCParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MiniCParser::MiniCParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MiniCParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *minicParserStaticData->atn, minicParserStaticData->decisionToDFA, minicParserStaticData->sharedContextCache, options);
}

MiniCParser::~MiniCParser() {
  delete _interpreter;
}

const atn::ATN& MiniCParser::getATN() const {
  return *minicParserStaticData->atn;
}

std::string MiniCParser::getGrammarFileName() const {
  return "MiniC.g4";
}

const std::vector<std::string>& MiniCParser::getRuleNames() const {
  return minicParserStaticData->ruleNames;
}

const dfa::Vocabulary& MiniCParser::getVocabulary() const {
  return minicParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MiniCParser::getSerializedATN() const {
  return minicParserStaticData->serializedATN;
}


//----------------- CompileUnitContext ------------------------------------------------------------------

MiniCParser::CompileUnitContext::CompileUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::CompileUnitContext::EOF() {
  return getToken(MiniCParser::EOF, 0);
}

std::vector<MiniCParser::FuncDefContext *> MiniCParser::CompileUnitContext::funcDef() {
  return getRuleContexts<MiniCParser::FuncDefContext>();
}

MiniCParser::FuncDefContext* MiniCParser::CompileUnitContext::funcDef(size_t i) {
  return getRuleContext<MiniCParser::FuncDefContext>(i);
}

std::vector<MiniCParser::VarDeclContext *> MiniCParser::CompileUnitContext::varDecl() {
  return getRuleContexts<MiniCParser::VarDeclContext>();
}

MiniCParser::VarDeclContext* MiniCParser::CompileUnitContext::varDecl(size_t i) {
  return getRuleContext<MiniCParser::VarDeclContext>(i);
}


size_t MiniCParser::CompileUnitContext::getRuleIndex() const {
  return MiniCParser::RuleCompileUnit;
}


std::any MiniCParser::CompileUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitCompileUnit(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::CompileUnitContext* MiniCParser::compileUnit() {
  CompileUnitContext *_localctx = _tracker.createInstance<CompileUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, MiniCParser::RuleCompileUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_INT

    || _la == MiniCParser::T_VOID) {
      setState(56);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(54);
        funcDef();
        break;
      }

      case 2: {
        setState(55);
        varDecl();
        break;
      }

      default:
        break;
      }
      setState(60);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(61);
    match(MiniCParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

MiniCParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::ReturnTypeContext* MiniCParser::FuncDefContext::returnType() {
  return getRuleContext<MiniCParser::ReturnTypeContext>(0);
}

tree::TerminalNode* MiniCParser::FuncDefContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

tree::TerminalNode* MiniCParser::FuncDefContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

tree::TerminalNode* MiniCParser::FuncDefContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

MiniCParser::BlockContext* MiniCParser::FuncDefContext::block() {
  return getRuleContext<MiniCParser::BlockContext>(0);
}

MiniCParser::FormalParamsContext* MiniCParser::FuncDefContext::formalParams() {
  return getRuleContext<MiniCParser::FormalParamsContext>(0);
}


size_t MiniCParser::FuncDefContext::getRuleIndex() const {
  return MiniCParser::RuleFuncDef;
}


std::any MiniCParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::FuncDefContext* MiniCParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 2, MiniCParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    returnType();
    setState(64);
    match(MiniCParser::T_ID);
    setState(65);
    match(MiniCParser::T_L_PAREN);
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T_INT) {
      setState(66);
      formalParams();
    }
    setState(69);
    match(MiniCParser::T_R_PAREN);
    setState(70);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnTypeContext ------------------------------------------------------------------

MiniCParser::ReturnTypeContext::ReturnTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::ReturnTypeContext::T_INT() {
  return getToken(MiniCParser::T_INT, 0);
}

tree::TerminalNode* MiniCParser::ReturnTypeContext::T_VOID() {
  return getToken(MiniCParser::T_VOID, 0);
}


size_t MiniCParser::ReturnTypeContext::getRuleIndex() const {
  return MiniCParser::RuleReturnType;
}


std::any MiniCParser::ReturnTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitReturnType(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ReturnTypeContext* MiniCParser::returnType() {
  ReturnTypeContext *_localctx = _tracker.createInstance<ReturnTypeContext>(_ctx, getState());
  enterRule(_localctx, 4, MiniCParser::RuleReturnType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    _la = _input->LA(1);
    if (!(_la == MiniCParser::T_INT

    || _la == MiniCParser::T_VOID)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParamsContext ------------------------------------------------------------------

MiniCParser::FormalParamsContext::FormalParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::FormalParamContext *> MiniCParser::FormalParamsContext::formalParam() {
  return getRuleContexts<MiniCParser::FormalParamContext>();
}

MiniCParser::FormalParamContext* MiniCParser::FormalParamsContext::formalParam(size_t i) {
  return getRuleContext<MiniCParser::FormalParamContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::FormalParamsContext::T_COMMA() {
  return getTokens(MiniCParser::T_COMMA);
}

tree::TerminalNode* MiniCParser::FormalParamsContext::T_COMMA(size_t i) {
  return getToken(MiniCParser::T_COMMA, i);
}


size_t MiniCParser::FormalParamsContext::getRuleIndex() const {
  return MiniCParser::RuleFormalParams;
}


std::any MiniCParser::FormalParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFormalParams(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::FormalParamsContext* MiniCParser::formalParams() {
  FormalParamsContext *_localctx = _tracker.createInstance<FormalParamsContext>(_ctx, getState());
  enterRule(_localctx, 6, MiniCParser::RuleFormalParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    formalParam();
    setState(79);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_COMMA) {
      setState(75);
      match(MiniCParser::T_COMMA);
      setState(76);
      formalParam();
      setState(81);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParamContext ------------------------------------------------------------------

MiniCParser::FormalParamContext::FormalParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::BasicTypeContext* MiniCParser::FormalParamContext::basicType() {
  return getRuleContext<MiniCParser::BasicTypeContext>(0);
}

tree::TerminalNode* MiniCParser::FormalParamContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

std::vector<tree::TerminalNode *> MiniCParser::FormalParamContext::T_L_BRACKET() {
  return getTokens(MiniCParser::T_L_BRACKET);
}

tree::TerminalNode* MiniCParser::FormalParamContext::T_L_BRACKET(size_t i) {
  return getToken(MiniCParser::T_L_BRACKET, i);
}

std::vector<tree::TerminalNode *> MiniCParser::FormalParamContext::T_R_BRACKET() {
  return getTokens(MiniCParser::T_R_BRACKET);
}

tree::TerminalNode* MiniCParser::FormalParamContext::T_R_BRACKET(size_t i) {
  return getToken(MiniCParser::T_R_BRACKET, i);
}

std::vector<tree::TerminalNode *> MiniCParser::FormalParamContext::T_DIGIT() {
  return getTokens(MiniCParser::T_DIGIT);
}

tree::TerminalNode* MiniCParser::FormalParamContext::T_DIGIT(size_t i) {
  return getToken(MiniCParser::T_DIGIT, i);
}


size_t MiniCParser::FormalParamContext::getRuleIndex() const {
  return MiniCParser::RuleFormalParam;
}


std::any MiniCParser::FormalParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFormalParam(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::FormalParamContext* MiniCParser::formalParam() {
  FormalParamContext *_localctx = _tracker.createInstance<FormalParamContext>(_ctx, getState());
  enterRule(_localctx, 8, MiniCParser::RuleFormalParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    basicType();
    setState(83);
    match(MiniCParser::T_ID);
    setState(94);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T_L_BRACKET) {
      setState(84);
      match(MiniCParser::T_L_BRACKET);
      setState(85);
      match(MiniCParser::T_R_BRACKET);
      setState(91);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MiniCParser::T_L_BRACKET) {
        setState(86);
        match(MiniCParser::T_L_BRACKET);
        setState(87);
        match(MiniCParser::T_DIGIT);
        setState(88);
        match(MiniCParser::T_R_BRACKET);
        setState(93);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

MiniCParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::BlockContext::T_L_BRACE() {
  return getToken(MiniCParser::T_L_BRACE, 0);
}

tree::TerminalNode* MiniCParser::BlockContext::T_R_BRACE() {
  return getToken(MiniCParser::T_R_BRACE, 0);
}

MiniCParser::BlockItemListContext* MiniCParser::BlockContext::blockItemList() {
  return getRuleContext<MiniCParser::BlockItemListContext>(0);
}


size_t MiniCParser::BlockContext::getRuleIndex() const {
  return MiniCParser::RuleBlock;
}


std::any MiniCParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::BlockContext* MiniCParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 10, MiniCParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(MiniCParser::T_L_BRACE);
    setState(98);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 34015807514) != 0)) {
      setState(97);
      blockItemList();
    }
    setState(100);
    match(MiniCParser::T_R_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemListContext ------------------------------------------------------------------

MiniCParser::BlockItemListContext::BlockItemListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::BlockItemContext *> MiniCParser::BlockItemListContext::blockItem() {
  return getRuleContexts<MiniCParser::BlockItemContext>();
}

MiniCParser::BlockItemContext* MiniCParser::BlockItemListContext::blockItem(size_t i) {
  return getRuleContext<MiniCParser::BlockItemContext>(i);
}


size_t MiniCParser::BlockItemListContext::getRuleIndex() const {
  return MiniCParser::RuleBlockItemList;
}


std::any MiniCParser::BlockItemListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlockItemList(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::BlockItemListContext* MiniCParser::blockItemList() {
  BlockItemListContext *_localctx = _tracker.createInstance<BlockItemListContext>(_ctx, getState());
  enterRule(_localctx, 12, MiniCParser::RuleBlockItemList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(102);
      blockItem();
      setState(105); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 34015807514) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

MiniCParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::StatementContext* MiniCParser::BlockItemContext::statement() {
  return getRuleContext<MiniCParser::StatementContext>(0);
}

MiniCParser::VarDeclContext* MiniCParser::BlockItemContext::varDecl() {
  return getRuleContext<MiniCParser::VarDeclContext>(0);
}


size_t MiniCParser::BlockItemContext::getRuleIndex() const {
  return MiniCParser::RuleBlockItem;
}


std::any MiniCParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::BlockItemContext* MiniCParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 14, MiniCParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(109);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T_L_PAREN:
      case MiniCParser::T_SEMICOLON:
      case MiniCParser::T_L_BRACE:
      case MiniCParser::T_SUB:
      case MiniCParser::T_NOT:
      case MiniCParser::T_RETURN:
      case MiniCParser::T_IF:
      case MiniCParser::T_WHILE:
      case MiniCParser::T_FOR:
      case MiniCParser::T_BREAK:
      case MiniCParser::T_CONTINUE:
      case MiniCParser::T_ID:
      case MiniCParser::T_DIGIT: {
        enterOuterAlt(_localctx, 1);
        setState(107);
        statement();
        break;
      }

      case MiniCParser::T_INT: {
        enterOuterAlt(_localctx, 2);
        setState(108);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

MiniCParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::BasicTypeContext* MiniCParser::VarDeclContext::basicType() {
  return getRuleContext<MiniCParser::BasicTypeContext>(0);
}

std::vector<MiniCParser::VarDefContext *> MiniCParser::VarDeclContext::varDef() {
  return getRuleContexts<MiniCParser::VarDefContext>();
}

MiniCParser::VarDefContext* MiniCParser::VarDeclContext::varDef(size_t i) {
  return getRuleContext<MiniCParser::VarDefContext>(i);
}

tree::TerminalNode* MiniCParser::VarDeclContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> MiniCParser::VarDeclContext::T_COMMA() {
  return getTokens(MiniCParser::T_COMMA);
}

tree::TerminalNode* MiniCParser::VarDeclContext::T_COMMA(size_t i) {
  return getToken(MiniCParser::T_COMMA, i);
}


size_t MiniCParser::VarDeclContext::getRuleIndex() const {
  return MiniCParser::RuleVarDecl;
}


std::any MiniCParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::VarDeclContext* MiniCParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 16, MiniCParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    basicType();
    setState(112);
    varDef();
    setState(117);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_COMMA) {
      setState(113);
      match(MiniCParser::T_COMMA);
      setState(114);
      varDef();
      setState(119);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(120);
    match(MiniCParser::T_SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicTypeContext ------------------------------------------------------------------

MiniCParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::BasicTypeContext::T_INT() {
  return getToken(MiniCParser::T_INT, 0);
}


size_t MiniCParser::BasicTypeContext::getRuleIndex() const {
  return MiniCParser::RuleBasicType;
}


std::any MiniCParser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::BasicTypeContext* MiniCParser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 18, MiniCParser::RuleBasicType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(MiniCParser::T_INT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

MiniCParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::VarDefContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

std::vector<tree::TerminalNode *> MiniCParser::VarDefContext::T_L_BRACKET() {
  return getTokens(MiniCParser::T_L_BRACKET);
}

tree::TerminalNode* MiniCParser::VarDefContext::T_L_BRACKET(size_t i) {
  return getToken(MiniCParser::T_L_BRACKET, i);
}

std::vector<MiniCParser::ExprContext *> MiniCParser::VarDefContext::expr() {
  return getRuleContexts<MiniCParser::ExprContext>();
}

MiniCParser::ExprContext* MiniCParser::VarDefContext::expr(size_t i) {
  return getRuleContext<MiniCParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::VarDefContext::T_R_BRACKET() {
  return getTokens(MiniCParser::T_R_BRACKET);
}

tree::TerminalNode* MiniCParser::VarDefContext::T_R_BRACKET(size_t i) {
  return getToken(MiniCParser::T_R_BRACKET, i);
}

tree::TerminalNode* MiniCParser::VarDefContext::T_ASSIGN() {
  return getToken(MiniCParser::T_ASSIGN, 0);
}


size_t MiniCParser::VarDefContext::getRuleIndex() const {
  return MiniCParser::RuleVarDef;
}


std::any MiniCParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::VarDefContext* MiniCParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 20, MiniCParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    match(MiniCParser::T_ID);
    setState(131);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_L_BRACKET) {
      setState(125);
      match(MiniCParser::T_L_BRACKET);
      setState(126);
      expr();
      setState(127);
      match(MiniCParser::T_R_BRACKET);
      setState(133);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(136);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T_ASSIGN) {
      setState(134);
      match(MiniCParser::T_ASSIGN);
      setState(135);
      expr();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

MiniCParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::StatementContext::getRuleIndex() const {
  return MiniCParser::RuleStatement;
}

void MiniCParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- WhileStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::WhileStatementContext::T_WHILE() {
  return getToken(MiniCParser::T_WHILE, 0);
}

tree::TerminalNode* MiniCParser::WhileStatementContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

MiniCParser::ExprContext* MiniCParser::WhileStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

tree::TerminalNode* MiniCParser::WhileStatementContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

MiniCParser::StatementContext* MiniCParser::WhileStatementContext::statement() {
  return getRuleContext<MiniCParser::StatementContext>(0);
}

MiniCParser::WhileStatementContext::WhileStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStatementContext ------------------------------------------------------------------

MiniCParser::BlockContext* MiniCParser::BlockStatementContext::block() {
  return getRuleContext<MiniCParser::BlockContext>(0);
}

MiniCParser::BlockStatementContext::BlockStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlockStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStatementContext ------------------------------------------------------------------

MiniCParser::LValContext* MiniCParser::AssignStatementContext::lVal() {
  return getRuleContext<MiniCParser::LValContext>(0);
}

tree::TerminalNode* MiniCParser::AssignStatementContext::T_ASSIGN() {
  return getToken(MiniCParser::T_ASSIGN, 0);
}

MiniCParser::ExprContext* MiniCParser::AssignStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

tree::TerminalNode* MiniCParser::AssignStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::AssignStatementContext::AssignStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::AssignStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitAssignStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ForStatementContext::T_FOR() {
  return getToken(MiniCParser::T_FOR, 0);
}

tree::TerminalNode* MiniCParser::ForStatementContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

std::vector<tree::TerminalNode *> MiniCParser::ForStatementContext::T_SEMICOLON() {
  return getTokens(MiniCParser::T_SEMICOLON);
}

tree::TerminalNode* MiniCParser::ForStatementContext::T_SEMICOLON(size_t i) {
  return getToken(MiniCParser::T_SEMICOLON, i);
}

tree::TerminalNode* MiniCParser::ForStatementContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

MiniCParser::StatementContext* MiniCParser::ForStatementContext::statement() {
  return getRuleContext<MiniCParser::StatementContext>(0);
}

std::vector<MiniCParser::ExprContext *> MiniCParser::ForStatementContext::expr() {
  return getRuleContexts<MiniCParser::ExprContext>();
}

MiniCParser::ExprContext* MiniCParser::ForStatementContext::expr(size_t i) {
  return getRuleContext<MiniCParser::ExprContext>(i);
}

MiniCParser::VarDeclContext* MiniCParser::ForStatementContext::varDecl() {
  return getRuleContext<MiniCParser::VarDeclContext>(0);
}

MiniCParser::ForStatementContext::ForStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::BreakStatementContext::T_BREAK() {
  return getToken(MiniCParser::T_BREAK, 0);
}

tree::TerminalNode* MiniCParser::BreakStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::BreakStatementContext::BreakStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpressionStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ExpressionStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::ExprContext* MiniCParser::ExpressionStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

MiniCParser::ExpressionStatementContext::ExpressionStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ContinueStatementContext::T_CONTINUE() {
  return getToken(MiniCParser::T_CONTINUE, 0);
}

tree::TerminalNode* MiniCParser::ContinueStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::ContinueStatementContext::ContinueStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ReturnStatementContext::T_RETURN() {
  return getToken(MiniCParser::T_RETURN, 0);
}

MiniCParser::ExprContext* MiniCParser::ReturnStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

tree::TerminalNode* MiniCParser::ReturnStatementContext::T_SEMICOLON() {
  return getToken(MiniCParser::T_SEMICOLON, 0);
}

MiniCParser::ReturnStatementContext::ReturnStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::IfStatementContext::T_IF() {
  return getToken(MiniCParser::T_IF, 0);
}

tree::TerminalNode* MiniCParser::IfStatementContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

MiniCParser::ExprContext* MiniCParser::IfStatementContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

tree::TerminalNode* MiniCParser::IfStatementContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

std::vector<MiniCParser::StatementContext *> MiniCParser::IfStatementContext::statement() {
  return getRuleContexts<MiniCParser::StatementContext>();
}

MiniCParser::StatementContext* MiniCParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<MiniCParser::StatementContext>(i);
}

tree::TerminalNode* MiniCParser::IfStatementContext::T_ELSE() {
  return getToken(MiniCParser::T_ELSE, 0);
}

MiniCParser::IfStatementContext::IfStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::StatementContext* MiniCParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 22, MiniCParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(187);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MiniCParser::ReturnStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(138);
      match(MiniCParser::T_RETURN);
      setState(139);
      expr();
      setState(140);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MiniCParser::AssignStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(142);
      lVal();
      setState(143);
      match(MiniCParser::T_ASSIGN);
      setState(144);
      expr();
      setState(145);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MiniCParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(147);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MiniCParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(149);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 25778194434) != 0)) {
        setState(148);
        expr();
      }
      setState(151);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MiniCParser::IfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(152);
      match(MiniCParser::T_IF);
      setState(153);
      match(MiniCParser::T_L_PAREN);
      setState(154);
      expr();
      setState(155);
      match(MiniCParser::T_R_PAREN);
      setState(156);
      statement();
      setState(159);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(157);
        match(MiniCParser::T_ELSE);
        setState(158);
        statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<MiniCParser::WhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(161);
      match(MiniCParser::T_WHILE);
      setState(162);
      match(MiniCParser::T_L_PAREN);
      setState(163);
      expr();
      setState(164);
      match(MiniCParser::T_R_PAREN);
      setState(165);
      statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<MiniCParser::ForStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(167);
      match(MiniCParser::T_FOR);
      setState(168);
      match(MiniCParser::T_L_PAREN);
      setState(171);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case MiniCParser::T_L_PAREN:
        case MiniCParser::T_SUB:
        case MiniCParser::T_NOT:
        case MiniCParser::T_ID:
        case MiniCParser::T_DIGIT: {
          setState(169);
          expr();
          break;
        }

        case MiniCParser::T_INT: {
          setState(170);
          varDecl();
          break;
        }

        case MiniCParser::T_SEMICOLON: {
          break;
        }

      default:
        break;
      }
      setState(173);
      match(MiniCParser::T_SEMICOLON);
      setState(175);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 25778194434) != 0)) {
        setState(174);
        expr();
      }
      setState(177);
      match(MiniCParser::T_SEMICOLON);
      setState(179);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 25778194434) != 0)) {
        setState(178);
        expr();
      }
      setState(181);
      match(MiniCParser::T_R_PAREN);
      setState(182);
      statement();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<MiniCParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(183);
      match(MiniCParser::T_BREAK);
      setState(184);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<MiniCParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(185);
      match(MiniCParser::T_CONTINUE);
      setState(186);
      match(MiniCParser::T_SEMICOLON);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

MiniCParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::LogicOrExpContext* MiniCParser::ExprContext::logicOrExp() {
  return getRuleContext<MiniCParser::LogicOrExpContext>(0);
}


size_t MiniCParser::ExprContext::getRuleIndex() const {
  return MiniCParser::RuleExpr;
}


std::any MiniCParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ExprContext* MiniCParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 24, MiniCParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    logicOrExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicOrExpContext ------------------------------------------------------------------

MiniCParser::LogicOrExpContext::LogicOrExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::LogicAndExpContext *> MiniCParser::LogicOrExpContext::logicAndExp() {
  return getRuleContexts<MiniCParser::LogicAndExpContext>();
}

MiniCParser::LogicAndExpContext* MiniCParser::LogicOrExpContext::logicAndExp(size_t i) {
  return getRuleContext<MiniCParser::LogicAndExpContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::LogicOrExpContext::T_OR() {
  return getTokens(MiniCParser::T_OR);
}

tree::TerminalNode* MiniCParser::LogicOrExpContext::T_OR(size_t i) {
  return getToken(MiniCParser::T_OR, i);
}


size_t MiniCParser::LogicOrExpContext::getRuleIndex() const {
  return MiniCParser::RuleLogicOrExp;
}


std::any MiniCParser::LogicOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLogicOrExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::LogicOrExpContext* MiniCParser::logicOrExp() {
  LogicOrExpContext *_localctx = _tracker.createInstance<LogicOrExpContext>(_ctx, getState());
  enterRule(_localctx, 26, MiniCParser::RuleLogicOrExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    logicAndExp();
    setState(196);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_OR) {
      setState(192);
      match(MiniCParser::T_OR);
      setState(193);
      logicAndExp();
      setState(198);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicAndExpContext ------------------------------------------------------------------

MiniCParser::LogicAndExpContext::LogicAndExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::EqualityExpContext *> MiniCParser::LogicAndExpContext::equalityExp() {
  return getRuleContexts<MiniCParser::EqualityExpContext>();
}

MiniCParser::EqualityExpContext* MiniCParser::LogicAndExpContext::equalityExp(size_t i) {
  return getRuleContext<MiniCParser::EqualityExpContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::LogicAndExpContext::T_AND() {
  return getTokens(MiniCParser::T_AND);
}

tree::TerminalNode* MiniCParser::LogicAndExpContext::T_AND(size_t i) {
  return getToken(MiniCParser::T_AND, i);
}


size_t MiniCParser::LogicAndExpContext::getRuleIndex() const {
  return MiniCParser::RuleLogicAndExp;
}


std::any MiniCParser::LogicAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLogicAndExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::LogicAndExpContext* MiniCParser::logicAndExp() {
  LogicAndExpContext *_localctx = _tracker.createInstance<LogicAndExpContext>(_ctx, getState());
  enterRule(_localctx, 28, MiniCParser::RuleLogicAndExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    equalityExp();
    setState(204);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_AND) {
      setState(200);
      match(MiniCParser::T_AND);
      setState(201);
      equalityExp();
      setState(206);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpContext ------------------------------------------------------------------

MiniCParser::EqualityExpContext::EqualityExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::RelationalExpContext *> MiniCParser::EqualityExpContext::relationalExp() {
  return getRuleContexts<MiniCParser::RelationalExpContext>();
}

MiniCParser::RelationalExpContext* MiniCParser::EqualityExpContext::relationalExp(size_t i) {
  return getRuleContext<MiniCParser::RelationalExpContext>(i);
}

std::vector<MiniCParser::EqualityOpContext *> MiniCParser::EqualityExpContext::equalityOp() {
  return getRuleContexts<MiniCParser::EqualityOpContext>();
}

MiniCParser::EqualityOpContext* MiniCParser::EqualityExpContext::equalityOp(size_t i) {
  return getRuleContext<MiniCParser::EqualityOpContext>(i);
}


size_t MiniCParser::EqualityExpContext::getRuleIndex() const {
  return MiniCParser::RuleEqualityExp;
}


std::any MiniCParser::EqualityExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitEqualityExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::EqualityExpContext* MiniCParser::equalityExp() {
  EqualityExpContext *_localctx = _tracker.createInstance<EqualityExpContext>(_ctx, getState());
  enterRule(_localctx, 30, MiniCParser::RuleEqualityExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    relationalExp();
    setState(213);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_EQ

    || _la == MiniCParser::T_NEQ) {
      setState(208);
      equalityOp();
      setState(209);
      relationalExp();
      setState(215);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityOpContext ------------------------------------------------------------------

MiniCParser::EqualityOpContext::EqualityOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::EqualityOpContext::T_EQ() {
  return getToken(MiniCParser::T_EQ, 0);
}

tree::TerminalNode* MiniCParser::EqualityOpContext::T_NEQ() {
  return getToken(MiniCParser::T_NEQ, 0);
}


size_t MiniCParser::EqualityOpContext::getRuleIndex() const {
  return MiniCParser::RuleEqualityOp;
}


std::any MiniCParser::EqualityOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitEqualityOp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::EqualityOpContext* MiniCParser::equalityOp() {
  EqualityOpContext *_localctx = _tracker.createInstance<EqualityOpContext>(_ctx, getState());
  enterRule(_localctx, 32, MiniCParser::RuleEqualityOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
    _la = _input->LA(1);
    if (!(_la == MiniCParser::T_EQ

    || _la == MiniCParser::T_NEQ)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpContext ------------------------------------------------------------------

MiniCParser::RelationalExpContext::RelationalExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::AddExpContext *> MiniCParser::RelationalExpContext::addExp() {
  return getRuleContexts<MiniCParser::AddExpContext>();
}

MiniCParser::AddExpContext* MiniCParser::RelationalExpContext::addExp(size_t i) {
  return getRuleContext<MiniCParser::AddExpContext>(i);
}

std::vector<MiniCParser::RelationalOpContext *> MiniCParser::RelationalExpContext::relationalOp() {
  return getRuleContexts<MiniCParser::RelationalOpContext>();
}

MiniCParser::RelationalOpContext* MiniCParser::RelationalExpContext::relationalOp(size_t i) {
  return getRuleContext<MiniCParser::RelationalOpContext>(i);
}


size_t MiniCParser::RelationalExpContext::getRuleIndex() const {
  return MiniCParser::RuleRelationalExp;
}


std::any MiniCParser::RelationalExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitRelationalExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::RelationalExpContext* MiniCParser::relationalExp() {
  RelationalExpContext *_localctx = _tracker.createInstance<RelationalExpContext>(_ctx, getState());
  enterRule(_localctx, 34, MiniCParser::RuleRelationalExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    addExp();
    setState(224);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 491520) != 0)) {
      setState(219);
      relationalOp();
      setState(220);
      addExp();
      setState(226);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalOpContext ------------------------------------------------------------------

MiniCParser::RelationalOpContext::RelationalOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::RelationalOpContext::T_LT() {
  return getToken(MiniCParser::T_LT, 0);
}

tree::TerminalNode* MiniCParser::RelationalOpContext::T_GT() {
  return getToken(MiniCParser::T_GT, 0);
}

tree::TerminalNode* MiniCParser::RelationalOpContext::T_LE() {
  return getToken(MiniCParser::T_LE, 0);
}

tree::TerminalNode* MiniCParser::RelationalOpContext::T_GE() {
  return getToken(MiniCParser::T_GE, 0);
}


size_t MiniCParser::RelationalOpContext::getRuleIndex() const {
  return MiniCParser::RuleRelationalOp;
}


std::any MiniCParser::RelationalOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitRelationalOp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::RelationalOpContext* MiniCParser::relationalOp() {
  RelationalOpContext *_localctx = _tracker.createInstance<RelationalOpContext>(_ctx, getState());
  enterRule(_localctx, 36, MiniCParser::RuleRelationalOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(227);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 491520) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExpContext ------------------------------------------------------------------

MiniCParser::AddExpContext::AddExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::MulExpContext *> MiniCParser::AddExpContext::mulExp() {
  return getRuleContexts<MiniCParser::MulExpContext>();
}

MiniCParser::MulExpContext* MiniCParser::AddExpContext::mulExp(size_t i) {
  return getRuleContext<MiniCParser::MulExpContext>(i);
}

std::vector<MiniCParser::AddOpContext *> MiniCParser::AddExpContext::addOp() {
  return getRuleContexts<MiniCParser::AddOpContext>();
}

MiniCParser::AddOpContext* MiniCParser::AddExpContext::addOp(size_t i) {
  return getRuleContext<MiniCParser::AddOpContext>(i);
}


size_t MiniCParser::AddExpContext::getRuleIndex() const {
  return MiniCParser::RuleAddExp;
}


std::any MiniCParser::AddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitAddExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::AddExpContext* MiniCParser::addExp() {
  AddExpContext *_localctx = _tracker.createInstance<AddExpContext>(_ctx, getState());
  enterRule(_localctx, 38, MiniCParser::RuleAddExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(229);
    mulExp();
    setState(235);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_ADD

    || _la == MiniCParser::T_SUB) {
      setState(230);
      addOp();
      setState(231);
      mulExp();
      setState(237);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddOpContext ------------------------------------------------------------------

MiniCParser::AddOpContext::AddOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::AddOpContext::T_ADD() {
  return getToken(MiniCParser::T_ADD, 0);
}

tree::TerminalNode* MiniCParser::AddOpContext::T_SUB() {
  return getToken(MiniCParser::T_SUB, 0);
}


size_t MiniCParser::AddOpContext::getRuleIndex() const {
  return MiniCParser::RuleAddOp;
}


std::any MiniCParser::AddOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitAddOp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::AddOpContext* MiniCParser::addOp() {
  AddOpContext *_localctx = _tracker.createInstance<AddOpContext>(_ctx, getState());
  enterRule(_localctx, 40, MiniCParser::RuleAddOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(238);
    _la = _input->LA(1);
    if (!(_la == MiniCParser::T_ADD

    || _la == MiniCParser::T_SUB)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpContext ------------------------------------------------------------------

MiniCParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::UnaryExpContext *> MiniCParser::MulExpContext::unaryExp() {
  return getRuleContexts<MiniCParser::UnaryExpContext>();
}

MiniCParser::UnaryExpContext* MiniCParser::MulExpContext::unaryExp(size_t i) {
  return getRuleContext<MiniCParser::UnaryExpContext>(i);
}

std::vector<MiniCParser::MulOpContext *> MiniCParser::MulExpContext::mulOp() {
  return getRuleContexts<MiniCParser::MulOpContext>();
}

MiniCParser::MulOpContext* MiniCParser::MulExpContext::mulOp(size_t i) {
  return getRuleContext<MiniCParser::MulOpContext>(i);
}


size_t MiniCParser::MulExpContext::getRuleIndex() const {
  return MiniCParser::RuleMulExp;
}


std::any MiniCParser::MulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitMulExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::MulExpContext* MiniCParser::mulExp() {
  MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, getState());
  enterRule(_localctx, 42, MiniCParser::RuleMulExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(240);
    unaryExp();
    setState(246);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28672) != 0)) {
      setState(241);
      mulOp();
      setState(242);
      unaryExp();
      setState(248);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulOpContext ------------------------------------------------------------------

MiniCParser::MulOpContext::MulOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::MulOpContext::T_MUL() {
  return getToken(MiniCParser::T_MUL, 0);
}

tree::TerminalNode* MiniCParser::MulOpContext::T_DIV() {
  return getToken(MiniCParser::T_DIV, 0);
}

tree::TerminalNode* MiniCParser::MulOpContext::T_MOD() {
  return getToken(MiniCParser::T_MOD, 0);
}


size_t MiniCParser::MulOpContext::getRuleIndex() const {
  return MiniCParser::RuleMulOp;
}


std::any MiniCParser::MulOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitMulOp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::MulOpContext* MiniCParser::mulOp() {
  MulOpContext *_localctx = _tracker.createInstance<MulOpContext>(_ctx, getState());
  enterRule(_localctx, 44, MiniCParser::RuleMulOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(249);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 28672) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpContext ------------------------------------------------------------------

MiniCParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::UnaryExpContext::getRuleIndex() const {
  return MiniCParser::RuleUnaryExp;
}

void MiniCParser::UnaryExpContext::copyFrom(UnaryExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LogicalNotUnaryExpContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::LogicalNotUnaryExpContext::T_NOT() {
  return getToken(MiniCParser::T_NOT, 0);
}

MiniCParser::UnaryExpContext* MiniCParser::LogicalNotUnaryExpContext::unaryExp() {
  return getRuleContext<MiniCParser::UnaryExpContext>(0);
}

MiniCParser::LogicalNotUnaryExpContext::LogicalNotUnaryExpContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::LogicalNotUnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLogicalNotUnaryExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallUnaryExpContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::FuncCallUnaryExpContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

tree::TerminalNode* MiniCParser::FuncCallUnaryExpContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

tree::TerminalNode* MiniCParser::FuncCallUnaryExpContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

MiniCParser::RealParamListContext* MiniCParser::FuncCallUnaryExpContext::realParamList() {
  return getRuleContext<MiniCParser::RealParamListContext>(0);
}

MiniCParser::FuncCallUnaryExpContext::FuncCallUnaryExpContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::FuncCallUnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFuncCallUnaryExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryUnaryExpContext ------------------------------------------------------------------

MiniCParser::PrimaryExpContext* MiniCParser::PrimaryUnaryExpContext::primaryExp() {
  return getRuleContext<MiniCParser::PrimaryExpContext>(0);
}

MiniCParser::PrimaryUnaryExpContext::PrimaryUnaryExpContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::PrimaryUnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitPrimaryUnaryExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NegativeUnaryExpContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::NegativeUnaryExpContext::T_SUB() {
  return getToken(MiniCParser::T_SUB, 0);
}

MiniCParser::UnaryExpContext* MiniCParser::NegativeUnaryExpContext::unaryExp() {
  return getRuleContext<MiniCParser::UnaryExpContext>(0);
}

MiniCParser::NegativeUnaryExpContext::NegativeUnaryExpContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::NegativeUnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitNegativeUnaryExp(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::UnaryExpContext* MiniCParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 46, MiniCParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(262);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MiniCParser::PrimaryUnaryExpContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(251);
      primaryExp();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MiniCParser::NegativeUnaryExpContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(252);
      match(MiniCParser::T_SUB);
      setState(253);
      unaryExp();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MiniCParser::LogicalNotUnaryExpContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(254);
      match(MiniCParser::T_NOT);
      setState(255);
      unaryExp();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MiniCParser::FuncCallUnaryExpContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(256);
      match(MiniCParser::T_ID);
      setState(257);
      match(MiniCParser::T_L_PAREN);
      setState(259);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 25778194434) != 0)) {
        setState(258);
        realParamList();
      }
      setState(261);
      match(MiniCParser::T_R_PAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpContext ------------------------------------------------------------------

MiniCParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::PrimaryExpContext::T_L_PAREN() {
  return getToken(MiniCParser::T_L_PAREN, 0);
}

MiniCParser::ExprContext* MiniCParser::PrimaryExpContext::expr() {
  return getRuleContext<MiniCParser::ExprContext>(0);
}

tree::TerminalNode* MiniCParser::PrimaryExpContext::T_R_PAREN() {
  return getToken(MiniCParser::T_R_PAREN, 0);
}

tree::TerminalNode* MiniCParser::PrimaryExpContext::T_DIGIT() {
  return getToken(MiniCParser::T_DIGIT, 0);
}

MiniCParser::LValContext* MiniCParser::PrimaryExpContext::lVal() {
  return getRuleContext<MiniCParser::LValContext>(0);
}


size_t MiniCParser::PrimaryExpContext::getRuleIndex() const {
  return MiniCParser::RulePrimaryExp;
}


std::any MiniCParser::PrimaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitPrimaryExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::PrimaryExpContext* MiniCParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 48, MiniCParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(270);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T_L_PAREN: {
        enterOuterAlt(_localctx, 1);
        setState(264);
        match(MiniCParser::T_L_PAREN);
        setState(265);
        expr();
        setState(266);
        match(MiniCParser::T_R_PAREN);
        break;
      }

      case MiniCParser::T_DIGIT: {
        enterOuterAlt(_localctx, 2);
        setState(268);
        match(MiniCParser::T_DIGIT);
        break;
      }

      case MiniCParser::T_ID: {
        enterOuterAlt(_localctx, 3);
        setState(269);
        lVal();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RealParamListContext ------------------------------------------------------------------

MiniCParser::RealParamListContext::RealParamListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::ExprContext *> MiniCParser::RealParamListContext::expr() {
  return getRuleContexts<MiniCParser::ExprContext>();
}

MiniCParser::ExprContext* MiniCParser::RealParamListContext::expr(size_t i) {
  return getRuleContext<MiniCParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::RealParamListContext::T_COMMA() {
  return getTokens(MiniCParser::T_COMMA);
}

tree::TerminalNode* MiniCParser::RealParamListContext::T_COMMA(size_t i) {
  return getToken(MiniCParser::T_COMMA, i);
}


size_t MiniCParser::RealParamListContext::getRuleIndex() const {
  return MiniCParser::RuleRealParamList;
}


std::any MiniCParser::RealParamListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitRealParamList(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::RealParamListContext* MiniCParser::realParamList() {
  RealParamListContext *_localctx = _tracker.createInstance<RealParamListContext>(_ctx, getState());
  enterRule(_localctx, 50, MiniCParser::RuleRealParamList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(272);
    expr();
    setState(277);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_COMMA) {
      setState(273);
      match(MiniCParser::T_COMMA);
      setState(274);
      expr();
      setState(279);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

MiniCParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::LValContext::T_ID() {
  return getToken(MiniCParser::T_ID, 0);
}

std::vector<tree::TerminalNode *> MiniCParser::LValContext::T_L_BRACKET() {
  return getTokens(MiniCParser::T_L_BRACKET);
}

tree::TerminalNode* MiniCParser::LValContext::T_L_BRACKET(size_t i) {
  return getToken(MiniCParser::T_L_BRACKET, i);
}

std::vector<MiniCParser::ExprContext *> MiniCParser::LValContext::expr() {
  return getRuleContexts<MiniCParser::ExprContext>();
}

MiniCParser::ExprContext* MiniCParser::LValContext::expr(size_t i) {
  return getRuleContext<MiniCParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MiniCParser::LValContext::T_R_BRACKET() {
  return getTokens(MiniCParser::T_R_BRACKET);
}

tree::TerminalNode* MiniCParser::LValContext::T_R_BRACKET(size_t i) {
  return getToken(MiniCParser::T_R_BRACKET, i);
}


size_t MiniCParser::LValContext::getRuleIndex() const {
  return MiniCParser::RuleLVal;
}


std::any MiniCParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::LValContext* MiniCParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 52, MiniCParser::RuleLVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    match(MiniCParser::T_ID);
    setState(287);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T_L_BRACKET) {
      setState(281);
      match(MiniCParser::T_L_BRACKET);
      setState(282);
      expr();
      setState(283);
      match(MiniCParser::T_R_BRACKET);
      setState(289);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void MiniCParser::initialize() {
  ::antlr4::internal::call_once(minicParserOnceFlag, minicParserInitialize);
}
