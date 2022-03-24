#ifndef INSASMCODE_HPP
#define INSASMCODE_HPP

#include "Instruction.hpp"
#include "Value.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace Inscode
{
    const std::string space = std::string("    ");
    const std::string newline = "\n";

    int var_shift_mtop(std::map<std::string, int> *var_shift);
    int fun_has_call(Function *func);
    std::string cond(BranchInst *ins);
    std::string br(BranchInst *ins);
    std::string ret(ReturnInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string alloc(AllocaInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string store(StoreInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string add(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string sub(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string Mul(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string Div(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string And(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string OR(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string ASR(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string AShr(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string LSL(BinaryInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string CMP(CmpInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);
    std::string Call(CallInst *ins, std::map<std::string, int> *var_shift, std::map<Value *, int> *reg_map);

} // namespace Inscode

#endif