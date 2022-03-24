#include "Ir.hpp"

using namespace std;

void IrBuilder::init(Scope *scope) {
	this->scope = scope;
	this->_reg_seq = 0;
	this->_block_seq = 0;
	this->_module = new Module( );
	// this->block = new Block( );
}

string IrBuilder::addGlobalConst(ValuePtr val) {
	ConstPtr c = std::static_pointer_cast<Const>(val); //强制类型转换
	this->_module->global_const_list.push_back(c);
	val->alloc_addr = "@" + val->name;
	return val->alloc_addr;
}

string IrBuilder::addConst(ValuePtr val) {
	int size = val->size;
	std::string name = val->name;
	// 变量
	if (val->vtype == VALUE_CONSTINT) {
		// ConstInt* c = (ConstInt*)val.get( );
		// alloca
		AllocaInst *inst_1 = AllocaInst::createAlloca(val, size, this->block);
		this->block->add_inst(inst_1);
		val->alloc_addr = "%" + val->name;
		// store
		StoreInst *inst_2 = StoreInst::createStore(val, std::static_pointer_cast<ConstInt>(val)->val, this->block);
		this->block->add_inst(inst_2);
		return val->alloc_addr;
	}
	// 数组
	else if (val->vtype == VALUE_CONSTARRAY) {
		std::shared_ptr<ConstArray> c = std::static_pointer_cast<ConstArray>(val);
		// alloca
		AllocaInst *inst_1 = AllocaInst::createAlloca(val, c->get_byte_size( ), this->block);
		this->block->add_inst(inst_1);
		val->alloc_addr = "%" + val->name;
		// store
		// TODO:确定数组初始化方案
		// 数组变量的初始化，从ConstArray中直接往内存中填数值。具体方案和codegen讨论决定
		return val->alloc_addr;
	}
	// 错误
	else {
		printf("[ERROR Ir.cpp-addConst-line:%d] expect const.\n", __LINE__);
		return "ERROR Ir.cpp-addConst";
	}
}
string IrBuilder::addGlobalVar(ValuePtr val) {
	VarPtr c = std::static_pointer_cast<Variable>(val); //强制类型转换
	this->_module->global_list.push_back(c);
	switch (val->vtype) {
	case VALUE_CONSTINT:
		break;
	case VALUE_CONSTARRAY:
		break;
	case VALUE_VARINT:
		break;
	case VALUE_VARARRAY:
		break;
	case VALUE_REG:
		break;
	default:
		break;
	}
	val->alloc_addr = "@" + val->name;
	return val->alloc_addr;
}

string IrBuilder::addVar(ValuePtr val) {
	int size = val->size;
	std::string name = val->name;
	// 变量
	if (val->vtype == VALUE_VARINT) {
		val->alloc_addr = "%" + val->name;
		AllocaInst *inst_1 = AllocaInst::createAlloca(val, size, this->block);
		this->block->add_inst(inst_1);

		// store
		VarIntPtr vp = std::static_pointer_cast<VarInt>(val);
		StoreInst *inst_2 = StoreInst::createStore(val, vp->val, this->block);
		this->block->add_inst(inst_2);
		return val->alloc_addr;
	}
	//数组
	else if (val->vtype == VALUE_VARARRAY) {
		std::shared_ptr<VarArray> c = std::static_pointer_cast<VarArray>(val);
		// alloca
		val->alloc_addr = "%" + val->name;
		AllocaInst *inst_1 = AllocaInst::createAlloca(val, c->get_byte_size( ), this->block);
		this->block->add_inst(inst_1);

		// store
		// TODO:确定数组初始化方案
		// 数组变量的初始化，从ConstArray中直接往内存中填数值。具体方案和codegen讨论决定
		return val->alloc_addr;
	}
	// 错误
	else {
		printf("[ERROR Ir.cpp-addVar-line:%d] expect variable. get:%s\n", __LINE__, val->alloc_addr.c_str( ));
		return "";
	}
}

string IrBuilder::addFunction(ValuePtr val) {
	if (val->vtype == VALUE_FUNCTION) {
		this->_block_seq = 0;
		FuncPtr c = std::static_pointer_cast<Function>(val); //强制类型转换
		this->_reg_seq = c->fparam_lst.size( );				 //传入的k个参量占据前 k个临时寄存器
		c->alloc_addr = c->name;
		this->_module->fun_list.push_back(c);
		this->_func = c;
		return c->alloc_addr;
	}
	// 错误
	else {
		printf("[ERROR Ir.cpp-addFunction-line:%d] expect function.\n", __LINE__);
		return "";
	}
}

