#ifndef VALUE_HPP
#define VALUE_HPP

#include <memory>
#include <string>

#include "Type.hpp"

enum ValueType {
	VALUE_CONSTINT,
	VALUE_CONSTARRAY,
	VALUE_VARINT,
	VALUE_VARARRAY,
	VALUE_REG,
	VALUE_FUNCTION,
	VALUE_VARARRAYREF,
	VALUE_FPARAM
};

class Value { //定义value类
  private:
  public:
	int size = 4; //值的数据位宽

	ValueType vtype;		// 值的派生类型
	std::string name;		// 值名称
	std::string alloc_addr; // 值的地址名

	// TODO:先不增加ud、du链
	// int num;	//序号，第几个变量、第几个函数
	// Block* ud;	//ud链，这个数数值的依赖变量
	// Block* du;	//du链，依赖这个变量数值的变量
	// std::vector<std::shared_ptr<Instruction>> ud;

	Value(ValueType vtype, std::string name = "") : vtype(vtype), name(name) {}
	virtual void print( ) = 0;
	virtual Value *copy( ) = 0;
};

typedef std::shared_ptr<Value> ValuePtr;

#endif
