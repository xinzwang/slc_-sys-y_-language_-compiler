#include "IrGen.hpp"

#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

void IrGen::visit(ast_CompUnit &node) {
	std::cout << "IrGen::visit ast_CompUnit" << endl;
	context.const_states.push(false);
	context.scope.enter( );
	// TODO: 初始化 Builder
	builder.init(&context.scope);

	// 添加库函数
	ValuePtr f_getint(new Function("getint", TYPE_INT));
	auto f = std::static_pointer_cast<Function>(f_getint);
	f->isLibrary = true;
	context.scope.insert_item(f_getint);
	// builder.addFunction(f_getint);

	ValuePtr f_getch(new Function("getch", TYPE_INT));
	f = std::static_pointer_cast<Function>(f_getch);
	f->isLibrary = true;
	context.scope.insert_item(f_getch);
	// builder.addFunction(f_getch);

	ValuePtr f_getarray(new Function("getarray", TYPE_INT));
	f = std::static_pointer_cast<Function>(f_getarray);
	f->isLibrary = true;
	FParam *f_getarray_arg1(new FParam("getarray_arg1", TYPE_INT, true));
	f_getarray_arg1->dim.push_back(0);
	f->fparam_lst.push_back(f_getarray_arg1);
	context.scope.insert_item(f_getarray);
	// builder.addFunction(f_getarray);

	ValuePtr f_putint(new Function("putint", TYPE_VOID));
	f = std::static_pointer_cast<Function>(f_putint);
	f->isLibrary = true;
	FParam *f_putint_arg1(new FParam("putint_arg1", TYPE_INT, false));
	f->fparam_lst.push_back(f_putint_arg1);
	context.scope.insert_item(f_putint);
	// builder.addFunction(f_putint);

	ValuePtr f_putch(new Function("putch", TYPE_VOID));
	f = std::static_pointer_cast<Function>(f_putch);
	f->isLibrary = true;
	FParam *f_putch_arg1(new FParam("putch_arg1", TYPE_INT, false));
	f->fparam_lst.push_back(f_putch_arg1);
	context.scope.insert_item(f_putch);
	// builder.addFunction(f_putch);

	ValuePtr f_putarray(new Function("putarray", TYPE_VOID));
	f = std::static_pointer_cast<Function>(f_putarray);
	f->isLibrary = true;
	FParam *f_putarray_arg1(new FParam("putarray_arg1", TYPE_INT, true));
	f_putarray_arg1->dim.push_back(0);
	f->fparam_lst.push_back(f_putarray_arg1);
	context.scope.insert_item(f_putarray);
	// builder.addFunction(f_putarray);

	ValuePtr f_putf(new Function("putf", TYPE_VOID));
	f = std::static_pointer_cast<Function>(f_putf);
	f->isLibrary = true;
	context.scope.insert_item(f_putf);
	// builder.addFunction(f_putf);

	for (auto n : node.decl_def_list) {
		n->accept(*this);
	}
	// for (auto n : node.const_decl_list) {
	// 	n->accept(*this);
	// }
	// for (auto n : node.var_decl_list) {
	// 	n->accept(*this);
	// }
	// for (auto n : node.fun_def_list) {
	// 	n->accept(*this);
	// }
}

void IrGen::visit(ast_ConstDecl &node) {
	std::cout << "IrGen::visit ast_ConstDecl" << endl;
	for (auto n : node.const_def_list) {
		n->accept(*this);
	}
}

void IrGen::visit(ast_ConstDef &node) {
	std::cout << "IrGen::visit ast_ConstDef" << endl;
	if (node.isArray) { // 处理数组定义
		// 计算数组各维度尺寸，并填充至初始化值节点的尺寸数组
		auto &b = node.const_init_val->bounds;
		b.clear( );
		for (auto n : node.const_exp) {
			// 计算数组维度尺寸，使用常量计算模式
			context.const_states.push(true);
			n->accept(*this);
			context.const_states.pop( );
			// 将计算出的尺寸加入尺寸数组
			ValuePtr v = context.parsing_vals.top( );
			context.parsing_vals.pop( );
			b.push_back(std::static_pointer_cast<ConstInt>(v)->val);
		}
		context.const_states.push(true);
		node.const_init_val->accept(*this);
		context.const_states.pop( );
		ValuePtr val = context.parsing_vals.top( );
		context.parsing_vals.pop( );
		val->name = node.id;
		context.scope.insert_item(val);
		// TODO: 常量空间分配
		if (context.scope.is_global( )) { // 全局常量处理
			val->alloc_addr = builder.addGlobalConst(val);
		} else { // 局部常量处理
			val->alloc_addr = builder.addConst(val);
		}
	} else { // 处理常量定义
		context.const_states.push(true);
		node.const_init_val->accept(*this);
		context.const_states.pop( );
		ValuePtr val = context.parsing_vals.top( );
		context.parsing_vals.pop( );
		val->name = node.id;
		context.scope.insert_item(val);
		// TODO: 常量空间分配
		if (context.scope.is_global( )) { // 全局常量处理
			val->alloc_addr = builder.addGlobalConst(val);
		} else { // 局部常量处理
			val->alloc_addr = builder.addConst(val);
		}
	}
}

