#ifndef IRGEN_HPP
#define IRGEN_HPP

#include "Ast.hpp"
#include "Ir.hpp"

#define INIT_VAL 0	//默认的初始化数值

class IrGen : public Visiter {
   private:
   public:
	IrContext context;
	IrBuilder builder;

	// IrGen();
	// ~IrGen();

	void visit(ast_CompUnit &node);
	void visit(ast_ConstDecl &node);
	void visit(ast_ConstDef &node);
	void visit(ast_ConstInitVal &node);
	void visit(ast_VarDecl &node);
	void visit(ast_VarDef &node);
	void visit(ast_InitVal &node);
	void visit(ast_FuncDef &node);
	void visit(ast_FuncFParam &node);
	void visit(ast_Block &node);
	void visit(ast_BlockItem &node);
	void visit(ast_LVal &node);
	void visit(ast_Number &node);
	void visit(ast_UnaryExp &node);
	void visit(ast_BinaryExp &node);
	void visit(ast_FunCall &node);
	void visit(ast_AssignStmt &node);
	void visit(ast_SelectStmt &node);
	void visit(ast_IterationStmt &node);
	void visit(ast_BreakStmt &node);
	void visit(ast_ContinueStmt &node);
	void visit(ast_ReturnStmt &node);
};

#endif