BlockPtr IrBuilder::createBB( ) {
	BlockPtr bb(new Block( ));
	++this->_block_seq;
	bb->father = NULL;
	bb->name = _func->name + "_block_" + std::to_string(this->_block_seq);
	return bb;
}
void IrBuilder::setEntry(FuncPtr func, BlockPtr bb) {
	func->block = bb; //设置函数入口block
	return;
}

void IrBuilder::setInsertPoint(BlockPtr bb) {
	//block的插入点入口
	this->block = bb;
	return;
}

void IrBuilder::setIterationPoint(ValuePtr val) { return; }

void IrBuilder::insertStmt(ValuePtr val) { return; }

ValuePtr IrBuilder::getArrayLoadInst(ValuePtr v) {
	VarArrayRefPtr arr_ref = std::static_pointer_cast<VarArrayRef>(v);
	VarArrayPtr arr_name = std::static_pointer_cast<VarArray>(arr_ref->arr);
	// //创建临时寄存器
	// ++(this->_reg_seq);
	// std::string name = "%" + std::to_string(this->_reg_seq);
	// ValuePtr val_p(new VarReg(name));
	// val_p->alloc_addr = name;
	// 创建临时寄存器
	++(this->_reg_seq);
	std::string name = "%" + std::to_string(this->_reg_seq);
	ValuePtr dest(new VarReg(name));
	dest->alloc_addr = name;
	//创建指令
	GEPInst *inst_1 = GEPInst::createGEP(dest, arr_ref->arr, arr_name->dim, arr_ref->inrange, this->block); //获取数元素的内存地址
	this->block->add_inst(inst_1);
	// LoadInst *inst_2 = LoadInst::createInst(dest, val_p, this->block); //将元素提取到内存
	// this->block->add_inst(inst_2);
	return dest;
}

ValuePtr IrBuilder::getLoadInst(ValuePtr v) { //TODO:这里要处理数组的生成
	// 变量
	if (v->vtype == VALUE_VARINT) {
		// 创建临时寄存器
		++(this->_reg_seq);
		std::string name = "%" + std::to_string(this->_reg_seq);
		ValuePtr dest(new VarReg(name));
		dest->alloc_addr = name;
		// 创建指令
		LoadInst *inst = LoadInst::createInst(dest, v, this->block);
		this->block->add_inst(inst);
		return dest;
	}
	// 变量数组
	else if (v->vtype == VALUE_VARARRAY) {
		return getArrayLoadInst(v);
	}
	//错误
	else {
		//TODO: 常量、常量数组的数值有没有被计算？如果没有，和汇编确定这个数值怎么办？
		printf("Got TODO: Ir.cpp-getLoadInst()-line:%d\n", __LINE__);
		return NULL;
	}
}

ValuePtr IrBuilder::getUnaryInst(Unary_OP op, ValuePtr v) {
	//正号直接返回原值
	if (op == OP_POS) { //正号
		printf("[WARNING getUnaryInst]: %d", __LINE__);
		return v;
	}
	//创建临时寄存器
	++(this->_reg_seq);
	std::string name = "%" + string(std::to_string(this->_reg_seq));
	ValuePtr dest(new VarReg(name));
	dest->alloc_addr = name;
	//创建指令
	//负号
	if (op == OP_NEG) { //负号
		UnaryInst *inst = UnaryInst::createNeg(dest, v, this->block);
		this->block->add_inst(inst);
		return dest;
	}
	//非指令
	else if (op == OP_NOT) {
		UnaryInst *inst = UnaryInst::createNot(dest, v, this->block);
		this->block->add_inst(inst);
		return dest;
	}
	// 错误
	else {
		printf("[ERROR Ir.cpp-getUnaryInst line:%d] expect unary op.\n", __LINE__);
		return NULL;
	}
}

