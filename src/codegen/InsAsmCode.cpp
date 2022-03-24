#include "InsAsmCode.hpp"
#include "Const.hpp"
#include "Instruction.hpp"

#include <cmath>
#include <string>
#include <tuple>

namespace Inscode {

void set_alloced_size(int s) {
	int alloced_size = s;
}

int fun_has_call(Function *func) {
	auto bb = func->block.get( );
	if (bb != nullptr) {
		for (int i = 0; i < (int)bb->next.size( ); i++)
			for (auto &ins : bb->inst_list) {
				if (ins->itype == IrType::Call)
					return 1;
			}
	}
	return 0;
}

int var_shift_mtop(std::map<std::string, int> *var_shift) { //获取可以使用的堆位置
	int des = 0;
	std::map<std::string, int>::iterator it;
	for (it = var_shift->begin( ); it != var_shift->end( ); it++) {
		if (it->second < des)
			des = it->second;
	}
	return des;
}
std::string Call(CallInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	//准备参数
	if (ins->rparams.size( ) <= 4) {
		for (int i = 0; i < (int)ins->rparams.size( ); i++) {
			if (ins->rparams[i]->vtype == VALUE_CONSTINT)
				res += Inscode::space + "mov    r" + std::to_string(i) + ", #" + std::to_string(((ConstInt *)ins->rparams[i])->val) + Inscode::newline;
			else {
				res += Inscode::space + "mov    r" + std::to_string(i) + ", r" + std::to_string(reg_map->at(ins->rparams.at(i))) + Inscode::newline;
			}
		}
	} else {
		for (int i = 4; i < (int)ins->rparams.size( ); i++) {
			if (ins->rparams[i]->vtype == VALUE_CONSTINT) {
				res += Inscode::space + "mov    r" + std::to_string(i - 4) + ", #" + std::to_string(((ConstInt *)ins->rparams[i])->val) + Inscode::newline;
				res += Inscode::space + "str    r" + std::to_string(i - 4) + ", [sp, #" + std::to_string((i - 4) * 4) + "]" + Inscode::newline;
			} else {
				res += Inscode::space + "ldr    r" + std::to_string(i - 4) + ", [fp, #" + std::to_string(var_shift->at(ins->rparams.at(i)->alloc_addr)) + "]" + Inscode::newline;
				res += Inscode::space + "str    r" + std::to_string(i - 4) + ", [sp, #" + std::to_string((i - 4) * 4) + "]" + Inscode::newline;
			}
		}
		res += Inscode::space + "bl    " + ins->func->name + Inscode::newline;
		return res;
	}
}

std::string ret(ReturnInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	if (ins->ret_v->vtype == VALUE_CONSTINT) {
		res += Inscode::space + "mov     r0, #" + ins->ret_v->alloc_addr + Inscode::newline;
	} else if (ins->ret_v->vtype == VALUE_VARINT) {
		res += Inscode::space + "ldr    r1, [sp, #" + std::to_string((*var_shift)["%" + ins->ret_v->name]) + "]\n";
		res += Inscode::space + "mov     r0, r1\n";
	}
	// res += Inscode::space "add    sp, fp, #0" + Inscode::newline;
	// res += Inscode::space "ldr    fp, [sp],#4"+Inscode::newline;
	// res += "bx    lr"+Inscode::newline;
	return res;
}

std::string br(BranchInst *ins) {
	std::string res;
	//无条件跳转
	if (ins->cond == nullptr)
		res += Inscode::space + "bl    " + ins->if_true->name + Inscode::newline;
	else {
		res += Inscode::space + "bne    " + ins->if_true->name + Inscode::newline;
		res += Inscode::space + "b    " + ins->if_true->name + Inscode::newline;
	}
	return res;
}

std::string alloc(AllocaInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	(*var_shift)[ins->dest->alloc_addr] = var_shift_mtop(var_shift) - 4;
	// res += Inscode::space + "mov     r0" + ", #0" + Inscode::newline;
	// res += Inscode::space + "str     r0" + "," + "[fp, #" + std::to_string(var_shift->at(ins->dest->alloc_addr)) + "]" + Inscode::newline;
	return res;
}

std::string store(StoreInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	if (ins->v == NULL) //写入int的值
	{
		res += Inscode::space + "mov    r0" + ", #" + std::to_string(ins->num) + Inscode::newline;
		res += Inscode::space + "str    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->dest->name]) + "]\n";
	} else //写入v的值
	{
		//res += Inscode::space + "ldr    r" + std::to_string(reg_index) + "," + "[fp, #" + std::to_string(var_shift->at(ins->dest)) + "]"+Inscode::newline;
		res += Inscode::space + "str    r" + std::to_string(reg_map->at(ins->v)) + ", " + "[fp, #" + std::to_string((*var_shift)[ins->dest->alloc_addr]) + "]\n";
	}
	return res;
}

