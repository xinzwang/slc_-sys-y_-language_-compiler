#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <list>
#include <map>
#include <memory>
#include <vector>

#include "Block.hpp"
#include "Function.hpp"
#include "Type.hpp"
#include "Value.hpp"

class Block;
typedef std::shared_ptr<Block> BlockPtr;

// 参考文档：https://blog.csdn.net/qq_42570601/article/details/107581608
// 这个文档对LLVM IR做了较详细的介绍，大家写的时候可以参考一下。如果有
// 新的想法就及时和我说！然后做修改（wxz）

// 指令类型
enum IrType {
	// High IR
	Break,
	Continue,

	// Terminator Instructions
	Ret, //ret	返回
	Br,	 //br	跳转

	// 单目运算
	Neg, //neg 相反数
	Not, //非
	// 双目运算
	Add,  //add 加
	Sub,  //sub
	Mul,  //mul 乘
	Div,  //div 除
	Rem,  //rem 余数
	And,  //与
	Or,	  //或
	Shl,  // 左移<<
	AShr, // 算数右移	arithmetic >>
	LShr, // 逻辑右移	logical >>
	Cmp,  //比较

	// RSub,  // Reverse Subtract
	// AddAddr,  // deprecated
	// Logical operators

	// 内存操作
	Alloca,
	Load,
	Store,

	// Other operators
	PHI,
	Call,
	GEP, // GetElementPtr

	// ZExt,  // zero extend
	// MulAdd,	  // a*b+c
	// MTSTART,  // %thread_id = MTSTART
	// MTEND,	  // MTEND %thread_id
	// // NEON SIMD
	// VV,	 // sum(vector .* vector)
	// BIC
};

//比较运算符类型
// enum CmpOp {
// 	EQ, //==
// 	NE, //!=
// 	GT, //>
// 	GE, //>=
// 	LT, //<
// 	LE	//<=
// };

Value *to_static_pointer(ValuePtr v);

class Instruction { // IR 指令基类
  public:
	IrType itype;	 //指令类型
	BlockPtr father; //指令所属Block

	Instruction(IrType _itype, BlockPtr _father) : itype(_itype), father(_father){ };
	virtual void print( ) = 0;
	virtual std::vector<Value *> get_val( ) = 0;
};

// UnaryInst 一元指令
class UnaryInst : public Instruction { // IR 一元指令
  private:
  public:
	Value *dest;
	Value *v;
	UnaryInst(IrType _itype, ValuePtr _dest, ValuePtr _v, BlockPtr _father) : Instruction(_itype, _father) {
		dest = to_static_pointer(_dest);
		v = to_static_pointer(_v);
	}

  public:
	static UnaryInst *createNeg(ValuePtr _dest, ValuePtr _v, BlockPtr _father) { return new UnaryInst(Neg, _dest, _v, _father); }
	static UnaryInst *createNot(ValuePtr _dest, ValuePtr _v, BlockPtr _father) { return new UnaryInst(Not, _dest, _v, _father); }
	void print( ) {
		switch (this->itype) {
		case Neg:
			printf("    [Neg]  dest:%s  v:%s\n", dest->alloc_addr.c_str( ), v->alloc_addr.c_str( ));
			break;
		case Not:
			printf("    [Not]  dest:%s  v:%s\n", dest->alloc_addr.c_str( ), v->alloc_addr.c_str( ));
			break;
		default:
			printf("[ERROR]  UnaryInst line:%d\n", __LINE__);
		}
	}
	std::vector<Value *> get_val( ) {
		std::vector<Value *> res;
		res.push_back(dest);
		res.push_back(v);
		return res;
	}
};

// BinaryInst 二元指令 dest:=v1 op v2
// 这里包含 add、sub、mul、div、and、or、shl、lshr、ashr、cmp等二元指令
class BinaryInst : public Instruction { // IR 二元指令
  private:
  public:
	bool nsw; // 为true，生成新的变量放在dest，相当于隐式变量分配
		// 为false，dest是已经给定的变量。
	Value *dest; //目的变量，是一个新的变量
	Value *v1;	 //运算数1
	Value *v2;	 //运算数2
	BinaryInst(IrType _itype, ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) : Instruction(_itype, _father) {
		dest = to_static_pointer(_dest);
		v1 = to_static_pointer(_v1);
		v2 = to_static_pointer(_v2);
	};

