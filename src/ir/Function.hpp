#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "Block.hpp"
#include "Type.hpp"
#include "Value.hpp"

class Block;
typedef std::shared_ptr<Block> BlockPtr;
class Argument;
class FParam;
class Function;

class FParam : public Value { // IR 函数形参类
  private:
  public:
	Type type;
	bool isArray;
	std::vector<int32_t> dim;
	FParam(std::string name, Type type, bool isArray) : Value(VALUE_FPARAM, name), type(type), isArray(isArray) {}
	void print( ) {
		std::string t = (type == TYPE_VOID) ? "void" : "int";
		if (isArray) {
			printf("<type:%s name:%s", t.c_str( ), name.c_str( ));
			int size = dim.size( );
			printf("%d", dim[0]);
			for (int i = 1; i < size; i++) {
				printf("%d", dim[i]);
			}
			printf(">");
		} else {
			printf("<type:%s name:%s>", t.c_str( ), name.c_str( ));
		}
	}
	Value *copy( ) {
		return this;
	}
};

class Function : public Value { // IR 函数类
  private:
  public:
	Type type;
	std::vector<FParam *> fparam_lst;
	bool isLibrary;
	BlockPtr block; //函数的第一个块
	// std::list<Block *> blocks;

	Function(std::string name, Type type) : Value(VALUE_FUNCTION, name), type(type), isLibrary(false) {}

	void print( );
	Value *copy( );
	int alloced_size( );
};
typedef std::shared_ptr<Function> FuncPtr;

#endif