void IrGen::visit(ast_ConstInitVal &node) {
	std::cout << "IrGen::visit ast_ConstInitVal" << endl;
	if (node.const_exp != nullptr) { // 单个常量值
		if (node.bounds.empty( )) {	 // 尺寸数组为空，故为单个常量的初始值
			node.const_exp->accept(*this);
		} else { // 尺寸数组不为空，故为数组中落单的初始化常量值
			// 计算这个常量的值
			node.const_exp->accept(*this);
		}
	} else { // 常量值数组
		// 新建数组常量，并填充尺寸数组
		ValuePtr val(new ConstArray( ));
		auto &va = std::static_pointer_cast<ConstArray>(val)->val_arr;
		auto &d = std::static_pointer_cast<ConstArray>(val)->dim;
		d.insert(d.end( ), node.bounds.begin( ), node.bounds.end( ));
		// 计算当前维度和子维度的总元素个数
		int cur_sum = node.bounds[0], sub_sum = 1;
		for (int i = 1; i < (int)node.bounds.size( ); ++i) {
			cur_sum *= node.bounds[i];
			sub_sum *= node.bounds[i];
		}
		context.array_states.push(0); // 开始填充数组当前维度的初始化值，此时无未完整填充子维度标志
		// 计算各元素的初始化值，注意这里的元素可能存在多维
		for (auto n : node.const_init_val_list) {
			// 为初始值数组中的元素节点填充尺寸数组，元素的尺寸维度比初始值数组低一维
			auto &b = n->bounds;
			b.clear( );
			b.insert(b.end( ), node.bounds.begin( ) + 1, node.bounds.end( ));
			// 递归处理元素的子元素
			n->accept(*this);
			ValuePtr v = context.parsing_vals.top( );
			context.parsing_vals.pop( );
			// 对子维度的两种情况进行处理：最后一维、非最后一维
			if (node.bounds.size( ) == 1) { // 若当前维已经是最后一维，元素不存在子元素
				// 将元素值直接以int形式加入初始值数组
				va.push_back(std::static_pointer_cast<ConstInt>(v)->val);
			} else {						   // 若当前维不是最后一维
				if (n->const_exp != nullptr) { // 为数组中落单的初始化常量值
					// 将当前值填入之前未完整填充的子维度
					va.push_back(std::static_pointer_cast<ConstInt>(v)->val);
					int atmp = context.array_states.top( );
					context.array_states.pop( );
					context.array_states.push(atmp + 1);
					if (context.array_states.top( ) >= sub_sum) { // 存在已经完整填充的子维度
						// 已经完整填充的子维度此时已经回填至当前维，故直接清除未完整填充子维度标志
						context.array_states.pop( );
						context.array_states.push(0);
					}
				} else {								   // 为包含子维度的初始化常量数组
					if (context.array_states.top( ) > 0) { // 仍存在未完整填充的子维度
						// 以0填充子维度，并清除未完整填充子维度标志
						// 填充剩余未指明初始化值的数组元素
						int rest = sub_sum - context.array_states.top( );
						for (int i = 0; i < rest; ++i) {
							va.push_back(0);
						}
						context.array_states.pop( );
						context.array_states.push(0);
					}
					// 将元素中的所有子元素值复制进初始值数组
					auto &_va = std::static_pointer_cast<ConstArray>(v)->val_arr;
					va.insert(va.end( ), _va.begin( ), _va.end( ));
				}
			}
		}
		// 填充剩余未指明初始化值的数组元素
		int rest = cur_sum - va.size( );
		for (int i = 0; i < rest; ++i) {
			va.push_back(0);
		}
		// 填充完毕，弹出此维度的未完整填充子维度标志
		context.array_states.pop( );
		context.parsing_vals.push(val);
	}
}

void IrGen::visit(ast_VarDecl &node) {
	std::cout << "IrGen::visit ast_VarDecl" << endl;
	for (auto n : node.var_def_list) {
		n->accept(*this);
	}
}

