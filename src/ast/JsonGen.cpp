#include "JsonGen.hpp"

void JsonGen::print(Ast &tree, std::string path) {
	this->visit(*(tree.root));

	std::ofstream f;
	f.open(path);
	f << this->file;
	f.close( );
	return;
}

void JsonGen::visit(ast_CompUnit &cur) {
	file.append("{");
	//全局声明表
	file.append("\"Global decl def list\":[");
	for (ast_Node *node : cur.decl_def_list) {
		node->accept(*this);
		file.append(",");
	}
	if (!cur.decl_def_list.empty( )) {
		file.pop_back( );
	}
	file.append("]");
	// //常量定义
	// file.append("\"ConstDecl\":[");
	// for (ast_ConstDecl *node : cur.const_decl_list) {
	// 	node->accept(*this);
	// 	file.append(",");
	// }
	// if (!cur.const_decl_list.empty( )) {
	// 	file.pop_back( );
	// }
	// file.append("],");
	// //变量定义
	// file.append("\"VarDecl\":[");
	// for (ast_VarDecl *node : cur.var_decl_list) {
	// 	node->accept(*this);
	// 	file.append(",");
	// }
	// if (!cur.const_decl_list.empty( )) {
	// 	file.pop_back( );
	// }
	// file.append("],");
	// //函数定义
	// file.append("\"FuncDef\":[");
	// for (ast_FuncDef *node : cur.fun_def_list) {
	// 	node->accept(*this);
	// 	file.append(",");
	// }
	// if (!cur.fun_def_list.empty( )) {
	// 	file.pop_back( );
	// }
	// file.append("]");
	file.append("}");
}
void JsonGen::visit(ast_ConstDecl &cur) {
	file.append("{");
	file.append("\"Type\":\"INT\",");

	file.append("\"ConstDef\":[");
	for (ast_ConstDef *node : cur.const_def_list) {
		node->accept(*this);
		file.append(",");
	}
	if (!cur.const_def_list.empty( )) {
		file.pop_back( );
	}
	file.append("]");

	file.append("}");
}
void JsonGen::visit(ast_ConstDef &cur) {
	file.append("{");

	file.append("\"ID\":\"");
	file.append(cur.id);
	file.append("\"");
	file.append(",");

	if (cur.isArray) {
		file.append("\"isArray\":\"true\",");
		file.append("\"Dimension\":[");
		for (ast_Expression *node : cur.const_exp) {
			node->accept(*this);
			file.append(",");
		}
		if (!cur.const_exp.empty( )) {
			file.pop_back( );
		}
		file.append("],");
	} else {
		file.append("\"isArray\":\"false\",");
	}

	file.append("\"ConstInitVal\":");
	if (cur.const_init_val != NULL) {
		this->visit(*(cur.const_init_val));
	} else {
		file.append("null");
	}

	file.append("}");
}
void JsonGen::visit(ast_ConstInitVal &cur) {
	file.append("{");

	file.append("\"Dimension\":[");
	for (std::size_t i = 0; i < cur.bounds.size( ); i++) {
		file.append(to_string(cur.bounds[i]));
		file.append(",");
	}
	if (cur.bounds.size( ) != 0) {
		file.pop_back( );
	}
	file.append("]");
	file.append(",");

	if (cur.const_exp == NULL) {
		file.append("\"ConstInitVal\":[");
		for (ast_ConstInitVal *node1 : cur.const_init_val_list) {
			node1->accept(*this);
			file.append(",");
		}
		if (!cur.const_init_val_list.empty( )) {
			file.pop_back( );
		}
		file.append("]");

	} else {
		file.append("\"ConstExp\":");
		cur.const_exp->accept(*this);
	}

	file.append("}");
}
void JsonGen::visit(ast_VarDecl &cur) {
	file.append("{");

	file.append("\"TYPE\":\"");
	if (cur.type == TYPE_INT) {
		file.append("INT");
	} else if (cur.type == TYPE_VOID) {
		file.append("VOID");
	}
	file.append("\"");
	file.append(",");

	file.append("\"VarDef\":[");
	for (ast_VarDef *node : cur.var_def_list) {
		node->accept(*this);
		file.append(",");
	}
	if (!cur.var_def_list.empty( )) {
		file.pop_back( );
	}
	file.append("]");

	file.append("}");
}
void JsonGen::visit(ast_VarDef &cur) {
	file.append("{");

	file.append("\"ID\":\"");
	file.append(cur.id);
	file.append("\"");
	file.append(",");

	if (cur.isArray) {
		file.append("\"isArray\":\"true\",");
		file.append("\"Dimension\":[");
		for (ast_Expression *node : cur.const_exp) {
			node->accept(*this);
			file.append(",");
		}
		if (!cur.const_exp.empty( )) {
			file.pop_back( );
		}
		file.append("],");
	} else {
		file.append("\"isArray\":\"false\",");
	}

	file.append("\"InitVal\":");
	if (cur.init_val != NULL) {
		this->visit(*(cur.init_val));
	} else {
		file.append("null");
	}

	file.append("}");
}
void JsonGen::visit(ast_InitVal &cur) {
	file.append("{");

	file.append("\"Dimension\":[");
	for (std::size_t i = 0; i < cur.bounds.size( ); i++) {
		file.append(to_string(cur.bounds[i]));
		file.append(",");
	}
	if (cur.bounds.size( ) != 0) {
		file.pop_back( );
	}
	file.append("]");
	file.append(",");

	if (cur.exp == NULL) {
		if (cur.init_val_list.empty( )) {
			printf("InitVal Error!!!!\n");
		}
		file.append("\"InitVal\":[");
		for (ast_InitVal *node1 : cur.init_val_list) {
			node1->accept(*this);
			file.append(",");
		}
		if (!cur.init_val_list.empty( )) {
			file.pop_back( );
		}
		file.append("]");

	} else {
		file.append("\"Exp\":");
		cur.exp->accept(*this);
	}

	file.append("}");
}
void JsonGen::visit(ast_FuncDef &cur) {
	file.append("{");

	switch (cur.type) {
		case TYPE_INT:
			file.append("\"TYPE\":\"INT\",");
			break;
		case TYPE_VOID:
			file.append("\"TYPE\":\"VOID\",");
			break;
		default:
			printf("[ERROR]: expect Type, but get something else\n");
			break;
	}

	file.append("\"ID\":\"");
	file.append(cur.id);
	file.append("\",");

	file.append("\"Params\":[");
	for (ast_FuncFParam *node : cur.func_params) {
		node->accept(*this);
		file.append(",");
	}
	if (!cur.func_params.empty( )) {
		file.pop_back( );
	}
	file.append("],");

	file.append("\"block\":");
	cur.block->accept(*this);

	file.append("}");
}
void JsonGen::visit(ast_FuncFParam &cur) {
	file.append("{");

	file.append("\"TYPE\":\"INT\",");

	file.append("\"ID\":\"");
	file.append(cur.id);
	file.append("\",");

	file.append("\"isArray\":");
	if (cur.isArray) {
		file.append("true,");
		file.append("\"ParamList\":[");
		for (ast_Expression *node : cur.param_array_list) {
			if (node == NULL) {	 //第一维度是NULL
				file.append("{");
				file.append("\"val\":\"NULL\"");
				file.append("}");
			} else {
				node->accept(*this);
			}
			file.append(",");
		}
		if (!cur.param_array_list.empty( )) {
			file.pop_back( );
		}
		file.append("]");
	} else {
		file.append("false");
	}

	file.append("}");
}

