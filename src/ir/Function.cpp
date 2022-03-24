#include "Function.hpp"

void Function::print( ) {
	std::string t = (type == TYPE_VOID) ? "void" : "int";
	printf("Function:  type:%s  name:%s", t.c_str( ), name.c_str( ));
	printf("  fparams:(");
	int size = fparam_lst.size( );
	if (size > 0) {
		fparam_lst[0]->print( );
		for (int i = 1; i < size; i++) {
			fparam_lst[i]->print( );
		}
	}
	printf(")\n");
	//Block输出
	if (this->block != nullptr)
		this->block->print( );
}

Value *Function::copy( ) {
	return this;
}

int Function::alloced_size( ) {
	int res;
	for (BlockPtr b = this->block; b != NULL; b = b->next_to_build) {
		for (Instruction *inst : b->inst_list) {
			if (inst->itype == Alloca) {
				res += ((AllocaInst *)inst)->size;
			}
		}
	}
	return res;
}