void IrGen::visit(ast_VarDef &node) {
	std::cout << "IrGen::visit ast_VarDef" << endl;
	if (node.isArray) { // 处理数组定义
		ValuePtr val;
		if (node.init_val == NULL) {
			//初始化列表空
			ValuePtr tmp(new VarArray( ));
			val = tmp;
			if (context.scope.is_global( )) {
				std::static_pointer_cast<VarArray>(val)->isGlobal = true;
				auto &va = std::static_pointer_cast<VarArray>(val)->val_arr;
				auto &d = std::static_pointer_cast<VarArray>(val)->dim;
				// 计算数组各维度尺寸，并填充至初始化值节点的尺寸数组
				d.clear( );
				for (auto n : node.const_exp) {
					// 计算数组维度尺寸，使用常量计算模式
					context.const_states.push(true);
					n->accept(*this);
					context.const_states.pop( );
					// 将计算出的尺寸加入尺寸数组
					ValuePtr v = context.parsing_vals.top( );
					context.parsing_vals.pop( );
					d.push_back(std::static_pointer_cast<ConstInt>(v)->val);
				}
				// 计算总元素个数
				int sum = d[0];
				for (int i = 1; i < (int)d.size( ); ++i) {
					sum *= d[i];
				}
				// 填充未指明初始化值的数组元素
				for (int i = 0; i < sum; ++i) {
					va.push_back(0);
				}
			} else {
				std::static_pointer_cast<VarArray>(val)->isGlobal = false;
				auto &va = std::static_pointer_cast<VarArray>(val)->_val_arr;
				auto &d = std::static_pointer_cast<VarArray>(val)->dim;
				// 计算数组各维度尺寸，并填充至初始化值节点的尺寸数组
				d.clear( );
				for (auto n : node.const_exp) {
					// 计算数组维度尺寸，使用常量计算模式
					context.const_states.push(true);
					n->accept(*this);
					context.const_states.pop( );
					// 将计算出的尺寸加入尺寸数组
					ValuePtr v = context.parsing_vals.top( );
					context.parsing_vals.pop( );
					d.push_back(std::static_pointer_cast<ConstInt>(v)->val);
				}
				// 计算总元素个数
				int sum = d[0];
				for (int i = 1; i < (int)d.size( ); ++i) {
					sum *= d[i];
				}
				// 填充剩余未指明初始化值的数组元素
				VarIntPtr zero(new VarInt(0));
				for (int i = 0; i < sum; ++i) {
					va.push_back(zero);
				}
			}
		} else {
			// 计算数组各维度尺寸，并填充至初始化值节点的尺寸数组
			auto &b = node.init_val->bounds;
			b.clear( );
			for (auto n : node.const_exp) {
				// 计算数组维度尺寸，使用常量计算模式
				context.const_states.push(true);
				n->accept(*this);
				context.const_states.pop( );
				// 将计算出的尺寸加入尺寸数组
				ValuePtr v = context.parsing_vals.top( );
				context.parsing_vals.pop( );
				b.push_back(std::static_pointer_cast<ConstInt>(v)->val);
			}
			if (context.scope.is_global( )) {
				context.const_states.push(true);
				node.init_val->accept(*this);
				context.const_states.pop( );
			} else {
				context.const_states.push(false);
				node.init_val->accept(*this);
				context.const_states.pop( );
			}
			val = context.parsing_vals.top( );
			context.parsing_vals.pop( );
		}
		val->name = node.id;
		std::static_pointer_cast<VarArray>(val)->isGlobal = context.scope.is_global( );
		context.scope.insert_item(val);
		// TODO: 变量空间分配
		if (context.scope.is_global( )) { // 全局变量处理
			val->alloc_addr = builder.addGlobalVar(val);
		} else { // 局部变量处理
			val->alloc_addr = builder.addVar(val);
		}
	}
	//非数组
	else { // 处理变量定义
		if (node.init_val == NULL) {
			// TODO: 变量空间分配
			//初始化列表 空
			if (context.scope.is_global( )) { // 全局变量处理
				ValuePtr val(new VarInt(INIT_VAL));
				val->name = node.id;
				context.scope.insert_item(val);
				val->alloc_addr = builder.addGlobalVar(val);
			} else { // 局部变量处理
				ConstIntPtr zero(new ConstInt(0));
				ValuePtr val(new VarInt(zero));
				val->name = node.id;
				context.scope.insert_item(val);
				val->alloc_addr = builder.addVar(val);
			}
		} else {
			//初始化列表 非空
			// TODO: 变量空间分配
			if (context.scope.is_global( )) { // 全局变量处理
				context.const_states.push(true);
				node.init_val->accept(*this);
				context.const_states.pop( );
				ConstIntPtr val = std::static_pointer_cast<ConstInt>(context.parsing_vals.top( ));
				context.parsing_vals.pop( );
				ValuePtr v(new VarInt(val->val, node.id));
				context.scope.insert_item(v);
				v->alloc_addr = builder.addGlobalVar(v);
			} else { // 局部变量处理
				context.const_states.push(false);
				node.init_val->accept(*this);
				context.const_states.pop( );
				ValuePtr val = context.parsing_vals.top( );
				context.parsing_vals.pop( );
				ValuePtr v(new VarInt(val, node.id));
				context.scope.insert_item(v);
				v->alloc_addr = builder.addVar(v);
			}
		}
	}
}

