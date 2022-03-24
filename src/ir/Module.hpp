#ifndef MODULE_HPP
#define MODULE_HPP

#include <list>
#include <memory>

#include "Const.hpp"
#include "Function.hpp"
#include "Variable.hpp"

class Module {
  public:
	std::string module_name;	  //Module名
	std::string source_file_name; //源文件名

	std::vector<VarPtr> global_list;		 //全局常量
	std::vector<ConstPtr> global_const_list; //全局变量
	std::vector<FuncPtr> fun_list;			 //函数表

	// void add_gloabl_var(Variable *v) { this->global_list.push_back(v); }
	// void add_global_const(Const *v) { this->global_const_list.push_back(v); }
	// void add_global_func(Function *v) { this->fun_list.push_back(v); }

	void print( ) {
		printf("\n\n-------------------------  IR  -------------------------\n\n");

		//全局 常量表
		printf("Global const list:\n");
		for (ConstPtr val : global_const_list) {
			val->print( );
		}
		printf("\n");
		//全局 变量表
		printf("Global var list:\n");
		for (VarPtr val : global_list) {
			val->print( );
		}
		printf("\n");
		//函数声明表
		for (FuncPtr f : fun_list) {
			f->print( );
			printf("\n");
		}
	}
};

#endif