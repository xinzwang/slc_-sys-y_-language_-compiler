#include "AsmCodeGen.hpp"
/**
 * 全局变量每次需要取地址
 * 局部变量由寄存器指出其位置，如果是0-12 则在对应的寄存器中，直接向内存取
 * 若为 -1，则对应的变量需要在内存寻找。
 */

std::map<Value *, int> CodeGen::reg_alloc( ) {
	std::map<Value *, int> res;
	for (FuncPtr func : this->_module->fun_list) {
		//0. 变量
		std::set<Instruction *> values;
		std::list<Reg *> regs;
		for (int i : all_regs) { //寄存器队列
			Reg *r = new Reg( );
			r->id = i;
			r->alloc_addr = "";
			r->is_used = false;
			regs.push_front(r);
		}
		//1. 找到所有需要分配寄存器的地方
		// for (FParam *args : func->fparam_lst) { //所有形式参数
		// 	values.insert(args);
		// }
		for (BlockPtr b = func->block; b != NULL; b = b->next_to_build) { //所有指令
			for (Instruction *inst : b->inst_list) {
				values.insert(inst);
			}
		}
		//2. 线性扫描，给变量分配寄存器
		for (Instruction *val : values) {
			//指令
			Instruction *inst = val;
			for (Value *v : inst->get_val( )) {
				if (v->vtype == VALUE_REG) {
					bool find = false;
					for (Reg *r : regs) {
						if (v->alloc_addr == r->alloc_addr) {
							res[v] = r->id;
							find = true;
							break;
						}
					}
					if (!find) {
						Reg *r = regs.front( );
						regs.pop_front( );
						regs.push_back(r);
						r->alloc_addr = v->alloc_addr;
						res[v] = r->id;
					}
				} else if (v->vtype == VALUE_VARINT) {
					res[v] = -1;
					printf("[WARNING] reg_alloc()-%d  expect:ValueReg, get ValueInt.\n", __LINE__);
				} else {
					res[v] = -1;
					printf("[WARNING] reg_alloc()-%d  expect:ValueReg.\n", __LINE__);
				}
			}
		}
	}
	return res;
}

// std::map<Value *, int> reg_alloc_color( ) {
// 	std::map<Value *, int> reg_map;

// 	for (FuncPtr func : _module->fun_list) {
// 		std::map<Block *, std::set<Value *>> live_in;
// 		std::map<Block *, std::set<Value *>> live_out;
// 		std::map<Value *, std::set<Value *>> IG;
// 		std::map<Value *, double> weight;
// 		std::set<Value *> values;

// 		// 1. 获取所有 Value
// 		for (FParam *args : func->fparam_lst) { //所有形式参数
// 			values.insert(args);
// 		}
// 		for (BlockPtr b = func->block; b != NULL; b = b->next_to_build) { //所有指令
// 			for (Instruction *inst : b->inst_list) {
// 				values.insert(inst);
// 			}
// 		}
// 		// 2. 计算 live in
// 		for (Value *v : values) {
// 			std::queue<BlockPtr> que;
// 			if (!dynamic_cast<Instruction *>(v)) { //不是指令，是变量
// 				live_in[func->block].insert(v);	   //函数的第一个块，插入v
// 				que.push(func->block);
// 				live_in[que.front].insert(v);
// 			} else { //是指令
// 				BlockPtr b = dynamic_cast<Instruction *>(v)->father;
// 				for (BlockPtr next : b->next) {
// 					que.push(next);
// 					live_in[next].insert(v);
// 				}
// 			}
// 			while (!que.empty( )) { //宽搜，对所有块的in,所有此value能到达的block添加live_in
// 				BlockPtr x = que.front( );
// 				que.pop( );
// 				for (BlockPtr next : x->next) {
// 					if (next != NULL && !live_in[next].count(v)) {
// 						live_in[next], insert(v);
// 						que.push(next);
// 					}
// 				}
// 			}
// 		}
// 		// 3. 计算 live out
// 		for (BlockPtr b = func->block; b != NULL; b = b->next_to_build) { //遍历所有块
// 			for (Instruction * inst->inst_list) {
// 				for (Value *v : inst->get_val( )) { //遍历操作数
// 					if (!values.count(v)) {			//屏蔽某些变量？！ 常量、？？
// 						continue;
// 					}
// 					std::queue<BlockPtr> que;
// 					bool flag = false;
// 					for (Instruction *pre_inst : b->inst_list) { //遍历所有的上一个块
// 						if (pre_inst == inst) {
// 							break;
// 						}
// 						if (pre_inst == v) {
// 							flag = true;
// 							break;
// 						}
// 					}
// 					if (flag) {
// 						continue;
// 					}
// 					for (BlockPtr pre_block : b->pre) {
// 						que.push(pre_block);
// 						live_out[pre_block].insert(v);
// 					}
// 				}
// 				while (!que.empty( )) {
// 					BlockPtr x = que.front( );
// 					que.pop( );
// 					bool flag = false;
// 					for (Instruction *pre_inst : x->inst_list) {
// 						if (pre_inst == v) {
// 							flag = true;
// 							break;
// 						}
// 					}
// 					if (flag) {
// 						continue;
// 					}
// 					for (BlockPtr pre_block : x->pre) {
// 						if (!live_out[pre_block].count(v)) {
// 							que.push(pre_block);
// 							live_out[pre_block].insert(v);
// 						}
// 					}
// 				}
// 			}
// 		}
// 		// 4. 计算 IG 推理图
// 		for (Value *i : func->fparam_lst) {
// 			for (Value *j : func->fparam_lst) {
// 				if (i != j) {
// 					IG[i].insert(j);
// 				}
// 			}
// 		}
// 		for (BlockPtr b = func->block; b != NULL; b = b->next_to_build) {
// 			std::set<Value *> living = live_in[b];
// 			std::map<Value *, int> remain;
// 			for (auto &v : live_in[b]) {
// 				bool flag = true;
// 				for (Instruction *inst : b->inst_list) {
// 					for (Value *val : inst->get_val( )) {
// 						if (val == v) {
// 							remain[v]++;
// 						}
// 					}
// 					if (inst == v) {
// 						flag = false;
// 						break;
// 					}
// 				}
// 				if (flag) {
// 					if (live_out[b].count(v)) {
// 						remain[v]++;
// 					}
// 				}
// 				//所有的指令
// 				for (Instruction *inst : b->inst_list) {
// 					for (Value *val : inst->get_val( )) {
// 					}
// 				}
// 			}
// 		}
// 		// 5. 着色
// 		std::vector<std::pair<double, Instruction *>> inst_list;
// 		for (auto &inst : values) {
// 			inst_list.push_back({weight[inst], inst});
// 		}
// 	}

// 	return reg_map;
// }