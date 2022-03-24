#include "AsmCodeGen.hpp"
#include "Instruction.hpp"

#include <queue>
using namespace std;

int comment_flag = 0; //0为不显示注释，反之显示
std::string CodeGen::codegen_main( ) {

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
}
std::string CodeGen::codegen_global_list( ) {
	std::string code_global;
	std::string code_long;
	for (ConstPtr c : _module->global_const_list) {
		//常量只分配数组
		if (c->vtype == VALUE_CONSTARRAY) {
			code_global += Inscode::space + ".global " + c->name + Inscode::newline;
			code_long += Inscode::space + ".long " + c->name + Inscode::newline;
			// static_map[c->alloc_addr] = static_used;
			// static_used += c->get_byte_size( );
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
			// static_map[c->alloc_addr] = static_used;
			// static_used += c->get_byte_size( );
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
	res += Inscode::space + ".data" + Inscode::newline;
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
	// reg_stack.clear( ); //栈清空
	//Inscode::set_alloced_size(func->alloced_size( ));
	var_shift.clear( );
	//1. 函数入口
	res += func->name + ":" + Inscode::newline;					   //入口名
	res += Inscode::space + "@ stack_size=128" + Inscode::newline; //注释
	res += codegen_functionprecode(func);
	//2. 函数所有Block
	for (BlockPtr b = func->block; b != NULL; b = b->next_to_build) {
		res += codegen_blockcode(b.get( ));
	}

	res += codegen_function_post_code(func);
	return res;
}
std::string CodeGen::codegen_end( ) {
	return "";
}

std::string CodeGen::codegen_functionprecode(Function *func) {
	// std::string res;
	// //.fname_pre:
	// res += "." + func->name + "_pre:" + Inscode::newline;
	// res += Inscode::space + "@ function preprocess" + Inscode::newline;
	// res += Inscode::space + "@ save callee-save registers and lr" + Inscode::newline;
	// if (func->name == "main")
	// {
	// 	res += Inscode::space + "@enlarge stack" + Inscode::newline;
	// 	res += Inscode::space + "push {r11, lr}" + Inscode::newline;
	// 	res += Inscode::space + "movw r0, #0" + Inscode::newline;	 //栈大小 256MB?!
	// 	res += Inscode::space + "movt ro, #4096" + Inscode::newline; //不确定
	// 	res += Inscode::space + "bl malloc" + Inscode::newline;		 //calloc malloc 有什么区别？
	// 	res += Inscode::space + "movw r11, #0" + Inscode::newline;
	// 	res += Inscode::space + "movt r11, #4096" + Inscode::newline;
	// 	res += Inscode::space + "add r12, r0, r11" + Inscode::newline;
	// 	res += Inscode::space + "pop {r11, lr}" + Inscode::newline;
	// 	res += Inscode::space + "mov r11, sp" + Inscode::newline;
	// 	res += Inscode::space + "mov sp, r12" + Inscode::newline;
	// 	res += Inscode::space + "push {r11}" + Inscode::newline;
	// }
	// res += Inscode::space + "@ save callee-save register and lr" + Inscode::newline;
	// res += Inscode::space + "push {r11, lr}" + Inscode::newline;
	// res += Inscode::space + "@ allocate stack space" + Inscode::newline;
	// res += Inscode::space + "sub sp, sp, #232" + Inscode::newline; //这个数字是栈的大小
	// //函数  参数传递  前3个在寄存器  其余在堆栈
	// res += Inscode::space + "@ process function args" + Inscode::newline;
	std::string res;
	int has_call = 0;
	has_call = Inscode::fun_has_call(func);
	if (has_call == 1 || func->name == "main") {
		res += func->name + ":" + Inscode::newline;
		res += Inscode::space + "push {fp, lr}" + Inscode::newline;
		res += Inscode::space + "add    fp, sp, #4" + Inscode::newline;
		res += Inscode::space + "sub    sp, sp, #232" + Inscode::newline; //这个数字是栈的大小
	} else {
		res += Inscode::space + "str    fp, [sp, #-4]!" + Inscode::newline;
		res += Inscode::space + "add    fp, sp, #0" + Inscode::newline;
		res += Inscode::space + "sub    sp, sp, #232" + Inscode::newline; //这个数字是栈的大小
	}
	//传入参数
	for (int i = 0; i < (int)func->fparam_lst.size( ) && i < 4; i++) //参数小于四个，从寄存器中取出参数
	{
		var_shift[func->fparam_lst[i]->name] = -(4 + i * 4);
		res += "str    r" + std::to_string(i - 1) + ", [fp, #" + std::to_string(var_shift[func->fparam_lst[i]->name]) + "]\n";
	}
	if (func->fparam_lst.size( ) > 4) //参数多于四个，由父函数已经压入堆栈中了，这里只是找到对应的偏移位置
		for (int i = 4; i < (int)func->fparam_lst.size( ); i++)
			var_shift[func->fparam_lst[i]->name] = 4 * (i - 4);
	return res;
}

std::string CodeGen::codegen_function_post_code(Function *func) //函数后追代码
{
	std::string res;
	int has_call = 0;
	has_call = Inscode::fun_has_call(func);
	if (has_call == 1 || func->name == "main") {
		res += Inscode::space + "sub    sp, fp, #4" + Inscode::newline;
		res += Inscode::space + "pop    {fp, pc}" + Inscode::newline;
	} else {
		res += Inscode::space + "ldr    fp, [sp], #4" + Inscode::newline;
		res += Inscode::space + "bx    lr" + Inscode::newline;
	}
	return res;
}

std::string CodeGen::codegen_blockcode(Block *bb) {
	std::string res;
	res += "." + bb->name + ":" + Inscode::newline;
	for (auto &ins : bb->inst_list)
	{
		res += codegen_inscode(ins);
	}
	return res;
}

std::string CodeGen::codegen_inscode(Instruction *ins) {
	std::string res;
	res += Inscode::space + "@" +
		   res += Inscode::space;
	for (Value *v : ins->get_val( )) {
		res += v->alloc_addr + ":" + to_string(reg_map[v]) + " ";
	}
	res += Inscode::newline;
	switch (ins->itype) {
	case IrType::Add:
		res += Inscode::add((BinaryInst *)ins, &var_shift, &reg_map);
		break;
	case IrType::Sub:
		res += Inscode::sub((BinaryInst *)ins, &var_shift, &reg_map);
		break;
	case IrType::Mul:
		res += Inscode::Mul((BinaryInst *)ins, &var_shift, &reg_map);
		break;
	case IrType::Div:
		res += Inscode::Div((BinaryInst *)ins, &var_shift, &reg_map);
		break;
	case IrType::Rem:
		/* code */
		break;
	case IrType::And:
		res += Inscode::And((BinaryInst *)ins, &var_shift, &reg_map);
		break;
	case IrType::Or:
		res += Inscode::OR((BinaryInst *)ins, &var_shift, &reg_map);
		break;
	case IrType::Shl:
		res += Inscode::LSL((BinaryInst *)ins, &var_shift, &reg_map);
		break;
	case IrType::Cmp:
		res += Inscode::CMP((CmpInst *)(ins), &var_shift, &reg_map);
		break;
	case IrType::Alloca:
		res += Inscode::alloc((AllocaInst *)(ins), &var_shift, &reg_map);
		break;
	case IrType::Load:
		res += "load\n";
		break;
	case IrType::Store:
		res += Inscode::store((StoreInst *)(ins), &var_shift, &reg_map);
		break;
	case IrType::PHI:
		/* code */
		break;
	case IrType::Call:
		res += Inscode::Call((CallInst *)(ins), &var_shift, &reg_map);
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
		res += Inscode::ret((ReturnInst *)ins, &var_shift, &reg_map);
		break;
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