void JsonGen::visit(ast_Block &cur) {
	file.append("[");
	for (ast_BlockItem *node : cur.block_item_list) {
		node->accept(*this);
		file.append(",");
	}
	if (!cur.block_item_list.empty( )) {
		file.pop_back( );
	}
	file.append("]");
}
void JsonGen::visit(ast_BlockItem &cur) {
	if (cur.const_decl != NULL) {
		cur.const_decl->accept(*this);
	}
	if (cur.var_decl != NULL) {
		cur.var_decl->accept(*this);
	}
	if (cur.stmt != NULL) {
		cur.stmt->accept(*this);
	}
}
void JsonGen::visit(ast_LVal &cur) {
	file.append("{");

	file.append("\"exptype\":\"lVal\",");

	file.append("\"ID\":\"");
	file.append(cur.id);
	file.append("\",");

	file.append("\"Dimension\":[");

	int flag = 0;
	for (ast_Expression *node : cur.array_exp_list) {
		if (!flag)
			flag = 1;
		else
			file.append(",");
		node->accept(*this);
	}
	file.append("]");

	file.append("}");
}
void JsonGen::visit(ast_Number &cur) {
	file.append("{");

	file.append("\"exptype\":\"Number\",");

	file.append("\"type\":\"INT\",");

	file.append("\"val\":");
	file.append(to_string(cur.num));

	file.append("}");
}