  public:
	static BinaryInst *createAdd(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(Add, _dest, _v1, _v2, _father); }
	static BinaryInst *createSub(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(Sub, _dest, _v1, _v2, _father); }
	static BinaryInst *createMul(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(Mul, _dest, _v1, _v2, _father); }
	static BinaryInst *createDiv(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(Div, _dest, _v1, _v2, _father); }
	static BinaryInst *createRem(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(Rem, _dest, _v1, _v2, _father); }
	static BinaryInst *createAnd(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(And, _dest, _v1, _v2, _father); }
	static BinaryInst *createOr(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(Or, _dest, _v1, _v2, _father); }
	static BinaryInst *createShl(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(Shl, _dest, _v1, _v2, _father); }
	static BinaryInst *createAShr(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(AShr, _dest, _v1, _v2, _father); }
	static BinaryInst *createLShr(ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new BinaryInst(LShr, _dest, _v1, _v2, _father); }
	void print( ) {
		printf("    ");
		switch (itype) {
		case Add:
			printf("[Add]");
			break;
		case Sub:
			printf("[Sub]");
			break;
		case Mul:
			printf("[Mul]");
			break;
		case Div:
			printf("[Div]");
			break;
		case Rem:
			printf("[Rem]");
			break;
		case And:
			printf("[And]");
			break;
		case Or:
			printf("[Or]");
			break;
		case Shl:
			printf("[Shl]");
			break;
		case AShr:
			printf("[AShr]");
			break;
		case LShr:
			printf("[LShr]");
			break;
		default:
			printf("[ERROR]  BinaryInst line:%d\n", __LINE__);
			return;
		}
		printf("  dest:%s  v1:%s  v2:%s\n", dest->alloc_addr.c_str( ), v1->alloc_addr.c_str( ), v2->alloc_addr.c_str( ));
	}
	std::vector<Value *> get_val( ) {
		std::vector<Value *> res;
		res.push_back(dest);
		res.push_back(v1);
		res.push_back(v2);
		return res;
	}
};

// CmpInst 比较指令
class CmpInst : public Instruction {
  public:
	enum CmpOp {
		EQ, // ==
		NE, // !=
		GT, // >
		GE, // >=
		LT, // <
		LE	// <=
	};

	CmpOp op;
	Value *dest;
	Value *v1;
	Value *v2;

	CmpInst(CmpOp _op, ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) : Instruction(Cmp, _father), op(_op) {
		dest = to_static_pointer(_dest);
		v1 = to_static_pointer(_v1);
		v2 = to_static_pointer(_v2);
	};

  public:
	static CmpInst *createCmp(CmpOp _op, ValuePtr _dest, ValuePtr _v1, ValuePtr _v2, BlockPtr _father) { return new CmpInst(_op, _dest, _v1, _v2, _father); }

	void print( ) {
		printf("    [Cmp]  op:");
		switch (op) {
		case EQ:
			printf("EQ");
			break;
		case NE:
			printf("NE");
			break;
		case GT:
			printf("GT");
			break;
		case GE:
			printf("GE");
			break;
		case LT:
			printf("LT");
			break;
		case LE:
			printf("LE");
			break;
		}
		printf("  dest:%s  v1:%s  v2:%s", dest->alloc_addr.c_str( ), v1->alloc_addr.c_str( ), v2->alloc_addr.c_str( ));
	}
	std::vector<Value *> get_val( ) {
		std::vector<Value *> res;
		res.push_back(dest);
		res.push_back(v1);
		res.push_back(v2);
		return res;
	}
};

// AssignInst 赋值语句 v1:=v2
// TODO: 赋值通过Store、Load完成，这条指令可能没用，等待
// class AssignInst : public Instruction { // IR 赋值指令
//   private:
//   public:
// 	ValuePtr dest;
// 	ValuePtr v;
// };

// AllocInst 分配栈的局部变量v
class AllocaInst : public Instruction { // IR alloca 指令
  private:
  public:
	int size;	 //空间大小,对于数组，指定数组的 字节大小
	Value *dest; //新声明的变量
	AllocaInst(ValuePtr _dest, int _size, BlockPtr _father) : Instruction(Alloca, _father), size(_size) {
		dest = to_static_pointer(_dest);
	}

  public:
	static AllocaInst *createAlloca(ValuePtr _dest, int _size, BlockPtr _father) { return new AllocaInst(_dest, _size, _father); }
	void print( ) {
		printf("    [Alloc]  dest:%s  size:%d\n", dest->alloc_addr.c_str( ), size);
	}
	std::vector<Value *> get_val( ) {
		std::vector<Value *> res;
		res.push_back(dest);
		return res;
	}
};