void IrGen::visit(ast_InitVal &node) {
	std::cout << "IrGen::visit ast_InitVal" << endl;
	if (node.exp != nullptr) {		// 单个变量值
		if (node.bounds.empty( )) { // 尺寸数组为空，故为单个变量的初始值
			node.exp->accept(*this);
		} else {
			// 尺寸数组不为空，故为数组中落单的初始化变量值
			// 计算这个变量的值
			node.exp->accept(*this);
		}
		if (context.const_states.top( )) { // 得到的值为常量类型，转换成变量类型
										   // ValuePtr constval = context.parsing_vals.top( );
										   // context.parsing_vals.pop( );
										   // auto &cv = std::static_pointer_cast<ConstInt>(constval)->val;
										   // ValuePtr val(new VarInt(cv));
										   // context.parsing_vals.push(val);
		}
	} else { // 变量值数组
		// 新建数组变量，并填充尺寸数组
		ValuePtr val(new VarArray( ));
		auto &va = std::static_pointer_cast<VarArray>(val)->val_arr;
		auto &_va = std::static_pointer_cast<VarArray>(val)->_val_arr;
		auto &d = std::static_pointer_cast<VarArray>(val)->dim;
		d.insert(d.end( ), node.bounds.begin( ), node.bounds.end( ));
		// 计算当前维度和子维度的总元素个数
		int cur_sum = node.bounds[0], sub_sum = 1;
		for (int i = 1; i < (int)node.bounds.size( ); ++i) {
			cur_sum *= node.bounds[i];
			sub_sum *= node.bounds[i];
		}
		// 开始填充数组当前维度的初始化值，此时无未完整填充子维度标志
		context.array_states.push(0);
		// 计算各元素的初始化值，注意这里的元素可能存在多维
		for (auto n : node.init_val_list) {
			// 为初始值数组中的元素节点填充尺寸数组，元素的尺寸维度比初始值数组低一维
			auto &b = n->bounds;
			b.clear( );
			b.insert(b.end( ), node.bounds.begin( ) + 1, node.bounds.end( ));
			// 递归处理元素的子元素
			n->accept(*this);
			// 对子维度的两种情况进行处理：最后一维、非最后一维
			if (node.bounds.size( ) == 1) { // 若当前维已经是最后一维，元素不存在子元素
				// 将元素值直接以int形式加入初始值数组
				if (context.const_states.top( )) { // 得到的值为常量类型
					ValuePtr v = context.parsing_vals.top( );
					context.parsing_vals.pop( );
					va.push_back(std::static_pointer_cast<ConstInt>(v)->val);
				} else {
					ValuePtr v = context.parsing_vals.top( );
					context.parsing_vals.pop( );
					_va.push_back(v);
				}
			} else {					 // 若当前维不是最后一维
				if (n->exp != nullptr) { // 为数组中落单的初始化常量值
					// 将当前值填入之前未完整填充的子维度
					if (context.const_states.top( )) { // 得到的值为常量类型
						ValuePtr v = context.parsing_vals.top( );
						context.parsing_vals.pop( );
						va.push_back(std::static_pointer_cast<ConstInt>(v)->val);
					} else {
						ValuePtr v = context.parsing_vals.top( );
						context.parsing_vals.pop( );
						_va.push_back(v);
					}
					int atmp = context.array_states.top( );
					context.array_states.pop( );
					context.array_states.push(atmp + 1);
					if (context.array_states.top( ) >= sub_sum) { // 存在已经完整填充的子维度
						// 已经完整填充的子维度此时已经回填至当前维，故直接清除未完整填充子维度标志
						context.array_states.pop( );
						context.array_states.push(0);
					}
				} else {								   // 为包含子维度的初始化常量数组
					if (context.array_states.top( ) > 0) { // 仍存在未完整填充的子维度
						// 以0填充子维度，并清除未完整填充子维度标志
						// 填充剩余未指明初始化值的数组元素
						int rest = sub_sum - context.array_states.top( );
						if (context.const_states.top( )) {
							for (int i = 0; i < rest; ++i) {
								va.push_back(0);
							}
						} else {
							for (int i = 0; i < rest; ++i) {
								ValuePtr v(new VarInt(0));
								_va.push_back(v);
							}
						}
						context.array_states.pop( );
						context.array_states.push(0);
					}
					// 将元素中的所有子元素值复制进初始值数组
					ValuePtr v = context.parsing_vals.top( );
					context.parsing_vals.pop( );
					auto &vv = std::static_pointer_cast<VarArray>(v)->val_arr;
					auto &_vv = std::static_pointer_cast<VarArray>(v)->_val_arr;
					if (context.const_states.top( )) {
						va.insert(va.end( ), vv.begin( ), vv.end( ));
					} else {
						_va.insert(_va.end( ), _vv.begin( ), _vv.end( ));
					}
				}
			}
		}
		// 填充剩余未指明初始化值的数组元素
		int rest = cur_sum - va.size( );
		for (int i = 0; i < rest; ++i) {
			va.push_back(0);
		}
		// 填充完毕，弹出此维度的未完整填充子维度标志
		context.array_states.pop( );
		context.parsing_vals.push(val);
	}
}

