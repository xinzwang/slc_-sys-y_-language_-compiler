#ifndef JSON_H
#define JSON_H
#include "Ast.hpp"
#include <fstream>
#include <iostream>
#include <string>

class JsonGen : Visiter {
  public:
	std::string file;
	void print(Ast &root, std::string path);
	void visit(ast_CompUnit &);
	void visit(ast_ConstDecl &);
	void visit(ast_ConstDef &);
	void visit(ast_ConstInitVal &);
	void visit(ast_VarDecl &);
	void visit(ast_VarDef &);
	void visit(ast_InitVal &);
	void visit(ast_FuncDef &);
	void visit(ast_FuncFParam &);
	void visit(ast_Block &);
	void visit(ast_BlockItem &);
	void visit(ast_LVal &);
	void visit(ast_Number &);
	void visit(ast_UnaryExp &);
	void visit(ast_BinaryExp &);
	void visit(ast_FunCall &);
	void visit(ast_AssignStmt &);
	void visit(ast_SelectStmt &);
	void visit(ast_IterationStmt &);
	void visit(ast_BreakStmt &);
	void visit(ast_ContinueStmt &);
	void visit(ast_ReturnStmt &);
};

#endif