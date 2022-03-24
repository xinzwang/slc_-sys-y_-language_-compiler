%skeleton "lalr1.cc"

%require "3.0.4"

%define api.namespace {Marker} //声明命名空间与下面声明的类名结合使用 Marker::Parser::  在scanner.l中有体现
%define parser_class_name { Parser }
%define api.token.constructor
%define api.value.type variant //使得类型与token定义可以使用各种复杂的结构与类型
%define parse.assert  //开启断言功能
%defines  //生成各种头文件  location.hh position.hh  parser.hpp

%code requires
{
	/*requires中的内容会放在YYLTYPE与YYSTPYPE定义前*/
	#include <iostream>
	#include <string>
	#include <vector>
	#include <stdint.h>
  	#include <cmath>

	#include "Ast.hpp"
	#include "Type.hpp"

  	using namespace std;

  	namespace Marker { /*避免包含头文件时冲突*/
		class Scanner;
		class Driver;
  	}
}

%code top
{
	//尽可能放在parser.cpp头部
	#include <iostream>
  	#include "scanner.hpp"
  	#include "parser.hpp"
  	#include "Driver.hpp"
  	#include "location.hh"

	#include "Ast.hpp"
	#include "Type.hpp"

	static Marker::Parser::symbol_type yylex(Marker::Scanner& scanner,Marker::Driver &driver){
    	return scanner.nextToken();
  	}
  	using namespace Marker;
}

%lex-param { Marker::Scanner& scanner }
%lex-param { Marker::Driver& driver }

%parse-param { Marker::Scanner& scanner }
%parse-param { Marker::Driver& driver }

%locations

%define parse.error verbose

/*通过Marker::Parser::make_XXX(loc) 给token添加前缀*/
%define api.token.prefix {TOKEN_}

%token CONST
%token INT
%token VOID
%token IF
%token ELSE
%token WHILE
%token BREAK
%token CONTINUE
%token RETURN

%token SEMI
%token COMMA
%token L_PAREN
%token R_PAREN
%token L_BRACKET
%token R_BRACKET
%token L_BRACE
%token R_BRACE

%token GT
%token LT
%token GTE
%token LTE
%token EQ
%token NEQ

%token ADD
%token SUB
%token MUL
%token DIV
%token MOD
%token ASSIGN

%token NOT
%token AND
%token OR

%token <int>INTCONST
%token <string>IDENT


%token EOL
%token END 0

%left ADD 
%left SUB 
%left MUL 
%left DIV 
%left MOD
%left L_PAREN
%left L_BRACKET
%left L_BRACE

%left GT
%left LT
%left GTE
%left LTE

%nonassoc ABS "|"
%nonassoc NEG

%type<ast_CompUnit*> st
%type<ast_CompUnit*>compUnit
// %type<ast_Decl*>decl
%type<ast_ConstDecl*>constDecl
%type<ast_ConstDef*>constDef
%type<ast_ConstInitVal*>constInitVal
%type<ast_VarDecl*>varDecl
%type<ast_VarDef*>varDef
%type<ast_InitVal*>initVal
%type<ast_FuncDef*>funcDef
%type<ast_FuncFParams*>funcFParams
%type<ast_FuncFParam*>funcFParam
%type<ast_Block*>block
%type<ast_BlockItem*>blockItem
%type<ast_Stmt*>stmt

%type<ast_Expression*>exp

%type<ast_Number*>number
%type<ast_Expression*>cond
%type<ast_LVal*>lVal

%type<ast_Expression*>primaryExp

%type<ast_Expression*>unaryExp
%type<ast_FuncRParams*>funcRParams

%type<ast_Expression*>mulExp
%type<ast_Expression*>addExp
%type<ast_Expression*>relExp
%type<ast_Expression*>eqExp
%type<ast_Expression*>landExp
%type<ast_Expression*>lorExp

%type<ast_Expression*>constExp
// 其他节点
%type<ast_FunCall*>funCall
%type<ast_AssignStmt*>assignStmt
%type<ast_SelectStmt*>selectStmt
%type<ast_IterationStmt*>iterationStmt
%type<ast_BreakStmt*>breakStmt
%type<ast_ContinueStmt*>continueStmt
%type<ast_ReturnStmt*>returnStmt

