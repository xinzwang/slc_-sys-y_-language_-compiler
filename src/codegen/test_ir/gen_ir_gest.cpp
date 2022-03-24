#include <iostream>
#include <memory>

#include "Instruction.hpp"
#include "Module.hpp"
#include "Value.hpp"

void test_ir_gen( ) {
	Module* m = new Module( );

	shared_ptr<Const> const_1 = make_shared_ptr<Const>( );

	const_1.get( )->name = "const_1";
	const_1.

		m->global_const_list.push_back(const_1);
}