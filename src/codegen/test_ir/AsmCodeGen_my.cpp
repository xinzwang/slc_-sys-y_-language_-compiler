#include "AsmCodeGen.hpp"

#include <queue>
using namespace std;

int comment_flag = 0; //0为不显示注释，反之显示
std::string CodeGen::codegen_main( ) {
	//0. 初始化
	static_used = 0;
	for (FuncPtr func : this->_module->fun_list) {
		alloced[func.get( )] = func->alloced_size( );
	}
	//1. 汇编框架
	arm_code += Inscode::space + ".arch armv" + "7-a" + Inscode::newline;						   //汇编版本信息
	arm_code += Inscode::space + ".file \"" + _module->source_file_name + "\"" + Inscode::newline; //文件信息
	arm_code += Inscode::space + ".text" + Inscode::newline;
	arm_code += Inscode::space + ".global main" + Inscode::newline; //待确认
	arm_code += Inscode::space + ".arm" + Inscode::newline;
	arm_code += Inscode::space + ".fpu neon" + Inscode::newline;
	// arm_code += Inscode::sperrorace + "AREA _MAIN, CODE, READONLY" + Inscode::newline;
	//全局常量，变量定义
	arm_code += codegen_global_list( ); //数据段
	//各级函数定义
	std::string func_start;
	for (auto &func : this->_module->fun_list) {
		if (func->name == "main") {
			func_start = codegen_functioncode(func.get( ));
		} else {
			arm_code += codegen_functioncode(func.get( ));
		}
	}
	arm_code += func_start; //程序入口
	//代码出口段
	arm_code += codegen_end( );
	arm_code += codegen_global_init( ); //静态数据段初始化

	return arm_code;
};

std::string CodeGen::codegen_global_list( ) {
	std::string code_global;
	std::string code_long;
	for (ConstPtr c : _module->global_const_list) {
		//常量只分配数组
		if (c->vtype == VALUE_CONSTARRAY) {
			code_global += Inscode::space + ".global " + c->name + Inscode::newline;
			code_long += Inscode::space + ".long " + c->name + Inscode::newline;
			static_map[c->alloc_addr] = static_used;
			static_used += c->get_byte_size( );
		} else if (c->vtype == VALUE_CONSTINT) {
			//TODO：ConstInt是否分配不确定。
		} else {
			printf("[Error] codegen_global_list. expect ConstArray. line:%d", __LINE__);
		}
	}
	for (VarPtr c : _module->global_list) {
		//变量分配
		if (c->vtype == VALUE_VARINT || c->vtype == VALUE_VARARRAY) {
			code_global += Inscode::space + ".global " + c->name + Inscode::newline;
			code_long += Inscode::space + ".long " + c->name + Inscode::newline;
			static_map[c->alloc_addr] = static_used;
			static_used += c->get_byte_size( );
		} else {
			printf("[Error] codegen_global_list. expect VarInt VarArray. line:%d", __LINE__);
		}
	}
	std::string res;
	res = code_global;
	res += ".global_vars:" + Inscode::newline;
	res += code_long;
	return res;
}
std::string CodeGen::codegen_global_init( ) {
	std::string res;
	for (ConstPtr c : _module->global_const_list) {
		if (c->vtype == VALUE_CONSTARRAY) { //常量只分配数组
			res += c->name + ":" + Inscode::newline;
			for (int val : std::static_pointer_cast<ConstArray>(c)->val_arr) {
				res += Inscode::space + ".long " + std::to_string(val) + Inscode::newline;
			}
		} else if (c->vtype == VALUE_CONSTINT) {
			//TODO：ConstInt是否分配不确定。
		} else {
			printf("[Error] codegen_global_init. expect ConstArray. line:%d", __LINE__);
		}
	}
	for (VarPtr c : _module->global_list) {
		if (c->vtype == VALUE_VARINT) {
			res += c->name + ":" + Inscode::newline;
			VarIntPtr val = std::static_pointer_cast<VarInt>(c);
			if (!val->isGlobal) {
				printf("[Error] codegen_global_init. expect Global VarInt. line:%d", __LINE__);
			}
			res += Inscode::space + ".long " + std::to_string(val->val) + Inscode::newline;
		} else if (c->vtype == VALUE_VARARRAY) {
			res += c->name + ":" + Inscode::newline;
			VarArrayPtr val = std::static_pointer_cast<VarArray>(c);
			if (!val->isGlobal) {
				printf("[Error] codegen_global_init. expect Global VarArray. line:%d", __LINE__);
			}
			for (int init_val : val->val_arr) {
				res += Inscode::space + ".long " + std::to_string(init_val) + Inscode::newline;
			}
		} else {
			printf("[Error] codegen_global_init. expect VarInt VarArray. line:%d", __LINE__);
		}
	}
	return res;
}

std::string CodeGen::codegen_functioncode(Function *func) {
	std::string res;
	//0. 初始化
	reg_stack.clear( ); //栈清空

	//1. 函数入口
	res += func->name + ":";									   //入口名
	res += Inscode::space + "@ stack_size=128" + Inscode::newline; //注释
	res += codegen_functionprecode(func);
	//2. 函数所有Block
	for (BlockPtr b = func->block; b != NULL; b = b->next_to_build) {
		res += codegen_blockcode(b.get( ));
	}
	//3. 函数出口
	//TODO：这里应该什么都不用做
	return res;
}

