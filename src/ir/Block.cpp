#include "Block.hpp"

void Block::add_inst(Instruction *i) {
	this->inst_list.push_back(i);
}

void Block::print( ) {
	//块入口名
	printf("%s:\n", name.c_str( ));
	// 指令
	for (Instruction *inst : inst_list) {
		if (inst->itype == Br) { //分支指令
		}
		inst->print( );
	}
	printf("\n");
	if (this->next_to_build != NULL) {
		printf("\n");
		BlockPtr p = std::static_pointer_cast<Block>(this->next_to_build);
		p->print( );
	}
}