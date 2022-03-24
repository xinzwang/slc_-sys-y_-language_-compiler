#include "Instruction.hpp"

Value *to_static_pointer(ValuePtr v) {
	if (v.get( ) == NULL) {
		return NULL;
	}
	return v->copy( );
}

void BranchInst::print( ) {
	if (cond == NULL) {
		BlockPtr p = std::static_pointer_cast<Block>(if_true);
		printf("    [Br]  block:%s\n", p->name.c_str( ));
	} else {
		BlockPtr p1 = std::static_pointer_cast<Block>(if_true);
		BlockPtr p2 = std::static_pointer_cast<Block>(if_false);
		printf("    [Br]  cond:%s  true:%s  false:%s\n", cond->alloc_addr.c_str( ), p1->name.c_str( ), p2->name.c_str( ));
	}
	return;
}

std::vector<Value *> BranchInst::get_val( ) {
	std::vector<Value *> res;
	if (cond != NULL) {
		res.push_back(cond);
	}
	return res;
}