std::string add(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::map<std::string, int>::iterator i;
	for (i = var_shift->begin( ); i != var_shift->end( ); i++)
		std::cout << i->first << "---->" << i->second << std::endl;
	std::string res;
	std::string reg_des = std::to_string(reg_map->at(ins->dest));
	std::string reg_1 = std::to_string(reg_map->at(ins->v1));
	std::string reg_2 = std::to_string(reg_map->at(ins->v2));
	res += Inscode::space + "ldr    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->v1->name]) + "]\n";
	res += Inscode::space + "ldr    r1, [fp, #" + std::to_string((*var_shift)["%" + ins->v2->name]) + "]\n";
	res += Inscode::space + "add    r" + reg_des + ", r0, r1" + Inscode::newline;
	return res;
}
std::string sub(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	std::string reg_des = std::to_string(reg_map->at(ins->dest));
	std::string reg_1 = std::to_string(reg_map->at(ins->v1));
	std::string reg_2 = std::to_string(reg_map->at(ins->v2));
	res += Inscode::space + "ldr    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->v1->name]) + "]\n";
	res += Inscode::space + "ldr    r1, [fp, #" + std::to_string((*var_shift)["%" + ins->v2->name]) + "]\n";
	res += Inscode::space + "sub    r" + reg_des + ", r0, r1" + Inscode::newline;
	return res;
}

std::string Mul(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	std::string reg_des = std::to_string(reg_map->at(ins->dest));
	std::string reg_1 = std::to_string(reg_map->at(ins->v1));
	std::string reg_2 = std::to_string(reg_map->at(ins->v2));
	res += Inscode::space + "ldr    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->v1->name]) + "]\n";
	res += Inscode::space + "ldr    r1, [fp, #" + std::to_string((*var_shift)["%" + ins->v2->name]) + "]\n";
	res += Inscode::space + "mul    r" + reg_des + ", r0, r1" + Inscode::newline;
	return res;
}

std::string Div(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	std::string reg_des = std::to_string(reg_map->at(ins->dest));
	std::string reg_1 = std::to_string(reg_map->at(ins->v1));
	std::string reg_2 = std::to_string(reg_map->at(ins->v2));
	res += Inscode::space + "ldr    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->v1->name]) + "]\n";
	res += Inscode::space + "ldr    r1, [fp, #" + std::to_string((*var_shift)["%" + ins->v2->name]) + "]\n";
	res += Inscode::space + "div    r" + reg_des + ", r0, r1" + Inscode::newline;
	return res;
}

std::string And(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	std::string reg_des = std::to_string(reg_map->at(ins->dest));
	std::string reg_1 = std::to_string(reg_map->at(ins->v1));
	std::string reg_2 = std::to_string(reg_map->at(ins->v2));
	res += Inscode::space + "ldr    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->v1->name]) + "]\n";
	res += Inscode::space + "ldr    r1, [fp, #" + std::to_string((*var_shift)["%" + ins->v2->name]) + "]\n";
	res += Inscode::space + "and    r" + reg_des + ", r0, r1" + Inscode::newline;
	return res;
}

std::string OR(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	std::string reg_des = std::to_string(reg_map->at(ins->dest));
	std::string reg_1 = std::to_string(reg_map->at(ins->v1));
	std::string reg_2 = std::to_string(reg_map->at(ins->v2));
	res += Inscode::space + "ldr    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->v1->name]) + "]\n";
	res += Inscode::space + "ldr    r1, [fp, #" + std::to_string((*var_shift)["%" + ins->v2->name]) + "]\n";
	res += Inscode::space + "orr    r" + reg_des + ", r0, r1" + Inscode::newline;
	return res;
}

//算术右移
std::string ASR(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	std::string reg_des = std::to_string(reg_map->at(ins->dest));
	std::string reg_1 = std::to_string(reg_map->at(ins->v1));
	std::string reg_2 = std::to_string(reg_map->at(ins->v2));
	res += Inscode::space + "ldr    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->v1->name]) + "]\n";
	res += Inscode::space + "ldr    r1, [fp, #" + std::to_string((*var_shift)["%" + ins->v2->name]) + "]\n";
	res += Inscode::space + "asr    r" + reg_des + ", r0, r1" + Inscode::newline;
	return res;
}
//逻辑右移
std::string AShr(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	std::string reg_des = std::to_string(reg_map->at(ins->dest));
	std::string reg_1 = std::to_string(reg_map->at(ins->v1));
	std::string reg_2 = std::to_string(reg_map->at(ins->v2));
	res += Inscode::space + "ldr    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->v1->name]) + "]\n";
	res += Inscode::space + "ldr    r1, [fp, #" + std::to_string((*var_shift)["%" + ins->v2->name]) + "]\n";
	res += Inscode::space + "lsr    r" + reg_des + ", r0, r1" + Inscode::newline;
	return res;
}
//逻辑左移
std::string LSL(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	std::string reg_des = std::to_string(reg_map->at(ins->dest));
	std::string reg_1 = std::to_string(reg_map->at(ins->v1));
	std::string reg_2 = std::to_string(reg_map->at(ins->v2));
	res += Inscode::space + "ldr    r0, [fp, #" + std::to_string((*var_shift)["%" + ins->v1->name]) + "]\n";
	res += Inscode::space + "ldr    r1, [fp, #" + std::to_string((*var_shift)["%" + ins->v2->name]) + "]\n";
	res += Inscode::space + "lsl    r" + reg_des + ", r0, r1" + Inscode::newline;
	return res;
}

std::string CMP(CmpInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map) {
	std::string res;
	// res += Inscode::space + "ldr    r" + std::to_string(reg_index_1) + "," + "[fp, #" + std::to_string(var_shift[ins->v1]) + "]"+Inscode::newline;
	// res += Inscode::space + "ldr    r" + std::to_string(reg_index_1) + "," + "[fp, #" + std::to_string(var_shift[ins->v2]) + "]"+Inscode::newline;
	// res += "cmp    r" + std::to_string(reg_index_1) + ", r" + std::to_string(reg_index_2);
	res += Inscode::space + "cmp" + Inscode::newline;
	return res;
}

} // namespace Inscode