%type<ast_ConstDefList*>constDefList
%type<ast_VarDefList*>varDefList

%type<ast_ConstBracketList*>const_bracketList
%type<ast_BracketList*>func_bracketList

%type<ast_InitList*>initList
%type<ast_ConstInitList*>constInitList
%type<ast_BlockItems*>blockItems


%start st

%%

st: compUnit { driver.ast.root = $1; }
	;


// compUnit: %empty	{ printf("Got empty"); $$ = new ast_CompUnit(); }
// 	| constDecl		{ $$ = new ast_CompUnit(); $$->const_decl_list.push_back($1); }
// 	| varDecl		{ $$ = new ast_CompUnit(); $$->var_decl_list.push_back($1); }
// 	| funcDef		{ $$ = new ast_CompUnit(); $$->fun_def_list.push_back($1); }
// 	| compUnit constDecl	{ $$ = $1; $$->const_decl_list.push_back($2); }
// 	| compUnit varDecl		{ $$ = $1; $$->var_decl_list.push_back($2); }
// 	| compUnit funcDef		{ $$ = $1; $$->fun_def_list.push_back($2); }
// 	;
compUnit: %empty	{ printf("Got empty"); $$ = new ast_CompUnit(); }
	| constDecl		{ $$ = new ast_CompUnit(); $$->decl_def_list.push_back($1); }
	| varDecl		{ $$ = new ast_CompUnit(); $$->decl_def_list.push_back($1); }
	| funcDef		{ $$ = new ast_CompUnit(); $$->decl_def_list.push_back($1); }
	| compUnit constDecl	{ $$ = $1; $$->decl_def_list.push_back($2); }
	| compUnit varDecl		{ $$ = $1; $$->decl_def_list.push_back($2); }
	| compUnit funcDef		{ $$ = $1; $$->decl_def_list.push_back($2); }
	;


constDecl: CONST INT constDefList SEMI { $$ = new ast_ConstDecl(); $$->type = TYPE_INT; $$->const_def_list = $3->const_def_list; delete $3; }
	;

constDefList: constDef				{ $$ = new ast_ConstDefList(); $$->const_def_list.push_back($1); }
	| constDefList COMMA constDef	{ $$ = $1; $$->const_def_list.push_back($3); }
	;

constDef: IDENT ASSIGN constInitVal					{ $$ = new ast_ConstDef(); $$->id = $1; $$->const_init_val = $3; }
	| IDENT const_bracketList ASSIGN constInitVal	{ $$ = new ast_ConstDef(); $$->id = $1; $$->isArray = true; $$->const_exp = $2->const_exp_list; $$->const_init_val = $4; }
	;

constInitVal: constExp 			{ $$ = new ast_ConstInitVal(); $$->const_exp = $1; }
	| L_BRACE R_BRACE			{ $$ = new ast_ConstInitVal(); }
	| L_BRACE constInitList R_BRACE	{ $$ = new ast_ConstInitVal(); $$->const_init_val_list = $2->const_init_list; delete $2; }
	;

constInitList: constInitVal				{ $$ = new ast_ConstInitList(); $$->const_init_list.push_back($1); }
	| constInitList COMMA constInitVal	{ $$ = $1; $$->const_init_list.push_back($3); }
	;

varDefList: varDef				{ $$ = new ast_VarDefList(); $$->var_def_list.push_back($1); }
	| varDefList COMMA varDef	{ $$ = $1; $$->var_def_list.push_back($3); }
	;

varDecl: INT varDefList SEMI	{ $$ = new ast_VarDecl(); $$->type = TYPE_INT; $$->var_def_list = $2->var_def_list; delete $2; }
	;

varDef: IDENT 					{ $$ = new ast_VarDef(); $$->id = $1; }
	| IDENT ASSIGN initVal		{ $$ = new ast_VarDef(); $$->id = $1; $$->init_val = $3; }
	| IDENT const_bracketList	{ $$ = new ast_VarDef(); $$->isArray = true; $$->id = $1; $$->const_exp = $2->const_exp_list; delete $2; }
	| IDENT const_bracketList ASSIGN initVal { $$ = new ast_VarDef(); $$->isArray = true; $$->id = $1; $$->const_exp = $2->const_exp_list; $$->init_val = $4; delete $2; }
	;

