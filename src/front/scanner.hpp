#ifndef LEXER_H
#define LEXER_H

//重要，作用不详
#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Marker_FlexLexer // 根据prefix修改

#include <FlexLexer.h>

#endif

#undef YY_DECL
#define YY_DECL Marker::Parser::symbol_type Marker::Scanner::nextToken( )

#include "parser.hpp"

namespace Marker {
class Driver;

//词法分析类
class Scanner : public yyFlexLexer {
  private:
	Driver &driver;

  public:
	Scanner(Marker::Driver &driver) : driver(driver) {}

	virtual Marker::Parser::symbol_type nextToken( ); //此函数由Flex生成

	virtual ~Scanner( ) {}
};
} // namespace Marker

#endif