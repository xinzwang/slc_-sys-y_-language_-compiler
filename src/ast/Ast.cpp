#include "Ast.hpp"

//主节点
void ast_CompUnit::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_ConstDecl::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_ConstDef::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_ConstInitVal::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_VarDecl::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_VarDef::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_InitVal::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_FuncDef::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_FuncFParam::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_Block::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_BlockItem::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_LVal::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_Number::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_UnaryExp::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_BinaryExp::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_FunCall::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_AssignStmt::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_SelectStmt::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_IterationStmt::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_BreakStmt::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_ContinueStmt::accept(Visiter &visitor) { visitor.visit(*this); }
void ast_ReturnStmt::accept(Visiter &visitor) { visitor.visit(*this); }
//辅助节点
void ast_VarDefList::accept(Visiter &visitor) { return; }
void ast_ConstDefList::accept(Visiter &visitor) { return; }
void ast_BracketList::accept(Visiter &visitor) { return; }
void ast_ConstBracketList::accept(Visiter &visitor) { return; }
void ast_FuncFParams::accept(Visiter &visitor) { return; }
void ast_FuncRParams::accept(Visiter &visitor) { return; }
void ast_BlockItems::accept(Visiter &visitor) { return; }
void ast_InitList::accept(Visiter &visitor) { return; }
void ast_ConstInitList::accept(Visiter &visitor) { return; }

ast_Node::~ast_Node( ) { return; }

ast_Stmt::ast_Stmt( ) {
	this->stmt_type = STMT;
}

ast_Block::ast_Block( ) {
	this->stmt_type = BLOCK;
}

ast_AssignStmt::ast_AssignStmt( ) {
	this->stmt_type = ASSIGN;
}

ast_SelectStmt::ast_SelectStmt( ) {
	this->stmt_type = SELECT;
}

ast_IterationStmt::ast_IterationStmt( ) {
	this->stmt_type = ITERATION;
}

ast_BreakStmt::ast_BreakStmt( ) {
	this->stmt_type = BREAK;
}

ast_ContinueStmt::ast_ContinueStmt( ) {
	this->stmt_type = CONTINUE;
}

ast_Number::ast_Number( ) {
	this->exp_type = NUMBER;
	this->stmt_type = EXP;
}
ast_BinaryExp::ast_BinaryExp( ) {
	this->exp_type = BINARY;
	this->stmt_type = EXP;
}
ast_LVal::ast_LVal( ) {
	this->exp_type = LVAL;
	this->stmt_type = EXP;
}
ast_FunCall::ast_FunCall( ) {
	this->exp_type = FUN_CALL;
}
ast_UnaryExp::ast_UnaryExp( ) {
	this->exp_type = UNARY;
	this->stmt_type = EXP;
}
ast_ReturnStmt::ast_ReturnStmt( ) {
	this->stmt_type = RETURN;
}

ast_Expression::ast_Expression( ) {
	this->exp_type = NONE;
	this->stmt_type = EXP;
}