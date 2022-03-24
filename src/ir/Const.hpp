#ifndef CONST_HPP
#define CONST_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Value.hpp"

class Const : public Value {
  public:
	Const(ValueType vtype, std::string name = "") : Value(vtype, name) {}
	virtual void print( ) = 0;
	virtual int get_byte_size( ) = 0;
};
typedef std::shared_ptr<Const> ConstPtr;

class ConstInt : public Const {
  public:
  public:
	int32_t val;
	ConstInt(int32_t val, std::string name = "") : Const(VALUE_CONSTINT, name), val(val) {
		this->alloc_addr = std::to_string(val);
	}
	void print( ) {
		printf("    <const_int>  name:%s  addr:%s  size:%d  val:%d\n", name.c_str( ), alloc_addr.c_str( ), size, val);
	}
	Value *copy( ) {
		ConstInt *p = new ConstInt(val, name);
		p->alloc_addr = alloc_addr;
		return p;
	}
	int get_byte_size( ) { return 4; }
};
typedef std::shared_ptr<ConstInt> ConstIntPtr;

class ConstArray : public Const {
  public:
	std::vector<int32_t> dim;
	std::vector<int32_t> val_arr;
	ConstArray(std::string name = "") : Const(VALUE_CONSTARRAY, name) {}
	int get_byte_size( );

	void print( ) {
		printf("    <const_array> name:%s addr:%s  size:%d", name.c_str( ), alloc_addr.c_str( ), size);
		printf("  dim:(");
		int size = dim.size( );
		if (size > 0) {
			printf("%d", dim[0]);
			for (int i = 1; i < size; i++) {
				printf(",%d", dim[i]);
			}
		}
		printf(")");

		printf("  val:(");
		size = val_arr.size( );
		if (size > 0) {
			printf("%d", val_arr[0]);
			for (int i = 1; i < size; i++) {
				printf(",%d", val_arr[i]);
			}
		}
		printf(")\n");
	}
	Value *copy( ) {
		ConstArray *p = new ConstArray(name);
		p->dim = dim;
		p->val_arr = val_arr;
		p->alloc_addr = alloc_addr;
		return p;
	}
};
typedef std::shared_ptr<ConstArray> ConstArrayPtr;

#endif