// LoadInst 从内存读取一个数据
class LoadInst : public Instruction { // IR load 指令
  private:
  public:
	Value *dest;
	Value *v;
	LoadInst(ValuePtr _dest, ValuePtr _v, BlockPtr _father) : Instruction(Load, _father) {
		dest = to_static_pointer(_dest);
		v = to_static_pointer(_v);
	}

  public:
	static LoadInst *createInst(ValuePtr _dest, ValuePtr _v, BlockPtr _father) { return new LoadInst(_dest, _v, _father); }
	void print( ) { printf("    [Load]  dest:%s  v:%s\n", dest->alloc_addr.c_str( ), v->alloc_addr.c_str( )); }
	std::vector<Value *> get_val( ) {
		std::vector<Value *> res;
		res.push_back(dest);
		res.push_back(v);
		return res;
	}
};

// StoreInst 将数据写入内存
class StoreInst : public Instruction { // IR store 指令
  private:
  public:
	Value *dest; //目的内存的地址
	Value *v;	 // 1. 写入变量的值	为NULL-写入num  非NULL写入变量v的值
	int32_t num; // 2. 写入常量的值
	StoreInst(ValuePtr _dest, ValuePtr _v, int32_t _num, BlockPtr _father) : Instruction(Store, _father), num(_num) {
		dest = to_static_pointer(_dest);
		v = to_static_pointer(_v);
	}

  public:
	static StoreInst *createStore(ValuePtr _dest, ValuePtr _v, BlockPtr _father) { return new StoreInst(_dest, _v, 0, _father); }
	static StoreInst *createStore(ValuePtr _dest, int32_t _num, BlockPtr _father) { return new StoreInst(_dest, NULL, _num, _father); }

	void print( ) {
		if (v != NULL) { //变量
			printf("    [Store]  dest:%s  v:%s\n", dest->alloc_addr.c_str( ), v->alloc_addr.c_str( ));
		} else {
			printf("    [Store]  dest:%s  v:%d\n", dest->alloc_addr.c_str( ), num);
		}
	}
	std::vector<Value *> get_val( ) {
		std::vector<Value *> res;
		res.push_back(dest);
		if (v != NULL) {
			res.push_back(v);
		}
		return res;
	}
};

// CallInst 函数调用
class CallInst : public Instruction { // IR call 指令
  private:
  public:
	Value *dest;				  //目的寄存器
	ValuePtr func;				  //函数名
	std::vector<Value *> rparams; //实参表
	CallInst(ValuePtr _dest, ValuePtr _func, std::vector<ValuePtr> _rparams, BlockPtr _father) : Instruction(Call, _father), func(_func) {
		dest = to_static_pointer(_dest);
		for (ValuePtr rp : _rparams) {
			rparams.push_back(to_static_pointer(rp));
		}
	}

  public:
	static CallInst *createCall(ValuePtr _dest, ValuePtr _func, std::vector<ValuePtr> _rparams, BlockPtr _father) { return new CallInst(_dest, _func, _rparams, _father); }
	void print( ) {
		printf("    [Call]  dest:%s  func:%s", dest->alloc_addr.c_str( ), func->name.c_str( ));
		printf("  rparms:(");
		for (Value *v : rparams) {
			printf("<v:%s>", v->alloc_addr.c_str( ));
		}
		printf(")\n");
	}
	std::vector<Value *> get_val( ) {
		std::vector<Value *> res;
		res.push_back(dest);
		for (Value *v : rparams) {
			res.push_back(v);
		}
		return res;
	}
};

// BranchInst 条件跳转
// 由于block保留了循环和分支的特征，因此这个语句是否使用需确定
// 但是break、continue可能仍需使用这个指令
class BranchInst : public Instruction { // IR br 指令
  private:
  public:
	Value *cond;	   //条件 NULL时认定为无条件跳转，到 if_true
	BlockPtr if_true;  // 条件成里跳转到这里
	BlockPtr if_false; // 条件不成立跳转到另一个地方
	BranchInst(ValuePtr _cond, BlockPtr _if_true, BlockPtr _if_false, BlockPtr _father) : Instruction(Br, _father), if_true(_if_true), if_false(_if_false) {
		cond = to_static_pointer(_cond);
	}

