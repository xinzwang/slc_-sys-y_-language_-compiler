#ifndef IR_HPP
#define IR_HPP

#include <stack>
#include <string>
#include <vector>

#include "Block.hpp"
#include "Const.hpp"
#include "Function.hpp"
#include "Instruction.hpp"
#include "Module.hpp"
#include "Scope.hpp"
#include "Type.hpp"
#include "Value.hpp"
#include "Variable.hpp"

using namespace std;

class IrContext { // IR 上下文
  private:
  public:
	Scope scope;
	std::stack<ValuePtr> parsing_vals; // 解析中间值暂存栈
	std::stack<bool> const_states;	   // 常量计算状态暂存栈，保存当前进行的计算是否为常量计算
	std::stack<int> array_states;	   // 数组填充状态暂存栈，保存当前初始化的数组是否存在未完整填充的子维度

	std::stack<BlockPtr> cond;
	std::stack<BlockPtr> body;
	std::stack<BlockPtr> out;
};

class IrBuilder { // IR 生成器
  private:
	int _reg_seq;
	int _block_seq;
	FuncPtr _func;
	Scope *scope;

  public:
	Module *_module;
	BlockPtr block; //正在生成的Block

  public:
	void init(Scope *scope); //初始化Builder

	void insertStmt(ValuePtr val); //生成IR语句，只在BlockItem获取到一个段落后执行

	BlockPtr createBB( ); //创建基本块

	void setEntry(FuncPtr func, BlockPtr bb); //函数生成 设置入口
	void setInsertPoint(BlockPtr bb);		  //函数生成 设置插入点
	void setIterationPoint(ValuePtr val);	  //循环  设置循环点

	string addGlobalConst(ValuePtr val); //分配 全局常量 空间
	string addConst(ValuePtr val);		 //分配 局部常量 空间
	string addGlobalVar(ValuePtr val);	 //分配 全局变量 空间
	string addVar(ValuePtr val);		 //分配 局部变量 空间
	string addFunction(ValuePtr val);	 //添加函数

	ValuePtr getLoadInst(ValuePtr v);
	ValuePtr getArrayLoadInst(ValuePtr v);							//从内存取v的数值
	ValuePtr getUnaryInst(Unary_OP op, ValuePtr v);					//获取一元表达式数值
	ValuePtr getBinaryInst(Binary_OP op, ValuePtr v1, ValuePtr v2); //获取二元表达式数值
	ValuePtr getCallInst(ValuePtr func, vector<ValuePtr> rparams);	//获取函数调用数值
	ValuePtr getAssignInst(ValuePtr vl, ValuePtr vr);				//获取复制语句数值
	// ValuePtr getBrInst(valuePtr cond, BlockPtr bt, BlockPtr bf);
	// ValuePtr getBrInst(valuePtr bt);
	ValuePtr getIfElseBlock(ValuePtr vc, ValuePtr vi, ValuePtr ve); //获取if-else块
	ValuePtr getIfBlock(ValuePtr vc, ValuePtr vi);					//获取if块
	ValuePtr getWhileBlock(ValuePtr vc, ValuePtr vs);				//获取while块
	ValuePtr getBreakInst( );										//获取break值
	ValuePtr getContinueInst( );									//获取continue值
	ValuePtr getReturnInst( );										//获取return值
};

#endif