initList: initVal 				{ $$ = new ast_InitList(); $$->init_list.push_back($1); }
	| initList COMMA initVal	{ $$ = $1; $$->init_list.push_back($3); }
	;

initVal: exp 			{ $$ = new ast_InitVal(); $$->exp = $1; }
	| L_BRACE R_BRACE	{ $$ = new ast_InitVal(); }
	| L_BRACE initList R_BRACE	{ $$ = new ast_InitVal(); $$->init_val_list = $2->init_list; delete $2; }
	;

funcDef: VOID IDENT L_PAREN R_PAREN block			{ $$ = new ast_FuncDef(); $$->type = TYPE_VOID; $$->id = $2; $$->block =$5; }
	| VOID IDENT L_PAREN funcFParams R_PAREN block	{ $$ = new ast_FuncDef(); $$->type = TYPE_VOID; $$->id = $2; $$->func_params = $4->func_f_param_list; $$->block = $6; delete $4; }
	| INT IDENT L_PAREN R_PAREN block				{ $$ = new ast_FuncDef(); $$->type = TYPE_INT; $$->id = $2; $$->block = $5; } 
	| INT IDENT L_PAREN funcFParams R_PAREN block	{ $$ = new ast_FuncDef(); $$->type = TYPE_INT; $$->id = $2; $$->func_params = $4->func_f_param_list; $$->block = $6; delete $4; }
	;

funcFParams: funcFParam			{ $$ = new ast_FuncFParams(); $$->func_f_param_list.push_back($1); }
	| funcFParams COMMA funcFParam	{ $$ = $1; $$->func_f_param_list.push_back($3); }
	;

funcFParam: INT IDENT				{ $$ = new ast_FuncFParam(); $$->type = TYPE_INT; $$->id = $2; }
	| INT IDENT func_bracketList	{ $$ = new ast_FuncFParam(); $$->type = TYPE_INT; $$->id = $2; $$->isArray = true; $$->param_array_list = $3->exp_list; delete $3; }
	;

block: L_BRACE blockItems R_BRACE	{ $$ = new ast_Block(); $$->block_item_list = $2->block_items; delete $2; }
	;

blockItems: %empty			{ $$ = new ast_BlockItems(); }
	| blockItems SEMI		{ $$ = $1; }
	| blockItems blockItem	{ $$ = $1; $$->block_items.push_back($2); }

	;

blockItem: constDecl	{ $$ = new ast_BlockItem(); $$->const_decl = $1; }
	| varDecl			{ $$ = new ast_BlockItem(); $$->var_decl = $1; }
	| stmt				{ $$ = new ast_BlockItem(); $$->stmt = $1; }
	;

stmt: block			{ $$ = $1; }
	| exp SEMI		{ $$ = $1;}
	| assignStmt	{ $$ = $1; }
	| selectStmt	{ $$ = $1; }
	| iterationStmt	{ $$ = $1; }
	| breakStmt		{ $$ = $1; }
	| continueStmt	{ $$ = $1; }
	| returnStmt	{ $$ = $1; }
	;

breakStmt: BREAK SEMI	{ $$ = new ast_BreakStmt(); }
	;

continueStmt: CONTINUE SEMI	{$$ = new ast_ContinueStmt(); }
	;

returnStmt: RETURN SEMI	{ $$ = new ast_ReturnStmt(); }
	| RETURN exp SEMI	{ $$ = new ast_ReturnStmt(); $$->exp = $2; }
	;

selectStmt: IF L_PAREN cond R_PAREN stmt		{ $$ = new ast_SelectStmt(); $$->cond = $3; $$->if_stmt = $5; }
	| IF L_PAREN cond R_PAREN stmt ELSE stmt	{ $$ = new ast_SelectStmt(); $$->cond = $3; $$->if_stmt = $5; $$->else_stmt = $7; }
	;

iterationStmt: WHILE L_PAREN cond R_PAREN stmt	{ $$ = new ast_IterationStmt(); $$->cond = $3; $$->stmt = $5; }
	;

assignStmt: lVal ASSIGN exp SEMI { $$ = new ast_AssignStmt(); $$->l_val = $1; $$->exp = $3; }
	;

exp: addExp	{ $$ = $1; }
	;