  public:
	static BranchInst *createBr(ValuePtr _cond, BlockPtr _if_true, BlockPtr _if_false, BlockPtr _father) { return new BranchInst(_cond, _if_true, _if_false, _father); }
	static BranchInst *createBr(BlockPtr _true, BlockPtr _father) { return new BranchInst(NULL, _true, NULL, _father); }
	void print( );
	std::vector<Value *> get_val( );
};

// GEPInst 获取指向数组元素的指针,只执行地址运算，不访问内存
// v[3][4]是一个数组
// dest = &(v[2][3]);
class GEPInst : public Instruction { // IR getelementptr 指令
  private:
  public:
	Value *dest;				   //目的变量
	Value *v;					   //数组的起始地址
	std::vector<int> inbounds;	   //数组的维度int a[3] 这里的3
	std::vector<ValuePtr> inrange; //数组的偏移

	GEPInst(ValuePtr _dest, ValuePtr _v, std::vector<int> _inbounds, std::vector<ValuePtr> _inrange, BlockPtr _father) : Instruction(GEP, _father), inbounds(_inbounds), inrange(_inrange) {
		dest = to_static_pointer(_dest);
		v = to_static_pointer(_v);
	}

  public:
	static GEPInst *createGEP(ValuePtr _dest, ValuePtr _v, std::vector<int> _inbounds, std::vector<ValuePtr> _inrange, BlockPtr _father) { return new GEPInst(_dest, _v, _inbounds, _inrange, _father); }
	void print( ) {
		printf("    [GEP]  dest:%s  v:%s", dest->alloc_addr.c_str( ), v->alloc_addr.c_str( ));
		printf("  inbounds:(");
		int size = inbounds.size( );
		if (size > 0) {
			printf("%d", inbounds[0]);
			for (int i = 1; i < size; i++) {
				printf(",%d", inbounds[i]);
			}
		}
		printf(")");
		printf("  inrange:(");
		size = inrange.size( );
		if (size > 0) {
			printf("%s", inrange[0]->alloc_addr.c_str( ));
			for (int i = 1; i < size; i++) {
				printf(",%s", inrange[i]->alloc_addr.c_str( ));
			}
		}
		printf(")\n");
	}
	std::vector<Value *> get_val( ) {
		std::vector<Value *> res;
		res.push_back(dest);
		res.push_back(v);
		return res;
	}
};

// ReturnInst 返回指令，ret_v指定返回值
// 这里需要code处理返回
class ReturnInst : public Instruction { // IR ret 指令
  private:
  public:
	bool isVoid;
	Value *ret_v; //返回值
	ReturnInst(ValuePtr v, BlockPtr _father) : Instruction(Ret, _father), isVoid(false) {
		ret_v = to_static_pointer(v);
	}
	ReturnInst(BlockPtr _father) : Instruction(Ret, _father), isVoid(true) { ret_v = NULL; }

  public:
	static ReturnInst *createRet(ValuePtr v, BlockPtr _father) { return new ReturnInst(v, _father); }
	static ReturnInst *createRet(BlockPtr _father) { return new ReturnInst(_father); }

	void print( ) {
		if (isVoid) {
			printf("    [Ret]\n");
		} else {
			printf("    [Ret]  val:%s\n", ret_v->alloc_addr.c_str( ));
		}
	}
	std::vector<Value *> get_val( ) {
		std::vector<Value *> res;
		res.push_back(ret_v);
		return res;
	}
};

// PhiInst phi指令，根据当前block之前执行的是哪一个block来得到相应的值
// 这个指令是为了实现SSA，即每个变量只被赋值一次。如：
// if(a){
// 	b = 1;
// }
// else{
// 	b = 2
// }
// c=b
// b被赋值两次，不满足SSA，因此需对变量如下处理：
// if(a){
// 	b1 = 1;
// }
// else{
// 	b2 = 2
// }
// c = PhiInst( <b1,block1>, <b2,block2> )
// 后续代码通过phi指令判定控制流是从哪个block走过来的
// 来确定使用b1还是b2作为b的数值
// class PhiInst : public Instruction {  // IR phi 指令
//    private:
//    public:
//    //TODO:考虑pair_list、_vector
// 	std::map<shared_ptr<Block>, ValuePtr> label_list;	//参数表 key表示来自于哪一个块，value表示对应的取值
// 	ValuePtr dest;
// };

#endif