ValuePtr IrBuilder::getBinaryInst(Binary_OP op, ValuePtr v1, ValuePtr v2) {
	//创建临时寄存器
	++(this->_reg_seq);
	std::string name = "%" + string(std::to_string(this->_reg_seq));
	ValuePtr dest(new VarReg(name));
	dest->alloc_addr = name;
	//创建指令
	Instruction *inst;
	switch (op) {
	case OP_ADD:
		inst = BinaryInst::createAdd(dest, v1, v2, this->block);
		break;
	case OP_SUB:
		inst = BinaryInst::createSub(dest, v1, v2, this->block);
		break;
	case OP_MUL:
		inst = BinaryInst::createMul(dest, v1, v2, this->block);
		break;
	case OP_DIV:
		inst = BinaryInst::createDiv(dest, v1, v2, this->block);
		break;
	case OP_MOD:
		inst = BinaryInst::createRem(dest, v1, v2, this->block);
		break;
	case OP_AND:
		inst = BinaryInst::createAnd(dest, v1, v2, this->block);
		break;
	case OP_OR:
		inst = BinaryInst::createOr(dest, v1, v2, this->block);
		break;
	case OP_GT:
		inst = CmpInst::createCmp(CmpInst::GT, dest, v1, v2, this->block);
		break;
	case OP_LT:
		inst = CmpInst::createCmp(CmpInst::LT, dest, v1, v2, this->block);
		break;
	case OP_GTE:
		inst = CmpInst::createCmp(CmpInst::GE, dest, v1, v2, this->block);
		break;
	case OP_LTE:
		inst = CmpInst::createCmp(CmpInst::LE, dest, v1, v2, this->block);
		break;
	case OP_EQ:
		inst = CmpInst::createCmp(CmpInst::EQ, dest, v1, v2, this->block);
		break;
	case OP_NEQ:
		inst = CmpInst::createCmp(CmpInst::NE, dest, v1, v2, this->block);
	default:
		printf("[ERROR Ir.cpp-getBinaryInst line:%d] expect binary op.\n", __LINE__);
		return NULL;
	}
	this->block->add_inst(inst);
	return dest;
}

ValuePtr IrBuilder::getCallInst(ValuePtr func, vector<ValuePtr> rparams) {
	//创建临时寄存器
	++(this->_reg_seq);
	std::string name = "%" + string(std::to_string(this->_reg_seq));
	ValuePtr dest(new VarReg(name));
	dest->alloc_addr = name;
	//创建指令
	CallInst *inst = CallInst::createCall(dest, func, rparams, this->block);
	this->block->add_inst(inst);
	return dest;
}

ValuePtr IrBuilder::getAssignInst(ValuePtr vl, ValuePtr vr) {
	//TODO:根据赋值的变量类型，可能可以优化
	//已分配内存的变量，vr是变量的内存地址指针
	if (vr->vtype == VALUE_VARINT || vr->vtype == VALUE_VARARRAY) {
		ValuePtr v1 = getLoadInst(vr); //v1 = *(vr)
		StoreInst *inst_2 = StoreInst::createStore(vl, v1, this->block);
		this->block->add_inst(inst_2);
		return ValuePtr(new ConstInt(1));
	}
	//临时寄存器，存放的就是数值
	else if (vr->vtype == VALUE_REG) {
		StoreInst *inst_2 = StoreInst::createStore(vl, vr, this->block);
		this->block->add_inst(inst_2);
		return ValuePtr(new ConstInt(1));
	}
	//常量
	else if (vr->vtype == VALUE_CONSTINT) {
		StoreInst *inst_2 = StoreInst::createStore(vl, vr, this->block);
		this->block->add_inst(inst_2);
		return ValuePtr(new ConstInt(1));
	}
	//错误
	else {
		printf("[ERROR Ir.cpp-getAssignInst line:%d] expect variable value.\n", __LINE__);
		return NULL;
	}
}

ValuePtr IrBuilder::getIfElseBlock(ValuePtr vc, ValuePtr vi, ValuePtr ve) {
	BlockPtr bc = createBB( );
	bc->name += "_cond";
	return NULL;
}
ValuePtr IrBuilder::getIfBlock(ValuePtr vc, ValuePtr vi) { return NULL; }
ValuePtr IrBuilder::getWhileBlock(ValuePtr vc, ValuePtr vs) { return NULL; }
ValuePtr IrBuilder::getBreakInst( ) { return NULL; }
ValuePtr IrBuilder::getContinueInst( ) { return NULL; }
ValuePtr IrBuilder::getReturnInst( ) { return NULL; }