void JsonGen::visit(ast_UnaryExp &cur) {
	file.append("{");
	file.append("\"exptype\":\"UnaryExp\",");

	switch (cur.op) {
		case OP_POS:
			file.append("\"OP\":\"+\",");
			break;
		case OP_NEG:
			file.append("\"OP\":\"-\",");
			break;
		case OP_NOT:
			file.append("\"OP\":\"!\",");
			break;
		default:
			printf("[ERROR]: expect unary_op, but get something else\n");
			break;
	}

	file.append("\"exp\":");
	cur.unary_exp->accept(*this);

	file.append("}");
}
void JsonGen::visit(ast_BinaryExp &cur) {
	file.append("{");
	file.append("\"exptype\":\"BinaryExp\",");
	switch (cur.op) {
		case OP_GT:
			file.append("\"OP\":\">\",");
			break;
		case OP_LT:
			file.append("\"OP\":\"<\",");
			break;
		case OP_GTE:
			file.append("\"OP\":\">=\",");
			break;
		case OP_LTE:
			file.append("\"OP\":\"<=\",");
			break;
		case OP_EQ:
			file.append("\"OP\":\"==\",");
			break;
		case OP_NEQ:
			file.append("\"OP\":\"!=\",");
			break;
		case OP_ADD:
			file.append("\"OP\":\"+\",");
			break;
		case OP_SUB:
			file.append("\"OP\":\"-\",");
			break;
		case OP_MUL:
			file.append("\"OP\":\"*\",");
			break;
		case OP_DIV:
			file.append("\"OP\":\"/\",");
			break;
		case OP_MOD:
			file.append("\"OP\":\"%\",");
			break;
		case OP_AND:
			file.append("\"OP\":\"&&\",");
			break;
		case OP_OR:
			file.append("\"OP\":\"||\",");
			break;
		default:
			printf("[ERROR]: expect binary_op, but get something else\n");
			break;
	}

	file.append("\"exp1\":");
	cur.exp1->accept(*this);
	file.append(",");

	file.append("\"exp2\":");
	cur.exp2->accept(*this);

	file.append("}");
}
void JsonGen::visit(ast_FunCall &cur) {
	file.append("{");
	file.append("\"exptype\":\"FunCall\",");

	file.append("\"ID\":\"");
	file.append(cur.id);
	file.append("\",");

	file.append("\"Params\":[");
	for (ast_Expression *node : cur.fun_r_params) {
		node->accept(*this);
		file.append(",");
	}
	if (!cur.fun_r_params.empty( )) {
		file.pop_back( );
	}
	file.append("]");

	file.append("}");
}
void JsonGen::visit(ast_AssignStmt &cur) {
	file.append("{");
	file.append("\"AssignStmt\":[");
	cur.l_val->accept(*this);
	file.append(",");
	ast_Expression *node = cur.exp;
	node->accept(*this);
	file.append("]");
	file.append("}");
}
void JsonGen::visit(ast_SelectStmt &cur) {
	file.append("{");
	file.append("\"TYPE\":\"SelectStmt\",");
	file.append("\"cond\":");
	cur.cond->accept(*this);
	file.append(",");

	if (cur.if_stmt != NULL) {
		file.append("\"if_stmt\":");
		cur.if_stmt->accept(*this);
	}

	if (cur.else_stmt != NULL) {
		file.append(",");
		file.append("\"else_stmt\":");
		cur.else_stmt->accept(*this);
	}

	file.append("}");
}
void JsonGen::visit(ast_IterationStmt &cur) {
	file.append("{");
	file.append("\"TYPE\":\"IterationStmt\",");
	file.append("\"cond\":");
	ast_Expression *node = cur.cond;
	node->accept(*this);
	file.append(",");
	file.append("\"stmt\":");
	cur.stmt->accept(*this);
	file.append("}");
}
void JsonGen::visit(ast_BreakStmt &cur) {
	file.append("{");
	file.append("\"BreakStmt\"");
	file.append("}");
}
void JsonGen::visit(ast_ContinueStmt &cur) {
	file.append("{");
	file.append("\"ContinueStmt\"");
	file.append("}");
}
void JsonGen::visit(ast_ReturnStmt &cur) {
	file.append("{");
	file.append("\"TYPE\":\"ReturnStmt\",");
	ast_Expression *node = cur.exp;
	file.append("\"val\":");
	if (node == NULL) {
		file.append("\"NULL\"");
	} else {
		node->accept(*this);
	}
	file.append("}");
}