void IrGen::visit(ast_FuncDef &node) {
	std::cout << "IrGen::visit ast_FuncDef" << endl;
	// 生成函数对象，并生成形参列表
	FuncPtr func(new Function(node.id, node.type));
	// 生成函数 IR
	// TODO: 函数生成
	context.scope.insert_item(func);
	context.scope.enter( ); //新的scope
	//在scope填充形参列表
	for (auto n : node.func_params) {
		FParam *fp = new FParam(n->id, n->type, n->isArray);
		std::static_pointer_cast<Function>(func)->fparam_lst.push_back(fp);
		if (n->isArray) { //数组
			ValuePtr fp(new VarArray(n->id));
			fp->alloc_addr = "%" + fp->name;
			fp->size = 4;
			context.scope.insert_item(fp);
		} else { //变量
			ValuePtr fp(new VarInt(n->id));
			fp->alloc_addr = "%" + fp->name;
			fp->size = 4;
			context.scope.insert_item(fp);
		}
	}
	func->alloc_addr = builder.addFunction(func);
	auto bb = builder.createBB( );
	builder.setEntry(func, bb); //设置函数block的入口
	builder.setInsertPoint(bb); //TODO:这句有什么用
	node.block->accept(*this);

	context.scope.leave( );
}

void IrGen::visit(ast_FuncFParam &node) {
	std::cout << "IrGen::visit ast_FuncFParam" << endl;
	// 什么都不做
}

void IrGen::visit(ast_Block &node) {
	std::cout << "IrGen::visit ast_Block" << endl;
	context.scope.enter( );
	for (auto n : node.block_item_list) {
		n->accept(*this);
		if (n->stmt != nullptr) {
			if (n->stmt->stmt_type == BREAK || n->stmt->stmt_type == CONTINUE || n->stmt->stmt_type == RETURN) {
				//break语句，切block
				// BlockPtr _body = context.body.top( );
				// BlockPtr _cur = builder.createBB( );
				// _body->next.push_back(_cur);
				// _cur->pre.push_back(_body);
				// _body->next_to_build = _cur;
				// //更新构建上下文
				// context.body.pop( );
				// context.body.push(_cur);
				// builder.setInsertPoint(_cur);
				//continue、break后续的块内语句不会被构建？！
				break;
			}
		}
	}
	context.scope.leave( );
}

void IrGen::visit(ast_BlockItem &node) {
	std::cout << "IrGen::visit ast_BlockItem" << endl;
	if (node.const_decl != nullptr) {
		node.const_decl->accept(*this);
		// 常量定义不需要额外指令
	} else if (node.var_decl != nullptr) {
		node.var_decl->accept(*this);
		// 变量定义不需要额外指令
	} else if (node.stmt != nullptr) {
		node.stmt->accept(*this);
		// TODO: 语句
		if (node.stmt->stmt_type == EXP || node.stmt->stmt_type == ASSIGN) {

			ValuePtr val = context.parsing_vals.top( );
			context.parsing_vals.pop( );
		}
		//指令插入在block构建过程中进行，这句可能不需要
		// builder.insertStmt(val);
	}
}

