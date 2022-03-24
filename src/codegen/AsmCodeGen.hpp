#ifndef ASMCODEGEN_HPP
#define ASMCODEGEN_HPP
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "Block.hpp"
#include "Const.hpp"
#include "Function.hpp"
#include "InsAsmCode.hpp"
#include "Instruction.hpp"
#include "Module.hpp"
#include "Variable.hpp"

// 全局变量 const std::string global_vars_label = ".global_vars";
//寄存器组

class CodeGen {
  private:
	class Reg {
	  public:
		int id;
		std::string alloc_addr;
		bool is_used;
	};

	const int rsp = 13;
	const int rlr = 14;
	const std::set<int> all_regs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; //所有寄存器
	const std::set<int> allocate_regs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};	   //变量存储的寄存器

	const std::set<int> caller_save_regs = {0, 1, 2, 3, 12, 14}; //四个参数、
	const std::set<int> callee_save_regs = {4, 5, 6, 7, 8, 9, 10, 11};

	const std::set<int> temp_regs = {11, 12, 14};

  private:
	std::string arm_code; //汇编最终代码
	Module *_module;
	//寄存器图
	// std::map<Value *, int> alloced;		   //每个函数的栈大小
	// std::map<std::string, int> static_map; //全局量的偏移
	// int static_used;
	// std::map<std::string, int> stack_map; //变量相对sp的偏移
	// int sp;

	std::map<Value *, int> reg_map;
	std::map<std::string, int> var_shift;

  public:
	std::map<Value *, int> reg_alloc( );

	CodeGen(Module *_module) : _module(_module) {
		this->reg_map = this->reg_alloc( );
		// for (FuncPtr func : this->_module->fun_list) {
		// 	// alloced[func.get( )] = func->alloced_size( );
		// }
	};
	//~CodeGen();
	std::string codegen_main( ); //主生成函数

	std::string codegen_global_list( ); //数据段声明
	std::string codegen_global_init( ); //数据段初始化

	std::string codegen_functioncode(Function *func);		//生成函数汇编代码
	std::string codegen_functionprecode(Function *func);	//函数前缀代码
	std::string codegen_function_post_code(Function *func); //函数后追代码

	std::string codegen_blockcode(Block *bb);	   //生成基本块代码
	std::string codegen_inscode(Instruction *ins); //生成基本指令代码

	std::string codegen_start(Function *func);		 //函数入口点
	std::string codegen_end( );						 //函数出口点
	std::string codegen_funcall(CallInst *call_ins); //函数调用
};
int var_shift_mtop(std::map<std::string, int> *var_shift); //获取可以使用的堆位置
#endif