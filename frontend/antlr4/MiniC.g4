grammar MiniC;

// 词法规则名总是以大写字母开头

// 语法规则名总是以小写字母开头

// 每个非终结符尽量多包含闭包、正闭包或可选符等的EBNF范式描述

// 若非终结符由多个产生式组成，则建议在每个产生式的尾部追加# 名称来区分，详细可查看非终结符statement的描述

// 语法规则描述：EBNF范式

// 源文件编译单元定义
compileUnit: (funcDef | varDecl)* EOF;

// 函数定义，支持多形参和void返回类型
funcDef:
	returnType T_ID T_L_PAREN formalParams? T_R_PAREN block;

// 返回类型
returnType: T_INT | T_VOID;

// 形参列表
formalParams: formalParam (T_COMMA formalParam)*;

// 形参定义
formalParam:
	basicType T_ID (
		T_L_BRACKET T_R_BRACKET (T_L_BRACKET T_DIGIT T_R_BRACKET)*
	)?;

// 语句块看用作函数体，这里允许多个语句，并且不含任何语句
block: T_L_BRACE blockItemList? T_R_BRACE;

// 每个ItemList可包含至少一个Item
blockItemList: blockItem+;

// 每个Item可以是一个语句，或者变量声明语句
blockItem: statement | varDecl;

// 变量声明，支持变量含有初值
varDecl: basicType varDef (T_COMMA varDef)* T_SEMICOLON;

// 基本类型
basicType: T_INT;

// 变量定义，支持可选的初始值赋值和数组定义
varDef: T_ID (T_L_BRACKET expr T_R_BRACKET)* (T_ASSIGN expr)?;

// 目前语句支持return和赋值语句以及分支和循环语句
statement:
	T_RETURN expr T_SEMICOLON																	# returnStatement
	| lVal T_ASSIGN expr T_SEMICOLON															# assignStatement
	| block																						# blockStatement
	| expr? T_SEMICOLON																			# expressionStatement
	| T_IF T_L_PAREN expr T_R_PAREN statement (T_ELSE statement)?								# ifStatement
	| T_WHILE T_L_PAREN expr T_R_PAREN statement												# whileStatement
	| T_FOR T_L_PAREN (expr | varDecl)? T_SEMICOLON expr? T_SEMICOLON expr? T_R_PAREN statement	#
		forStatement
	| T_BREAK T_SEMICOLON		# breakStatement
	| T_CONTINUE T_SEMICOLON	# continueStatement;

// 表达式语法修改为逻辑层
expr: logicOrExp;

// 逻辑或表达式
logicOrExp: logicAndExp (T_OR logicAndExp)*;

// 逻辑与表达式
logicAndExp: equalityExp (T_AND equalityExp)*;

// 相等性表达式
equalityExp: relationalExp (equalityOp relationalExp)*;

// 相等性操作符
equalityOp: T_EQ | T_NEQ;

// 关系表达式
relationalExp: addExp (relationalOp addExp)*;

// 关系操作符
relationalOp: T_LT | T_GT | T_LE | T_GE;

// 加减表达式
addExp: mulExp (addOp mulExp)*;

// 加减运算符
addOp: T_ADD | T_SUB;

// 乘除模表达式
mulExp: unaryExp (mulOp unaryExp)*;

// 乘除模运算符
mulOp: T_MUL | T_DIV | T_MOD;

// 一元表达式
unaryExp:
	primaryExp									# primaryUnaryExp
	| T_SUB unaryExp							# negativeUnaryExp
	| T_NOT unaryExp							# logicalNotUnaryExp
	| T_ID T_L_PAREN realParamList? T_R_PAREN	# funcCallUnaryExp;

// 基本表达式：括号表达式、整数、左值表达式
primaryExp: T_L_PAREN expr T_R_PAREN | T_DIGIT | lVal;

// 实参列表
realParamList: expr (T_COMMA expr)*;

// 左值表达式
lVal: T_ID (T_L_BRACKET expr T_R_BRACKET)*;

// 用正规式来进行词法规则的描述

T_L_PAREN: '(';
T_R_PAREN: ')';
T_SEMICOLON: ';';
T_L_BRACE: '{';
T_R_BRACE: '}';

// 添加数组下标的方括号词法规则
T_L_BRACKET: '[';
T_R_BRACKET: ']';

T_ASSIGN: '=';
T_COMMA: ',';

T_ADD: '+';
T_SUB: '-';
T_MUL: '*';
T_DIV: '/';
T_MOD: '%';

// 关系运算符
T_LT: '<';
T_GT: '>';
T_LE: '<=';
T_GE: '>=';
T_EQ: '==';
T_NEQ: '!=';

// 逻辑运算符
T_AND: '&&';
T_OR: '||';
T_NOT: '!';

// 要注意关键字同样也属于T_ID，因此必须放在T_ID的前面，否则会识别成T_ID
T_RETURN: 'return';
T_INT: 'int';
T_VOID: 'void';
T_IF: 'if';
T_ELSE: 'else';
T_WHILE: 'while';
T_FOR: 'for';
T_BREAK: 'break';
T_CONTINUE: 'continue';

T_ID: [a-zA-Z_][a-zA-Z0-9_]*;
T_DIGIT:
	'0' [0-7]+
	| '0' [xX][0-9a-fA-F]+
	| '0'
	| [1-9][0-9]*;

/* 空白符丢弃 */
WS: [ \r\n\t]+ -> skip;

/* 单行注释 */
SINGLE_LINE_COMMENT: '//' ~[\r\n]* -> skip;

/* 多行注释 */
MULTI_LINE_COMMENT: '/*' .*? '*/' -> skip;