void IrGen::visit(ast_LVal &node) {
	std::cout << "IrGen::visit ast_LVal" << endl;
	if (context.const_states.top( )) { // 当前值为常量表达式一部分，直接获取值
		ValuePtr v = context.scope.find_item(node.id);
		if (node.array_exp_list.size( ) == 0) { // 当前为常量取值
			context.parsing_vals.push(v);
		} else { // 当前为数组取值
			// 获取所取数组元素的偏移
			auto &d = std::static_pointer_cast<ConstArray>(v)->dim;
			int index = 0;
			for (int i = 0; i < (int)node.array_exp_list.size( ); ++i) {
				node.array_exp_list[i]->accept(*this);
				ValuePtr vd = context.parsing_vals.top( );
				context.parsing_vals.pop( );
				if (i == (int)node.array_exp_list.size( ) - 1) { // 最后一维不用乘尺寸
					index += std::static_pointer_cast<ConstInt>(vd)->val;
				} else {
					index = (index + std::static_pointer_cast<ConstInt>(vd)->val) * d[i];
				}
			}
			// 获取所取数组元素的值
			ValuePtr val(new ConstInt(std::static_pointer_cast<ConstArray>(v)->val_arr[index]));
			context.parsing_vals.push(val);
		}
	} else { // 当前值为非常量表达式一部分
		// TODO: 变量地址
		ValuePtr v = context.scope.find_item(node.id);
		if (node.array_exp_list.size( ) == 0) { // 当前为变量取值
			context.parsing_vals.push(v);
		} else { // 当前为数组取值
			ValuePtr vr(new VarArrayRef(std::static_pointer_cast<VarArray>(v)));
			auto &vr_inrange = std::static_pointer_cast<VarArrayRef>(vr)->inrange;
			for (int i = 0; i < (int)node.array_exp_list.size( ); ++i) {
				node.array_exp_list[i]->accept(*this);
				ValuePtr vd = context.parsing_vals.top( );
				context.parsing_vals.pop( );
				vr_inrange.push_back(vd);
			}
			ValuePtr val = builder.getArrayLoadInst(vr);
			context.parsing_vals.push(val);
		}
	}
}

void IrGen::visit(ast_Number &node) {
	std::cout << "IrGen::visit ast_Number" << endl;
	if (context.const_states.top( )) { // 当前数字出现在常量表达式中
		ValuePtr val(new ConstInt(node.num, std::to_string(node.num)));
		val->alloc_addr = val->name;
		context.parsing_vals.push(val);

	} else { // 当前数字出现在非常量表达式中
		ValuePtr val(new VarInt(node.num, std::to_string(node.num)));
		val->alloc_addr = val->name;
		context.parsing_vals.push(val);
	}
}

void IrGen::visit(ast_UnaryExp &node) {
	std::cout << "IrGen::visit ast_UnaryExp" << endl;
	if (context.const_states.top( )) { // 当前表达式出现在常量表达式中
		// 计算表达式操作数的值
		node.unary_exp->accept(*this);
		ValuePtr val = context.parsing_vals.top( );
		int &vv = std::static_pointer_cast<ConstInt>(val)->val;
		// 计算表达式的值
		if (node.op == OP_POS) {
			node.unary_exp->accept(*this);
		} else if (node.op == OP_NEG) {
			vv = -vv;
		} else if (node.op == OP_NOT) {
			vv = !vv;
		}
	} else { // 当前表达式出现在非常量表达式中
		// 计算表达式操作数的值
		node.unary_exp->accept(*this);
		ValuePtr val;
		ValuePtr v = context.parsing_vals.top( );
		context.parsing_vals.pop( );
		// TODO: 添加变量计算
		if (node.op == OP_POS) {
			val = builder.getUnaryInst(node.op, v);
		} else if (node.op == OP_NEG) {
			val = builder.getUnaryInst(node.op, v);
		} else if (node.op == OP_NOT) {
			val = builder.getUnaryInst(node.op, v);
		}
		context.parsing_vals.push(val);
	}
}

