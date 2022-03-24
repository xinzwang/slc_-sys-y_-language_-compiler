#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <vector>

#include "Type.hpp"

enum EXP_TYPE {
	NONE,
	LVAL,
	FUN_CALL,
	NUMBER,
	UNARY,

	BINARY
};

enum STMT_TYPE {
	STMT,
	EXP,
	BLOCK,
	ASSIGN,
	SELECT,
	ITERATION,
	BREAK,
	CONTINUE,
	RETURN,
};

class ast_Node;		 //节点
class ast_CompUnit;	 //编译单元
// Declaration
class ast_ConstDecl;	 //常量声明
class ast_ConstDef;		 //常量定义
class ast_ConstInitVal;	 //常量初值
class ast_VarDecl;		 //变量声明
// Definition
class ast_VarDef;	   //变量定义
class ast_InitVal;	   //变量初值
class ast_FuncDef;	   //函数定义
class ast_FuncFParam;  //函数形参

// Block
class ast_Stmt;		  //语句基类
class ast_Block;	  //语句块
class ast_BlockItem;  //语句块项

// Expression
class ast_Expression;	//表达式基类
class ast_LVal;			//左值表达式
class ast_Number;		//数值
class ast_UnaryExp;		//一元表达式
class ast_FuncRParams;	//函数实参列表
class ast_BinaryExp;

//其他节点
class ast_FunCall;		  //函数调用
class ast_AssignStmt;	  //赋值语句
class ast_SelectStmt;	  //分支语句
class ast_IterationStmt;  //循环语句
class ast_BreakStmt;	  //跳出语句
class ast_ContinueStmt;	  //继续语句
class ast_ReturnStmt;	  //返回语句

class ast_ConstDefList;	 //常量参数定义表
class ast_VarDefList;	 //变量参数定义表

class ast_InitList;		  //初始化列表
class ast_ConstInitList;  //常量初始化列表
class ast_BlockItems;	  //语句列表
class ast_FuncFParams;	  //函数形参表

//Visiter 提供访问树的接口
class Visiter {
   public:
	virtual void visit(ast_CompUnit &) = 0;
	virtual void visit(ast_ConstDecl &) = 0;
	virtual void visit(ast_ConstDef &) = 0;
	virtual void visit(ast_ConstInitVal &) = 0;
	virtual void visit(ast_VarDecl &) = 0;
	virtual void visit(ast_VarDef &) = 0;
	virtual void visit(ast_InitVal &) = 0;
	virtual void visit(ast_FuncDef &) = 0;
	virtual void visit(ast_FuncFParam &) = 0;
	virtual void visit(ast_Block &) = 0;
	virtual void visit(ast_BlockItem &) = 0;
	virtual void visit(ast_LVal &) = 0;
	virtual void visit(ast_Number &) = 0;
	virtual void visit(ast_UnaryExp &) = 0;
	virtual void visit(ast_BinaryExp &) = 0;
	virtual void visit(ast_FunCall &) = 0;
	virtual void visit(ast_AssignStmt &) = 0;
	virtual void visit(ast_SelectStmt &) = 0;
	virtual void visit(ast_IterationStmt &) = 0;
	virtual void visit(ast_BreakStmt &) = 0;
	virtual void visit(ast_ContinueStmt &) = 0;
	virtual void visit(ast_ReturnStmt &) = 0;
};

class Ast {
   public:
	ast_CompUnit *root;
};

//使用std命名空间
using namespace std;

class ast_Node {
   public:
	virtual void accept(Visiter &visiter) = 0;
	virtual ~ast_Node( );
};

// class ast_CompUnit : public ast_Node {
//   public:
// 	vector<ast_ConstDecl *> const_decl_list; //常量声明
// 	vector<ast_VarDecl *> var_decl_list;	 //变量声明
// 	vector<ast_FuncDef *> fun_def_list;		 //函数定义
// 	void accept(Visiter &visiter);
// };
class ast_CompUnit : public ast_Node {
   public:
	vector<ast_Node *> decl_def_list;  //全局声明表
	void accept(Visiter &visiter);
};

class ast_ConstDecl : public ast_Node {
   public:
	Type type;								//常量类型
	vector<ast_ConstDef *> const_def_list;	//常量定义列表
	void accept(Visiter &visiter);
};

class ast_ConstDef : public ast_Node {
   public:
	string id;							 //标识符
	bool isArray;						 //是否为数组
	vector<ast_Expression *> const_exp;	 //数组-维度指定
	ast_ConstInitVal *const_init_val;	 //常量初始化数值
	void accept(Visiter &visiter);
};

class ast_ConstInitVal : public ast_Node {
   public:
	vector<int> bounds;								 //维度
	ast_Expression *const_exp;						 //常量表达式
	vector<ast_ConstInitVal *> const_init_val_list;	 //初始化列表
	void accept(Visiter &visiter);
};

class ast_VarDecl : public ast_Node {
   public:
	Type type;
	vector<ast_VarDef *> var_def_list;	//变量定义列表
	void accept(Visiter &visiter);
};