cond: lorExp	{ $$ = $1; }
	;

lVal: IDENT	{ $$ = new ast_LVal(); $$->id = $1; }
	| lVal L_BRACKET exp R_BRACKET	{ $$ = $1; $$->array_exp_list.push_back($3); }
	;


primaryExp:	number 			{ $$ = $1; }
	| lVal					{ $$ = $1; }
	| L_PAREN exp R_PAREN	{ $$ = $2; }
	;

number: INTCONST { $$ = new ast_Number(); $$->num = $1; }
	;

unaryExp: primaryExp	{ $$ = $1; }
	| funCall			{ $$ = $1; }
	| ADD unaryExp		{ ast_UnaryExp* t = new ast_UnaryExp(); $$ = t; t->op = OP_POS; t->unary_exp = $2; }
	| SUB unaryExp		{ ast_UnaryExp* t = new ast_UnaryExp(); $$ = t; t->op = OP_NEG; t->unary_exp = $2; }
	| NOT unaryExp		{ ast_UnaryExp* t = new ast_UnaryExp(); $$ = t; t->op = OP_NOT; t->unary_exp = $2; }
	;

funCall: IDENT L_PAREN funcRParams R_PAREN { $$ = new ast_FunCall(); $$->id = $1; $$->fun_r_params = $3->exp_list; delete $3; }
	;

funcRParams: %empty			{ $$ = new ast_FuncRParams(); }
	| exp					{ $$=  new ast_FuncRParams(); $$->exp_list.push_back($1); }
	| funcRParams COMMA exp	{ $$ = $1; $$->exp_list.push_back($3); }
	;

mulExp: unaryExp			{ $$ = $1; }
	| mulExp MUL unaryExp	{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op =OP_MUL; t->exp2 = $3; }
	| mulExp DIV unaryExp	{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op =OP_DIV; t->exp2 = $3; }
	| mulExp MOD unaryExp	{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op =OP_MOD; t->exp2 = $3; }
	;

addExp: mulExp				{ $$ = $1; }
	| addExp ADD mulExp		{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op = OP_ADD; t->exp2 = $3; }
	| addExp SUB mulExp		{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op = OP_SUB; t->exp2 = $3; }
	;

relExp: addExp				{ $$ = $1; }
	| relExp GT addExp		{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op = OP_GT; t->exp2 = $3; }
	| relExp LT addExp		{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op = OP_LT; t->exp2 = $3; }
	| relExp GTE addExp		{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op = OP_GTE; t->exp2 = $3; }
	| relExp LTE addExp		{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp2 = $1; t->op = OP_LTE; t->exp2 = $3; }
	;

eqExp: relExp			{ $$ = $1; }
	| eqExp EQ relExp	{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op=OP_EQ; t->exp2 = $3; }
	| eqExp NEQ relExp	{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op=OP_NEQ; t->exp2 = $3; }
	;

landExp: eqExp				{ $$ = $1; }
	| landExp AND eqExp		{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op = OP_AND; t->exp2 = $3; }
	;

lorExp: landExp				{ $$ = $1; }
	| lorExp OR landExp		{ ast_BinaryExp* t = new ast_BinaryExp(); $$ = (ast_Expression*)t; t->exp1 = $1; t->op = OP_OR; t->exp2 = $3; }
	;

constExp: addExp	{ $$ = $1; }
	;

const_bracketList: L_BRACKET constExp R_BRACKET { $$ = new ast_ConstBracketList(); $$->const_exp_list.push_back($2); }
	| const_bracketList L_BRACKET constExp R_BRACKET	{ $$ = $1; $$->const_exp_list.push_back($3); }
	;

func_bracketList: L_BRACKET  R_BRACKET	{ $$ = new ast_BracketList(); $$->exp_list.push_back(NULL); }
	| L_BRACKET exp R_BRACKET			{ $$ = new ast_BracketList(); $$->exp_list.push_back($2); }
	| func_bracketList L_BRACKET exp R_BRACKET	{ $$ = $1; $$->exp_list.push_back($3); }
	;

%%

void Marker::Parser::error(const Marker::location& location,const std::string& message){
  std::cout<<"msg:"<<message
           <<", error happened at: "<<location<<std::endl;
}

