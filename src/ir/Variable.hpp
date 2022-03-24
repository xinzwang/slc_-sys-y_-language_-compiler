#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>
#include <vector>

#include "Value.hpp"

class Variable : public Value {
  public:
	Variable(ValueType vtype, std::string name = "") : Value(vtype, name) {}
	virtual void print( ) = 0;
	virtual int get_byte_size( ) = 0;
};
typedef std::shared_ptr<Variable> VarPtr;

class VarInt : public Variable {
  public:
	bool isGlobal;
	int32_t val;
	ValuePtr _val;
	VarInt(int32_t val, std::string name = "") : Variable(VALUE_VARINT, name), isGlobal(true), val(val), _val(NULL) {}
	VarInt(ValuePtr val, std::string name = "") : Variable(VALUE_VARINT, name), isGlobal(false), val(0), _val(val) {}
	VarInt(std::string name = "") : Variable(VALUE_VARINT, name), isGlobal(false), val(0), _val(NULL) {}
	void print( ) {
		if (isGlobal) {
			printf("    <global_var_int>  name:%s  addr:%s  size:%d  val:%d\n", name.c_str( ), alloc_addr.c_str( ), size, val);
		} else {
			printf("    <var_int>  name:%s  addr:%s  size:%d  val:%s\n", name.c_str( ), alloc_addr.c_str( ), size, _val->alloc_addr.c_str( ));
		}
	}
	Value *copy( ) {
		if (isGlobal) {
			VarInt *p = new VarInt(val, name);
			p->alloc_addr = alloc_addr;
			return p;
		} else {
			VarInt *p = new VarInt(_val, name);
			p->alloc_addr = alloc_addr;
			return p;
		}
	}
	int get_byte_size( ) {
		return 4;
	}
};
typedef std::shared_ptr<VarInt> VarIntPtr;

class VarArray : public Variable {
  public:
	bool isGlobal;
	std::vector<int32_t> dim;		//数组维度
	std::vector<int32_t> val_arr;	//初始化列表 全局
	std::vector<ValuePtr> _val_arr; //初始化列表 局部
	VarArray(std::string name = "") : Variable(VALUE_VARARRAY, name) {}
	int get_byte_size( );
	void print( ) {
		if (isGlobal) {
			printf("    <global_var_array> name:%s addr:%s  size:%d", name.c_str( ), alloc_addr.c_str( ), size);
		} else {
			printf("    <var_array> name:%s addr:%s  size:%d", name.c_str( ), alloc_addr.c_str( ), size);
		}
		printf("  dim:(");
		int size = dim.size( );
		if (size > 0) {
			printf("%d", dim[0]);
			for (int i = 1; i < size; i++) {
				printf(",%d", dim[i]);
			}
		}
		printf(")");

		if (isGlobal) {
			printf("  val:(");
			size = val_arr.size( );
			if (size > 0) {
				printf("%d", val_arr[0]);
				for (int i = 1; i < size; i++) {
					printf(",%d", val_arr[i]);
				}
			}
			printf(")\n");
		} else {
			printf("  val:(");
			size = _val_arr.size( );
			if (size > 0) {
				printf("%s", _val_arr[0]->alloc_addr.c_str( ));
				for (int i = 1; i < size; i++) {
					printf(",%s", _val_arr[i]->alloc_addr.c_str( ));
				}
			}
			printf(")\n");
		}
	}
	Value *copy( ) {
		VarArray *p = new VarArray(name);
		p->isGlobal = isGlobal;
		p->dim = dim;
		p->val_arr = val_arr;
		p->alloc_addr = alloc_addr;
		return p;
	}
};
typedef std::shared_ptr<VarArray> VarArrayPtr;

class VarReg : public Variable {
  public:
	VarReg(std::string name = "") : Variable(VALUE_REG, name) {}
	void print( ) {
		printf("    <reg>  name:%s  addr:%s  size:%d\n", name.c_str( ), alloc_addr.c_str( ), size);
	}
	Value *copy( ) {
		VarReg *p = new VarReg(name);
		p->alloc_addr = alloc_addr;
		return p;
	}
	int get_byte_size( ) {
		return 4;
	}
};
typedef std::shared_ptr<VarReg> VarRegPtr;

class VarArrayRef : public Variable {
  public:
	VarArrayPtr arr;			   //待用数组
	std::vector<ValuePtr> inrange; //引用数组的维度
	VarArrayRef(VarArrayPtr var, std::string name = "") : Variable(VALUE_VARARRAYREF, name), arr(var) {}
	void print( ) {
		printf("    <var_array_ref>  name:%s\n", name.c_str( ));
	};
	Value *copy( ) {
		VarArrayRef *p = new VarArrayRef(arr, name);
		p->inrange = inrange;
		p->alloc_addr = alloc_addr;
		return p;
	}
	int get_byte_size( ) {
		return 4;
	}
};
typedef std::shared_ptr<VarArrayRef> VarArrayRefPtr;

#endif