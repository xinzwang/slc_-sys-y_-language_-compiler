#ifndef DRIVER_H
#define DRIVER_H

#include "Ast.hpp"

#include "parser.hpp"
#include "pre.hpp"
#include "scanner.hpp"
#include "IrGen.hpp"

#include <iostream>

namespace Marker {
//驱动类
class Driver {
  private:
	Pre pre;
	Scanner scanner;
	Parser parser;

  public:
	Ast ast;

	int run(std::string &file);

	Driver( );
	virtual ~Driver( );
};

} // namespace Marker

#endif