void IrGen::visit(ast_BinaryExp &node) {
	std::cout << "IrGen::visit ast_BinaryExp" << endl;
	if (context.const_states.top( )) { // 当前表达式出现在常量表达式中
		// 计算表达式操作数的值
		node.exp1->accept(*this);
		ValuePtr v1 = context.parsing_vals.top( );
		context.parsing_vals.pop( );
		node.exp2->accept(*this);
		ValuePtr v2 = context.parsing_vals.top( );
		context.parsing_vals.pop( );
		int &vv1 = std::static_pointer_cast<ConstInt>(v1)->val;
		int &vv2 = std::static_pointer_cast<ConstInt>(v2)->val;
		ValuePtr val(new ConstInt(0));
		int &vv = std::static_pointer_cast<ConstInt>(val)->val;
		context.parsing_vals.push(val);
		// 计算表达式的值
		if (node.op == OP_GT) {
			vv = vv1 > vv2;
		} else if (node.op == OP_LT) {
			vv = vv1 < vv2;
		} else if (node.op == OP_GTE) {
			vv = vv1 >= vv2;
		} else if (node.op == OP_LTE) {
			vv = vv1 <= vv2;
		} else if (node.op == OP_EQ) {
			vv = vv1 == vv2;
		} else if (node.op == OP_NEQ) {
			vv = vv1 != vv2;
		} else if (node.op == OP_ADD) {
			vv = vv1 + vv2;
		} else if (node.op == OP_SUB) {
			vv = vv1 - vv2;
		} else if (node.op == OP_MUL) {
			vv = vv1 * vv2;
		} else if (node.op == OP_DIV) {
			vv = vv1 / vv2;
		} else if (node.op == OP_MOD) {
			vv = vv1 % vv2;
		} else if (node.op == OP_AND) {
			vv = vv1 && vv2;
		} else if (node.op == OP_OR) {
			vv = vv1 || vv2;
		}
	} else { // 当前表达式出现在非常量表达式中
		// 计算表达式操作数的值
		node.exp1->accept(*this);
		ValuePtr v1 = context.parsing_vals.top( );
		context.parsing_vals.pop( );
		node.exp2->accept(*this);
		ValuePtr v2 = context.parsing_vals.top( );
		context.parsing_vals.pop( );
		ValuePtr val;
		// TODO: 添加变量计算
		if (node.op == OP_GT) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_LT) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_GTE) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_LTE) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_EQ) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_NEQ) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_ADD) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_SUB) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_MUL) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_DIV) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_MOD) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_AND) {
			val = builder.getBinaryInst(node.op, v1, v2);
		} else if (node.op == OP_OR) {
			val = builder.getBinaryInst(node.op, v1, v2);
		}
		context.parsing_vals.push(val);
	}
}

void IrGen::visit(ast_FunCall &node) {
	std::cout << "IrGen::visit ast_FunCall" << endl;
	// 取函数对象
	ValuePtr func = context.scope.find_item(node.id);
	// printf("###### %x %s\n", (unsigned int)func.get(), func->name.c_str());
	// 生成实参列表
	std::vector<ValuePtr> rparams;
	for (auto n : node.fun_r_params) {
		n->accept(*this);
		ValuePtr v = context.parsing_vals.top( );
		context.parsing_vals.pop( );
		rparams.push_back(v);
	}
	//
	// TODO: 函数调用
	ValuePtr val = builder.getCallInst(func, rparams);
	context.parsing_vals.push(val);
}

void IrGen::visit(ast_AssignStmt &node) {
	std::cout << "IrGen::visit ast_AssignStmt" << endl;
	ValuePtr vl, vr;
	// 取赋值语句左部
	node.l_val->accept(*this);
	vl = context.parsing_vals.top( );
	context.parsing_vals.pop( );
	// 取赋值语句右部
	node.exp->accept(*this);
	vr = context.parsing_vals.top( );
	context.parsing_vals.pop( );
	// 生成IR
	// TODO: 赋值语句
	ValuePtr val = builder.getAssignInst(vl, vr);
	context.parsing_vals.push(val);
}