class ast_VarDef : public ast_Node {
   public:
	string id;							 //标识符
	bool isArray;						 //是否为数组
	vector<ast_Expression *> const_exp;	 //数组-维度指定
	ast_InitVal *init_val;				 //初始化数值
	void accept(Visiter &visiter);
};

class ast_InitVal : public ast_Node {
   public:
	vector<int> bounds;					  //维度
	ast_Expression *exp;				  //表达式
	vector<ast_InitVal *> init_val_list;  //初始化列表
	void accept(Visiter &visiter);
};

class ast_FuncDef : public ast_Node {
   public:
	Type type;
	string id;
	vector<ast_FuncFParam *> func_params;
	ast_Block *block;
	void accept(Visiter &visiter);
};

class ast_FuncFParam : public ast_Node {
   public:
	Type type;									//类型
	string id;									//标识符
	bool isArray;								//是否为数组
	vector<ast_Expression *> param_array_list;	//数组参数列表    可修改
	void accept(Visiter &visiter);
};

class ast_Stmt : public ast_Node {
   public:
	STMT_TYPE stmt_type;
	ast_Stmt( );
};

class ast_Block : public ast_Stmt {
   public:
	vector<ast_BlockItem *> block_item_list;  //语句列表
	ast_Block( );
	void accept(Visiter &visiter);
};

class ast_BlockItem : public ast_Node {
   public:
	ast_ConstDecl *const_decl;
	ast_VarDecl *var_decl;
	ast_Stmt *stmt;	 //语句
	void accept(Visiter &visiter);
};

class ast_AssignStmt : public ast_Stmt {
   public:
	ast_LVal *l_val;  //左值表达式
	ast_Expression *exp;
	ast_AssignStmt( );
	void accept(Visiter &visiter);
};

class ast_SelectStmt : public ast_Stmt {
   public:
	ast_Expression *cond;  //条件表达式
	ast_Stmt *if_stmt;	   //if语句块
	ast_Stmt *else_stmt;   //else语句块
	ast_SelectStmt( );
	void accept(Visiter &visiter);
};

class ast_IterationStmt : public ast_Stmt {
   public:
	ast_Expression *cond;  //条件表达式
	ast_Stmt *stmt;		   //循环语句块
	ast_IterationStmt( );
	void accept(Visiter &visiter);
};

class ast_BreakStmt : public ast_Stmt {
   public:
	ast_BreakStmt( );
	void accept(Visiter &visiter);
};

class ast_ContinueStmt : public ast_Stmt {
   public:
	ast_ContinueStmt( );
	void accept(Visiter &visiter);
};

class ast_ReturnStmt : public ast_Stmt {
   public:
	ast_Expression *exp;
	ast_ReturnStmt( );
	void accept(Visiter &visiter);
};

class ast_Expression : public ast_Stmt {
   public:
	EXP_TYPE exp_type;
	ast_Expression( );
};

class ast_LVal : public ast_Expression {
   public:
	string id;
	vector<ast_Expression *> array_exp_list;
	ast_LVal( );
	void accept(Visiter &visiter);
};

class ast_Number : public ast_Expression {
   public:
	int32_t num;
	ast_Number( );
	void accept(Visiter &visiter);
};

class ast_UnaryExp : public ast_Expression {
   public:
	Unary_OP op;
	ast_Expression *unary_exp;
	ast_UnaryExp( );
	void accept(Visiter &visiter);
};

class ast_FunCall : public ast_Expression {
   public:
	string id;
	vector<ast_Expression *> fun_r_params;
	ast_FunCall( );
	void accept(Visiter &visiter);
};

class ast_BinaryExp : public ast_Expression {
   public:
	Binary_OP op;
	ast_Expression *exp1;
	ast_Expression *exp2;
	ast_BinaryExp( );
	void accept(Visiter &visiter);
};

//辅助节点
class ast_VarDefList : public ast_Node {
   public:
	vector<ast_VarDef *> var_def_list;
	void accept(Visiter &visiter);
};

class ast_ConstDefList : public ast_Node {
   public:
	vector<ast_ConstDef *> const_def_list;
	void accept(Visiter &visiter);
};

class ast_BracketList : public ast_Node {
   public:
	vector<ast_Expression *> exp_list;
	void accept(Visiter &visiter);
};

class ast_ConstBracketList : public ast_Node {
   public:
	vector<ast_Expression *> const_exp_list;
	void accept(Visiter &visiter);
};

class ast_FuncFParams : public ast_Node {
   public:
	vector<ast_FuncFParam *> func_f_param_list;
	void accept(Visiter &visiter);
};

class ast_FuncRParams : public ast_Node {
   public:
	vector<ast_Expression *> exp_list;
	void accept(Visiter &visiter);
};

class ast_BlockItems : public ast_Node {
   public:
	vector<ast_BlockItem *> block_items;
	void accept(Visiter &visiter);
};

class ast_InitList {
   public:
	vector<ast_InitVal *> init_list;
	void accept(Visiter &visiter);
};

class ast_ConstInitList {
   public:
	vector<ast_ConstInitVal *> const_init_list;
	void accept(Visiter &visiter);
};
#endif