%{
    #include<iostream>
    #include<string>

    #include"parser.hpp"
    #include"scanner.hpp"     //包含yylexLexer子类的头文件
    #include"location.hh"   //包含位置调试信息头文件

    static Marker::location loc;    //位置实例
    
    //该宏在每个记号的语义动作之前被调用，来根据记号的长度设置位置的信息
    #define YY_USER_ACTION loc.columns(yyleng);

    #undef yywrap
    #define yywrap() 1

    using namespace Marker;
    #define yyterminate() Parser::make_END(loc);
%}

%option c++
%option noyywrap debug

%option yyclass = "Scanner"
%option prefix="Marker_"

IntConst (([0-9]+)|([0-7]+)|((0x|0X)[0-9a-fA-F]+))(((u|U)?(l|L|ll|LL)?)|((l|L|ll|LL)?(u|U)?))
Ident [_a-zA-Z][_a-zA-Z0-9]*

%%
%{
    loc.step();
%}

{IntConst} {  return Parser::make_INTCONST(std::strtol(yytext,(&yytext+yyleng),10),loc);  }

[\t ] {  loc.step();  }

\n {
    loc.lines(yyleng);
    loc.step();
    //return Parser::make_EOL(loc);
}

"const" { return Parser::make_CONST(loc); }
"int" { return Parser::make_INT(loc); }
"void" { return Parser::make_VOID(loc); }
"if" { return Parser::make_IF(loc); }
"else" { return Parser::make_ELSE(loc); }
"while" { return Parser::make_WHILE(loc); }
"break" { return Parser::make_BREAK(loc); }
"continue" { return Parser::make_CONTINUE(loc); }
"return" { return Parser::make_RETURN(loc); }

";" { return Parser::make_SEMI(loc); }
"," { return Parser::make_COMMA(loc); }
"(" { return Parser::make_L_PAREN(loc); }
")" { return Parser::make_R_PAREN(loc); }
"[" { return Parser::make_L_BRACKET(loc); }
"]" { return Parser::make_R_BRACKET(loc); }
"{" { return Parser::make_L_BRACE(loc); }
"}" { return Parser::make_R_BRACE(loc); }

"=" { return Parser::make_ASSIGN(loc); }

">" { return Parser::make_GT(loc); }
"<" { return Parser::make_LT(loc); }
">=" { return Parser::make_GTE(loc); }
"<=" { return Parser::make_LTE(loc); }
"==" { return Parser::make_EQ(loc); }
"!=" { return Parser::make_NEQ(loc); }

"+" { return Parser::make_ADD(loc); }
"-" { return Parser::make_SUB(loc); }
"*" { return Parser::make_MUL(loc); }
"/" { return Parser::make_DIV(loc); }
"%" { return Parser::make_MOD(loc); }


"!" { return Parser::make_NOT(loc); }
"&&" { return Parser::make_AND(loc); }
"||" { return Parser::make_OR(loc); }


{Ident} { return Parser::make_IDENT(yytext,loc);  }

<<EOF>> {  return yyterminate(); }

.        {
            printf("[ERROR]-<parser>:Mystery character %s\n", yytext);
            loc.step();
        }
%%