void IrGen::visit(ast_SelectStmt &node) {
	std::cout << "IrGen::visit ast_SelectStmt" << endl;

	BlockPtr in_block = this->builder.block;
	BlockPtr cond_block = builder.createBB( );
	BlockPtr if_block = builder.createBB( );
	BlockPtr else_block = builder.createBB( );
	BlockPtr out_block = builder.createBB( );
	BlockPtr cur;

	//in-block
	in_block->next.push_back(cond_block);
	cond_block->pre.push_back(in_block);
	in_block->next_to_build = cond_block;

	//cond-block
	builder.setInsertPoint(cond_block);				 //设置构建block 为 cond_block
	node.cond->accept(*this);						 //构建block
	ValuePtr cond_val = context.parsing_vals.top( ); //取判定的value
	context.parsing_vals.pop( );
	BranchInst *inst_1 = BranchInst::createBr(cond_val, if_block, else_block, cond_block); //跳转指令

	cond_block->add_inst(inst_1);		  //分支的最后一句，添加跳转
	cond_block->next.push_back(if_block); //控制流
	cond_block->next.push_back(else_block);
	if_block->pre.push_back(cond_block);
	else_block->pre.push_back(cond_block);
	cond_block->next_to_build = if_block; //下一个构建的块

	//if-block
	builder.setInsertPoint(if_block);
	if (node.if_stmt != NULL) {
		node.if_stmt->accept(*this); //构建if-block
		//正在构建的块
		cur = builder.block;
		BranchInst *inst_2 = BranchInst::createBr(out_block, cur);
		cur->add_inst(inst_2);
		cur->next.push_back(out_block);
		out_block->pre.push_back(cur);
	}
	builder.block->next_to_build = else_block;

	//else-block
	builder.setInsertPoint(else_block);
	if (node.else_stmt != NULL) {
		node.else_stmt->accept(*this); //构建else-block
		cur = builder.block;
		BranchInst *inst_3 = BranchInst::createBr(out_block, cur);
		cur->add_inst(inst_3);
		cur->next.push_back(out_block);
		out_block->pre.push_back(cur);
	}
	builder.block->next_to_build = out_block;
	//next-block
	builder.setInsertPoint(out_block);
	return;
}

void IrGen::visit(ast_IterationStmt &node) {
	std::cout << "IrGen::visit ast_IterationStmt" << endl;
	BlockPtr cur = NULL;

	BlockPtr in_block = this->builder.block;   //当前块
	BlockPtr cond_block = builder.createBB( ); // cond
	BlockPtr body_block = builder.createBB( ); // body
	BlockPtr out_block = builder.createBB( );  //下一个块

	context.cond.push(cond_block);
	context.body.push(body_block);
	context.out.push(out_block);

	//前一个块
	in_block->next.push_back(cond_block);
	cond_block->next.push_back(in_block);
	in_block->next_to_build = cond_block;

	//cond部分
	builder.setInsertPoint(cond_block);														//设置解析block
	node.cond->accept(*this);																//插入指令
	ValuePtr cond_val = context.parsing_vals.top( );										//获取值
	BranchInst *inst_1 = BranchInst::createBr(cond_val, body_block, out_block, cond_block); //条件跳转
	cond_block->add_inst(inst_1);
	cond_block->next.push_back(body_block);
	cond_block->next.push_back(out_block);
	body_block->pre.push_back(cond_block);
	out_block->pre.push_back(cond_block);

	builder.block->next_to_build = body_block;

	//body部分
	builder.setInsertPoint(body_block); //body的block
	node.stmt->accept(*this);			//解析body

	cur = builder.block;										//body的最后一个block
	BranchInst *inst_2 = BranchInst::createBr(cond_block, cur); //跳转到cond_block，下一循环
	cur->add_inst(inst_2);
	cur->next.push_back(cond_block);
	cond_block->pre.push_back(cur);
	cur->next_to_build = out_block;

	//结束，清栈
	context.cond.pop( );
	context.body.pop( );
	context.out.pop( );

	builder.setInsertPoint(out_block);
	return;
}

void IrGen::visit(ast_BreakStmt &node) {
	std::cout << "IrGen::visit ast_BreakStmt" << endl;
	// break 语句
	BlockPtr cur = context.body.top( );
	BlockPtr out = context.out.top( );
	BranchInst *inst = BranchInst::createBr(out, cur);
	cur->add_inst(inst);
	cur->next.push_back(out);
	out->pre.push_back(cur);

	//TODO：可优化：执行break后，不用切换下一个块。其后的代码无用，可以尝试优化
}

void IrGen::visit(ast_ContinueStmt &node) {
	std::cout << "IrGen::visit ast_ContinueStmt" << endl;
	// continue 语句
	BlockPtr cond = context.cond.top( );
	BlockPtr cur = context.body.top( );
	BranchInst *inst = BranchInst::createBr(cond, cur);
	cur->add_inst(inst);
	cur->next.push_back(cond);
	cond->pre.push_back(cur);
}

void IrGen::visit(ast_ReturnStmt &node) {
	std::cout << "IrGen::visit ast_ReturnStmt" << endl;
	// return 语句
	BlockPtr cur = builder.block;
	ReturnInst *inst;
	if (node.exp == NULL) {
		inst = ReturnInst::createRet(builder.block);
	} else {
		node.exp->accept(*this);
		ValuePtr val = context.parsing_vals.top( );
		inst = ReturnInst::createRet(val, builder.block);
	}
	cur->add_inst(inst);
}