std::string CodeGen::codegen_functionprecode(Function *func) {
	std::string res;
	//.fname_pre:
	res += "." + func->name + "_pre:";
	res += Inscode::space + "@ function preprocess" + Inscode::newline;
	res += Inscode::space + "@ save callee-save registers and lr" + Inscode::newline;
	if (func->name == "main") {
		res += Inscode::space + "@enlarge stack" + Inscode::newline;
		res += Inscode::space + "push {r11, lr}" + Inscode::newline;
		res += Inscode::space + "movw r0, #0" + Inscode::newline;	 //栈大小 256MB?!
		res += Inscode::space + "movt ro, #4096" + Inscode::newline; //不确定
		res += Inscode::space + "bl malloc" + Inscode::newline;		 //calloc malloc 有什么区别？
		res += Inscode::space + "movw r11, #0" + Inscode::newline;
		res += Inscode::space + "movt r11, #4096" + Inscode::newline;
		res += Inscode::space + "add r12, r0, r11" + Inscode::newline;
		res += Inscode::space + "pop {r11, lr}" + Inscode::newline;
		res += Inscode::space + "mov r11, sp" + Inscode::newline;
		res += Inscode::space + "mov sp, r12" + Inscode::newline;
		res += Inscode::space + "push {r11}" + Inscode::newline;
	}
	res += Inscode::space + "@ save callee-save register and lr" + Inscode::newline;
	res += Inscode::space + "push {r11, lr}" + Inscode::newline;
	res += Inscode::space + "@ allocate stack space" + Inscode::newline;
	res += Inscode::space + "sub sp, sp, #232" + Inscode::newline; //这个数字是栈的大小
	//函数  参数传递  前3个在寄存器  其余在堆栈
	res += Inscode::space + "@ process function args" + Inscode::newline;
	std::string temp_arm_code;
	std::string temp_arm_code2;
	int has_call = 0;
	has_call = Inscode::fun_has_call(func);
	if (has_call == 1) {
		temp_arm_code += func->name + ":" + Inscode::newline;
		temp_arm_code += Inscode::space + "push {fp, lr}" + Inscode::newline;
		temp_arm_code += Inscode::space + "add    fp, sp, #4" + Inscode::newline;
	} else {
		temp_arm_code += Inscode::space + "str    fp, [sp, #-4]\n";
		temp_arm_code += Inscode::space + "add    fp, sp, #0\n";
	}
	//处理传入参数
	if (func->fparam_lst.size( ) <= 4) { //在寄存器0-3中
		for (int i = 0; i < func->fparam_lst.size( ); i++) {
			//fparam_lst参数入栈
			var_shift[func->fparam_lst[i]->name] = -(4 + i * 4);
			temp_arm_code2 += "str    r" + std::to_string(i - 1) + ", [fp, #" + std::to_string(var_shift[func->fparam_lst[i]->name]) + "]\n";
		}
	} else { //除去前四个参数，其余在堆栈中
		//TODO:这里没有传前三个参数？！
		for (int i = 4; i < func->fparam_lst.size( ); i++)
			var_shift[func->fparam_lst[i]->name] = 4 * (i - 4);
	}
}

std::string codegen_function_post_code(Function *func) {
	return "";
}

std::string CodeGen::codegen_blockcode(Block *bb) {
	std::string temp_arm_code;
	for (auto &ins : bb->inst_list) {
		temp_arm_code += codegen_inscode(ins);
	}
	return temp_arm_code;
}

std::string CodeGen::codegen_inscode(Instruction *ins, std::map<std::string, int> *var_shift) {
	std::string res
		res += Inscode::space + std::to_string(ins->itype) + " " + Inscode::newline;
	switch (ins->itype) {
	case IrType::Alloca: {
		AllocaInst *inst = std::static_pointer_cast<AllocaInst>(ins);
		sp -= size;
		stack_map[inst->dest->alloc_addr] = sp;
		break;
	}
	case IrType::Load: {
		// LoadInst *inst = std::static_pointer_cast<LoadInst>(ins);
		// int rd = reg_map[inst->dest]; //目的
		// int rv = reg_map[inst->v];	  //源地址
		// if (inst->v->vtype == VALUE_REG) {

		// } else if (inst->v->vtype == VALUE_VARINT) {

		// 	res+= Inscode::space +"add sp"
		// }
		// res += ldr(rd, rv); // ldr rd, [rv]
		break;
	}
	case IrType::Store: {
		StoreInst *inst = std::static_pointer_cast<StoreInst>(ins);
		if (inst->dest->alloc_addr[0] == "@") { //全局变量
			int d = static_map[inst->dest]		//偏移
					sp -
					alloca + d
		}

		break;
	}
	case IrType::Add:
		/* code */
		break;
	case IrType::Sub:
		/* code */
		break;
	case IrType::Mul:
		/* code */
		break;
	case IrType::Div:
		/* code */
		break;
	case IrType::Rem:
		/* code */
		break;
	case IrType::And:
		/* code */
		break;
	case IrType::Or:
		/* code */
		break;
	case IrType::Shl:
		/* code */
		break;
	case IrType::Cmp:
		/* code */
		break;

	case IrType::Call:
		res += codegen_funcall((CallInst *)ins);
		break;
	case GEP:
		/* code */
		break;
	case IrType::Break:
		/* code */
		break;
	case IrType::Continue:
		/* code */
		break;
	case IrType::Ret:
		brek;
	case IrType::Br:
		/* code */
		break;
	case IrType::Neg:
		/* code */
		break;
	case IrType::Not:
		/* code */
		break;

	default:
		break;
	}
	return res;
}

std::string CodeGen::codegen_end( ) //汇编程序结束代码
{
	std::string temp_arm_code;
	// temp_arm_code += "END" + Inscode::newline;
	return temp_arm_code;
}
