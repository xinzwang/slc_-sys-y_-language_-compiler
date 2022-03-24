// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.
// //                    "%code top" blocks.
#line 33 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:397

	//尽可能放在parser.cpp头部
	#include <iostream>
  	#include "scanner.hpp"
  	#include "parser.hpp"
  	#include "Driver.hpp"
  	#include "location.hh"

	#include "Ast.hpp"
	#include "Type.hpp"

	static Marker::Parser::symbol_type yylex(Marker::Scanner& scanner,Marker::Driver &driver){
    	return scanner.nextToken();
  	}
  	using namespace Marker;

#line 51 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:397


// First part of user declarations.

#line 56 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

// User implementation prologue.

#line 70 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:479
namespace Marker {
#line 156 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   Parser :: Parser  (Marker::Scanner& scanner_yyarg, Marker::Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

   Parser ::~ Parser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
   Parser ::by_state::by_state ()
    : state (empty_state)
  {}

  inline
   Parser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   Parser ::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
   Parser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   Parser ::symbol_number_type
   Parser ::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
   Parser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   Parser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 66: // assignStmt
        value.move< ast_AssignStmt* > (that.value);
        break;

      case 57: // block
        value.move< ast_Block* > (that.value);
        break;

      case 59: // blockItem
        value.move< ast_BlockItem* > (that.value);
        break;

      case 58: // blockItems
        value.move< ast_BlockItems* > (that.value);
        break;

      case 83: // func_bracketList
        value.move< ast_BracketList* > (that.value);
        break;

      case 61: // breakStmt
        value.move< ast_BreakStmt* > (that.value);
        break;

      case 42: // st
      case 43: // compUnit
        value.move< ast_CompUnit* > (that.value);
        break;

      case 82: // const_bracketList
        value.move< ast_ConstBracketList* > (that.value);
        break;

      case 44: // constDecl
        value.move< ast_ConstDecl* > (that.value);
        break;

      case 46: // constDef
        value.move< ast_ConstDef* > (that.value);
        break;

      case 45: // constDefList
        value.move< ast_ConstDefList* > (that.value);
        break;

      case 48: // constInitList
        value.move< ast_ConstInitList* > (that.value);
        break;

      case 47: // constInitVal
        value.move< ast_ConstInitVal* > (that.value);
        break;

      case 62: // continueStmt
        value.move< ast_ContinueStmt* > (that.value);
        break;

      case 67: // exp
      case 68: // cond
      case 70: // primaryExp
      case 72: // unaryExp
      case 75: // mulExp
      case 76: // addExp
      case 77: // relExp
      case 78: // eqExp
      case 79: // landExp
      case 80: // lorExp
      case 81: // constExp
        value.move< ast_Expression* > (that.value);
        break;

      case 73: // funCall
        value.move< ast_FunCall* > (that.value);
        break;

      case 54: // funcDef
        value.move< ast_FuncDef* > (that.value);
        break;

      case 56: // funcFParam
        value.move< ast_FuncFParam* > (that.value);
        break;

      case 55: // funcFParams
        value.move< ast_FuncFParams* > (that.value);
        break;

      case 74: // funcRParams
        value.move< ast_FuncRParams* > (that.value);
        break;

      case 52: // initList
        value.move< ast_InitList* > (that.value);
        break;

      case 53: // initVal
        value.move< ast_InitVal* > (that.value);
        break;

      case 65: // iterationStmt
        value.move< ast_IterationStmt* > (that.value);
        break;

      case 69: // lVal
        value.move< ast_LVal* > (that.value);
        break;

      case 71: // number
        value.move< ast_Number* > (that.value);
        break;

      case 63: // returnStmt
        value.move< ast_ReturnStmt* > (that.value);
        break;

      case 64: // selectStmt
        value.move< ast_SelectStmt* > (that.value);
        break;

      case 60: // stmt
        value.move< ast_Stmt* > (that.value);
        break;

      case 50: // varDecl
        value.move< ast_VarDecl* > (that.value);
        break;

      case 51: // varDef
        value.move< ast_VarDef* > (that.value);
        break;

      case 49: // varDefList
        value.move< ast_VarDefList* > (that.value);
        break;

      case 35: // INTCONST
        value.move< int > (that.value);
        break;

      case 36: // IDENT
        value.move< string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 66: // assignStmt
        value.copy< ast_AssignStmt* > (that.value);
        break;

      case 57: // block
        value.copy< ast_Block* > (that.value);
        break;

      case 59: // blockItem
        value.copy< ast_BlockItem* > (that.value);
        break;

      case 58: // blockItems
        value.copy< ast_BlockItems* > (that.value);
        break;

      case 83: // func_bracketList
        value.copy< ast_BracketList* > (that.value);
        break;

      case 61: // breakStmt
        value.copy< ast_BreakStmt* > (that.value);
        break;

      case 42: // st
      case 43: // compUnit
        value.copy< ast_CompUnit* > (that.value);
        break;

      case 82: // const_bracketList
        value.copy< ast_ConstBracketList* > (that.value);
        break;

      case 44: // constDecl
        value.copy< ast_ConstDecl* > (that.value);
        break;

      case 46: // constDef
        value.copy< ast_ConstDef* > (that.value);
        break;

      case 45: // constDefList
        value.copy< ast_ConstDefList* > (that.value);
        break;

      case 48: // constInitList
        value.copy< ast_ConstInitList* > (that.value);
        break;

      case 47: // constInitVal
        value.copy< ast_ConstInitVal* > (that.value);
        break;

      case 62: // continueStmt
        value.copy< ast_ContinueStmt* > (that.value);
        break;

      case 67: // exp
      case 68: // cond
      case 70: // primaryExp
      case 72: // unaryExp
      case 75: // mulExp
      case 76: // addExp
      case 77: // relExp
      case 78: // eqExp
      case 79: // landExp
      case 80: // lorExp
      case 81: // constExp
        value.copy< ast_Expression* > (that.value);
        break;

      case 73: // funCall
        value.copy< ast_FunCall* > (that.value);
        break;

      case 54: // funcDef
        value.copy< ast_FuncDef* > (that.value);
        break;

      case 56: // funcFParam
        value.copy< ast_FuncFParam* > (that.value);
        break;

      case 55: // funcFParams
        value.copy< ast_FuncFParams* > (that.value);
        break;

      case 74: // funcRParams
        value.copy< ast_FuncRParams* > (that.value);
        break;

      case 52: // initList
        value.copy< ast_InitList* > (that.value);
        break;

      case 53: // initVal
        value.copy< ast_InitVal* > (that.value);
        break;

      case 65: // iterationStmt
        value.copy< ast_IterationStmt* > (that.value);
        break;

      case 69: // lVal
        value.copy< ast_LVal* > (that.value);
        break;

      case 71: // number
        value.copy< ast_Number* > (that.value);
        break;

      case 63: // returnStmt
        value.copy< ast_ReturnStmt* > (that.value);
        break;

      case 64: // selectStmt
        value.copy< ast_SelectStmt* > (that.value);
        break;

      case 60: // stmt
        value.copy< ast_Stmt* > (that.value);
        break;

      case 50: // varDecl
        value.copy< ast_VarDecl* > (that.value);
        break;

      case 51: // varDef
        value.copy< ast_VarDef* > (that.value);
        break;

      case 49: // varDefList
        value.copy< ast_VarDefList* > (that.value);
        break;

      case 35: // INTCONST
        value.copy< int > (that.value);
        break;

      case 36: // IDENT
        value.copy< string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
   Parser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   Parser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   Parser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   Parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   Parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 66: // assignStmt
        yylhs.value.build< ast_AssignStmt* > ();
        break;

      case 57: // block
        yylhs.value.build< ast_Block* > ();
        break;

      case 59: // blockItem
        yylhs.value.build< ast_BlockItem* > ();
        break;

      case 58: // blockItems
        yylhs.value.build< ast_BlockItems* > ();
        break;

      case 83: // func_bracketList
        yylhs.value.build< ast_BracketList* > ();
        break;

      case 61: // breakStmt
        yylhs.value.build< ast_BreakStmt* > ();
        break;

      case 42: // st
      case 43: // compUnit
        yylhs.value.build< ast_CompUnit* > ();
        break;

      case 82: // const_bracketList
        yylhs.value.build< ast_ConstBracketList* > ();
        break;

      case 44: // constDecl
        yylhs.value.build< ast_ConstDecl* > ();
        break;

      case 46: // constDef
        yylhs.value.build< ast_ConstDef* > ();
        break;

      case 45: // constDefList
        yylhs.value.build< ast_ConstDefList* > ();
        break;

      case 48: // constInitList
        yylhs.value.build< ast_ConstInitList* > ();
        break;

      case 47: // constInitVal
        yylhs.value.build< ast_ConstInitVal* > ();
        break;

      case 62: // continueStmt
        yylhs.value.build< ast_ContinueStmt* > ();
        break;

      case 67: // exp
      case 68: // cond
      case 70: // primaryExp
      case 72: // unaryExp
      case 75: // mulExp
      case 76: // addExp
      case 77: // relExp
      case 78: // eqExp
      case 79: // landExp
      case 80: // lorExp
      case 81: // constExp
        yylhs.value.build< ast_Expression* > ();
        break;

      case 73: // funCall
        yylhs.value.build< ast_FunCall* > ();
        break;

      case 54: // funcDef
        yylhs.value.build< ast_FuncDef* > ();
        break;

      case 56: // funcFParam
        yylhs.value.build< ast_FuncFParam* > ();
        break;

      case 55: // funcFParams
        yylhs.value.build< ast_FuncFParams* > ();
        break;

      case 74: // funcRParams
        yylhs.value.build< ast_FuncRParams* > ();
        break;

      case 52: // initList
        yylhs.value.build< ast_InitList* > ();
        break;

      case 53: // initVal
        yylhs.value.build< ast_InitVal* > ();
        break;

      case 65: // iterationStmt
        yylhs.value.build< ast_IterationStmt* > ();
        break;

      case 69: // lVal
        yylhs.value.build< ast_LVal* > ();
        break;

      case 71: // number
        yylhs.value.build< ast_Number* > ();
        break;

      case 63: // returnStmt
        yylhs.value.build< ast_ReturnStmt* > ();
        break;

      case 64: // selectStmt
        yylhs.value.build< ast_SelectStmt* > ();
        break;

      case 60: // stmt
        yylhs.value.build< ast_Stmt* > ();
        break;

      case 50: // varDecl
        yylhs.value.build< ast_VarDecl* > ();
        break;

      case 51: // varDef
        yylhs.value.build< ast_VarDef* > ();
        break;

      case 49: // varDefList
        yylhs.value.build< ast_VarDefList* > ();
        break;

      case 35: // INTCONST
        yylhs.value.build< int > ();
        break;

      case 36: // IDENT
        yylhs.value.build< string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 183 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { driver.ast.root = yystack_[0].value.as< ast_CompUnit* > (); }
#line 961 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 195 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { printf("Got empty"); yylhs.value.as< ast_CompUnit* > () = new ast_CompUnit(); }
#line 967 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 196 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_CompUnit* > () = new ast_CompUnit(); yylhs.value.as< ast_CompUnit* > ()->decl_def_list.push_back(yystack_[0].value.as< ast_ConstDecl* > ()); }
#line 973 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 197 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_CompUnit* > () = new ast_CompUnit(); yylhs.value.as< ast_CompUnit* > ()->decl_def_list.push_back(yystack_[0].value.as< ast_VarDecl* > ()); }
#line 979 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 198 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_CompUnit* > () = new ast_CompUnit(); yylhs.value.as< ast_CompUnit* > ()->decl_def_list.push_back(yystack_[0].value.as< ast_FuncDef* > ()); }
#line 985 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 199 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_CompUnit* > () = yystack_[1].value.as< ast_CompUnit* > (); yylhs.value.as< ast_CompUnit* > ()->decl_def_list.push_back(yystack_[0].value.as< ast_ConstDecl* > ()); }
#line 991 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 200 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_CompUnit* > () = yystack_[1].value.as< ast_CompUnit* > (); yylhs.value.as< ast_CompUnit* > ()->decl_def_list.push_back(yystack_[0].value.as< ast_VarDecl* > ()); }
#line 997 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 201 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_CompUnit* > () = yystack_[1].value.as< ast_CompUnit* > (); yylhs.value.as< ast_CompUnit* > ()->decl_def_list.push_back(yystack_[0].value.as< ast_FuncDef* > ()); }
#line 1003 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 205 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstDecl* > () = new ast_ConstDecl(); yylhs.value.as< ast_ConstDecl* > ()->type = TYPE_INT; yylhs.value.as< ast_ConstDecl* > ()->const_def_list = yystack_[1].value.as< ast_ConstDefList* > ()->const_def_list; delete yystack_[1].value.as< ast_ConstDefList* > (); }
#line 1009 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 208 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstDefList* > () = new ast_ConstDefList(); yylhs.value.as< ast_ConstDefList* > ()->const_def_list.push_back(yystack_[0].value.as< ast_ConstDef* > ()); }
#line 1015 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 209 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstDefList* > () = yystack_[2].value.as< ast_ConstDefList* > (); yylhs.value.as< ast_ConstDefList* > ()->const_def_list.push_back(yystack_[0].value.as< ast_ConstDef* > ()); }
#line 1021 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 212 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstDef* > () = new ast_ConstDef(); yylhs.value.as< ast_ConstDef* > ()->id = yystack_[2].value.as< string > (); yylhs.value.as< ast_ConstDef* > ()->const_init_val = yystack_[0].value.as< ast_ConstInitVal* > (); }
#line 1027 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 213 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstDef* > () = new ast_ConstDef(); yylhs.value.as< ast_ConstDef* > ()->id = yystack_[3].value.as< string > (); yylhs.value.as< ast_ConstDef* > ()->isArray = true; yylhs.value.as< ast_ConstDef* > ()->const_exp = yystack_[2].value.as< ast_ConstBracketList* > ()->const_exp_list; yylhs.value.as< ast_ConstDef* > ()->const_init_val = yystack_[0].value.as< ast_ConstInitVal* > (); }
#line 1033 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 216 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstInitVal* > () = new ast_ConstInitVal(); yylhs.value.as< ast_ConstInitVal* > ()->const_exp = yystack_[0].value.as< ast_Expression* > (); }
#line 1039 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 217 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstInitVal* > () = new ast_ConstInitVal(); }
#line 1045 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 218 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstInitVal* > () = new ast_ConstInitVal(); yylhs.value.as< ast_ConstInitVal* > ()->const_init_val_list = yystack_[1].value.as< ast_ConstInitList* > ()->const_init_list; delete yystack_[1].value.as< ast_ConstInitList* > (); }
#line 1051 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 221 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstInitList* > () = new ast_ConstInitList(); yylhs.value.as< ast_ConstInitList* > ()->const_init_list.push_back(yystack_[0].value.as< ast_ConstInitVal* > ()); }
#line 1057 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 222 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstInitList* > () = yystack_[2].value.as< ast_ConstInitList* > (); yylhs.value.as< ast_ConstInitList* > ()->const_init_list.push_back(yystack_[0].value.as< ast_ConstInitVal* > ()); }
#line 1063 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 225 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_VarDefList* > () = new ast_VarDefList(); yylhs.value.as< ast_VarDefList* > ()->var_def_list.push_back(yystack_[0].value.as< ast_VarDef* > ()); }
#line 1069 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 226 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_VarDefList* > () = yystack_[2].value.as< ast_VarDefList* > (); yylhs.value.as< ast_VarDefList* > ()->var_def_list.push_back(yystack_[0].value.as< ast_VarDef* > ()); }
#line 1075 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 229 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_VarDecl* > () = new ast_VarDecl(); yylhs.value.as< ast_VarDecl* > ()->type = TYPE_INT; yylhs.value.as< ast_VarDecl* > ()->var_def_list = yystack_[1].value.as< ast_VarDefList* > ()->var_def_list; delete yystack_[1].value.as< ast_VarDefList* > (); }
#line 1081 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 232 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_VarDef* > () = new ast_VarDef(); yylhs.value.as< ast_VarDef* > ()->id = yystack_[0].value.as< string > (); }
#line 1087 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 233 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_VarDef* > () = new ast_VarDef(); yylhs.value.as< ast_VarDef* > ()->id = yystack_[2].value.as< string > (); yylhs.value.as< ast_VarDef* > ()->init_val = yystack_[0].value.as< ast_InitVal* > (); }
#line 1093 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 234 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_VarDef* > () = new ast_VarDef(); yylhs.value.as< ast_VarDef* > ()->isArray = true; yylhs.value.as< ast_VarDef* > ()->id = yystack_[1].value.as< string > (); yylhs.value.as< ast_VarDef* > ()->const_exp = yystack_[0].value.as< ast_ConstBracketList* > ()->const_exp_list; delete yystack_[0].value.as< ast_ConstBracketList* > (); }
#line 1099 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 235 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_VarDef* > () = new ast_VarDef(); yylhs.value.as< ast_VarDef* > ()->isArray = true; yylhs.value.as< ast_VarDef* > ()->id = yystack_[3].value.as< string > (); yylhs.value.as< ast_VarDef* > ()->const_exp = yystack_[2].value.as< ast_ConstBracketList* > ()->const_exp_list; yylhs.value.as< ast_VarDef* > ()->init_val = yystack_[0].value.as< ast_InitVal* > (); delete yystack_[2].value.as< ast_ConstBracketList* > (); }
#line 1105 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 238 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_InitList* > () = new ast_InitList(); yylhs.value.as< ast_InitList* > ()->init_list.push_back(yystack_[0].value.as< ast_InitVal* > ()); }
#line 1111 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 239 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_InitList* > () = yystack_[2].value.as< ast_InitList* > (); yylhs.value.as< ast_InitList* > ()->init_list.push_back(yystack_[0].value.as< ast_InitVal* > ()); }
#line 1117 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 242 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_InitVal* > () = new ast_InitVal(); yylhs.value.as< ast_InitVal* > ()->exp = yystack_[0].value.as< ast_Expression* > (); }
#line 1123 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 243 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_InitVal* > () = new ast_InitVal(); }
#line 1129 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 244 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_InitVal* > () = new ast_InitVal(); yylhs.value.as< ast_InitVal* > ()->init_val_list = yystack_[1].value.as< ast_InitList* > ()->init_list; delete yystack_[1].value.as< ast_InitList* > (); }
#line 1135 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 247 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncDef* > () = new ast_FuncDef(); yylhs.value.as< ast_FuncDef* > ()->type = TYPE_VOID; yylhs.value.as< ast_FuncDef* > ()->id = yystack_[3].value.as< string > (); yylhs.value.as< ast_FuncDef* > ()->block =yystack_[0].value.as< ast_Block* > (); }
#line 1141 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 248 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncDef* > () = new ast_FuncDef(); yylhs.value.as< ast_FuncDef* > ()->type = TYPE_VOID; yylhs.value.as< ast_FuncDef* > ()->id = yystack_[4].value.as< string > (); yylhs.value.as< ast_FuncDef* > ()->func_params = yystack_[2].value.as< ast_FuncFParams* > ()->func_f_param_list; yylhs.value.as< ast_FuncDef* > ()->block = yystack_[0].value.as< ast_Block* > (); delete yystack_[2].value.as< ast_FuncFParams* > (); }
#line 1147 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 249 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncDef* > () = new ast_FuncDef(); yylhs.value.as< ast_FuncDef* > ()->type = TYPE_INT; yylhs.value.as< ast_FuncDef* > ()->id = yystack_[3].value.as< string > (); yylhs.value.as< ast_FuncDef* > ()->block = yystack_[0].value.as< ast_Block* > (); }
#line 1153 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 250 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncDef* > () = new ast_FuncDef(); yylhs.value.as< ast_FuncDef* > ()->type = TYPE_INT; yylhs.value.as< ast_FuncDef* > ()->id = yystack_[4].value.as< string > (); yylhs.value.as< ast_FuncDef* > ()->func_params = yystack_[2].value.as< ast_FuncFParams* > ()->func_f_param_list; yylhs.value.as< ast_FuncDef* > ()->block = yystack_[0].value.as< ast_Block* > (); delete yystack_[2].value.as< ast_FuncFParams* > (); }
#line 1159 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 253 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncFParams* > () = new ast_FuncFParams(); yylhs.value.as< ast_FuncFParams* > ()->func_f_param_list.push_back(yystack_[0].value.as< ast_FuncFParam* > ()); }
#line 1165 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 254 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncFParams* > () = yystack_[2].value.as< ast_FuncFParams* > (); yylhs.value.as< ast_FuncFParams* > ()->func_f_param_list.push_back(yystack_[0].value.as< ast_FuncFParam* > ()); }
#line 1171 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 257 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncFParam* > () = new ast_FuncFParam(); yylhs.value.as< ast_FuncFParam* > ()->type = TYPE_INT; yylhs.value.as< ast_FuncFParam* > ()->id = yystack_[0].value.as< string > (); }
#line 1177 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 258 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncFParam* > () = new ast_FuncFParam(); yylhs.value.as< ast_FuncFParam* > ()->type = TYPE_INT; yylhs.value.as< ast_FuncFParam* > ()->id = yystack_[1].value.as< string > (); yylhs.value.as< ast_FuncFParam* > ()->isArray = true; yylhs.value.as< ast_FuncFParam* > ()->param_array_list = yystack_[0].value.as< ast_BracketList* > ()->exp_list; delete yystack_[0].value.as< ast_BracketList* > (); }
#line 1183 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 261 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Block* > () = new ast_Block(); yylhs.value.as< ast_Block* > ()->block_item_list = yystack_[1].value.as< ast_BlockItems* > ()->block_items; delete yystack_[1].value.as< ast_BlockItems* > (); }
#line 1189 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 264 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BlockItems* > () = new ast_BlockItems(); }
#line 1195 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 265 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BlockItems* > () = yystack_[1].value.as< ast_BlockItems* > (); }
#line 1201 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 266 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BlockItems* > () = yystack_[1].value.as< ast_BlockItems* > (); yylhs.value.as< ast_BlockItems* > ()->block_items.push_back(yystack_[0].value.as< ast_BlockItem* > ()); }
#line 1207 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 270 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BlockItem* > () = new ast_BlockItem(); yylhs.value.as< ast_BlockItem* > ()->const_decl = yystack_[0].value.as< ast_ConstDecl* > (); }
#line 1213 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 271 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BlockItem* > () = new ast_BlockItem(); yylhs.value.as< ast_BlockItem* > ()->var_decl = yystack_[0].value.as< ast_VarDecl* > (); }
#line 1219 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 272 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BlockItem* > () = new ast_BlockItem(); yylhs.value.as< ast_BlockItem* > ()->stmt = yystack_[0].value.as< ast_Stmt* > (); }
#line 1225 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 275 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Stmt* > () = yystack_[0].value.as< ast_Block* > (); }
#line 1231 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 276 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Stmt* > () = yystack_[1].value.as< ast_Expression* > ();}
#line 1237 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 277 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Stmt* > () = yystack_[0].value.as< ast_AssignStmt* > (); }
#line 1243 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 278 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Stmt* > () = yystack_[0].value.as< ast_SelectStmt* > (); }
#line 1249 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 279 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Stmt* > () = yystack_[0].value.as< ast_IterationStmt* > (); }
#line 1255 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 280 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Stmt* > () = yystack_[0].value.as< ast_BreakStmt* > (); }
#line 1261 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 281 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Stmt* > () = yystack_[0].value.as< ast_ContinueStmt* > (); }
#line 1267 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 282 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Stmt* > () = yystack_[0].value.as< ast_ReturnStmt* > (); }
#line 1273 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 285 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BreakStmt* > () = new ast_BreakStmt(); }
#line 1279 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 288 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    {yylhs.value.as< ast_ContinueStmt* > () = new ast_ContinueStmt(); }
#line 1285 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 291 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ReturnStmt* > () = new ast_ReturnStmt(); }
#line 1291 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 292 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ReturnStmt* > () = new ast_ReturnStmt(); yylhs.value.as< ast_ReturnStmt* > ()->exp = yystack_[1].value.as< ast_Expression* > (); }
#line 1297 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 295 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_SelectStmt* > () = new ast_SelectStmt(); yylhs.value.as< ast_SelectStmt* > ()->cond = yystack_[2].value.as< ast_Expression* > (); yylhs.value.as< ast_SelectStmt* > ()->if_stmt = yystack_[0].value.as< ast_Stmt* > (); }
#line 1303 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 296 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_SelectStmt* > () = new ast_SelectStmt(); yylhs.value.as< ast_SelectStmt* > ()->cond = yystack_[4].value.as< ast_Expression* > (); yylhs.value.as< ast_SelectStmt* > ()->if_stmt = yystack_[2].value.as< ast_Stmt* > (); yylhs.value.as< ast_SelectStmt* > ()->else_stmt = yystack_[0].value.as< ast_Stmt* > (); }
#line 1309 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 299 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_IterationStmt* > () = new ast_IterationStmt(); yylhs.value.as< ast_IterationStmt* > ()->cond = yystack_[2].value.as< ast_Expression* > (); yylhs.value.as< ast_IterationStmt* > ()->stmt = yystack_[0].value.as< ast_Stmt* > (); }
#line 1315 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 302 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_AssignStmt* > () = new ast_AssignStmt(); yylhs.value.as< ast_AssignStmt* > ()->l_val = yystack_[3].value.as< ast_LVal* > (); yylhs.value.as< ast_AssignStmt* > ()->exp = yystack_[1].value.as< ast_Expression* > (); }
#line 1321 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 305 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1327 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 308 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1333 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 311 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_LVal* > () = new ast_LVal(); yylhs.value.as< ast_LVal* > ()->id = yystack_[0].value.as< string > (); }
#line 1339 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 312 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_LVal* > () = yystack_[3].value.as< ast_LVal* > (); yylhs.value.as< ast_LVal* > ()->array_exp_list.push_back(yystack_[1].value.as< ast_Expression* > ()); }
#line 1345 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 316 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Number* > (); }
#line 1351 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 317 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_LVal* > (); }
#line 1357 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 318 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[1].value.as< ast_Expression* > (); }
#line 1363 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 321 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Number* > () = new ast_Number(); yylhs.value.as< ast_Number* > ()->num = yystack_[0].value.as< int > (); }
#line 1369 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 324 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1375 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 325 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_FunCall* > (); }
#line 1381 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 326 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_UnaryExp* t = new ast_UnaryExp(); yylhs.value.as< ast_Expression* > () = t; t->op = OP_POS; t->unary_exp = yystack_[0].value.as< ast_Expression* > (); }
#line 1387 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 327 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_UnaryExp* t = new ast_UnaryExp(); yylhs.value.as< ast_Expression* > () = t; t->op = OP_NEG; t->unary_exp = yystack_[0].value.as< ast_Expression* > (); }
#line 1393 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 328 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_UnaryExp* t = new ast_UnaryExp(); yylhs.value.as< ast_Expression* > () = t; t->op = OP_NOT; t->unary_exp = yystack_[0].value.as< ast_Expression* > (); }
#line 1399 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 331 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FunCall* > () = new ast_FunCall(); yylhs.value.as< ast_FunCall* > ()->id = yystack_[3].value.as< string > (); yylhs.value.as< ast_FunCall* > ()->fun_r_params = yystack_[1].value.as< ast_FuncRParams* > ()->exp_list; delete yystack_[1].value.as< ast_FuncRParams* > (); }
#line 1405 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 334 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncRParams* > () = new ast_FuncRParams(); }
#line 1411 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 335 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncRParams* > ()=  new ast_FuncRParams(); yylhs.value.as< ast_FuncRParams* > ()->exp_list.push_back(yystack_[0].value.as< ast_Expression* > ()); }
#line 1417 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 336 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_FuncRParams* > () = yystack_[2].value.as< ast_FuncRParams* > (); yylhs.value.as< ast_FuncRParams* > ()->exp_list.push_back(yystack_[0].value.as< ast_Expression* > ()); }
#line 1423 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 339 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1429 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 340 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op =OP_MUL; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1435 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 341 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op =OP_DIV; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1441 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 342 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op =OP_MOD; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1447 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 345 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1453 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 346 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op = OP_ADD; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1459 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 347 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op = OP_SUB; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1465 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 350 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1471 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 351 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op = OP_GT; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1477 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 352 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op = OP_LT; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1483 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 353 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op = OP_GTE; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1489 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 354 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp2 = yystack_[2].value.as< ast_Expression* > (); t->op = OP_LTE; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1495 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 357 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1501 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 358 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op=OP_EQ; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1507 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 359 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op=OP_NEQ; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1513 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 362 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1519 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 363 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op = OP_AND; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1525 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 366 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1531 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 367 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { ast_BinaryExp* t = new ast_BinaryExp(); yylhs.value.as< ast_Expression* > () = (ast_Expression*)t; t->exp1 = yystack_[2].value.as< ast_Expression* > (); t->op = OP_OR; t->exp2 = yystack_[0].value.as< ast_Expression* > (); }
#line 1537 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 370 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_Expression* > () = yystack_[0].value.as< ast_Expression* > (); }
#line 1543 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 373 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstBracketList* > () = new ast_ConstBracketList(); yylhs.value.as< ast_ConstBracketList* > ()->const_exp_list.push_back(yystack_[1].value.as< ast_Expression* > ()); }
#line 1549 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 374 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_ConstBracketList* > () = yystack_[3].value.as< ast_ConstBracketList* > (); yylhs.value.as< ast_ConstBracketList* > ()->const_exp_list.push_back(yystack_[1].value.as< ast_Expression* > ()); }
#line 1555 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 377 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BracketList* > () = new ast_BracketList(); yylhs.value.as< ast_BracketList* > ()->exp_list.push_back(NULL); }
#line 1561 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 378 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BracketList* > () = new ast_BracketList(); yylhs.value.as< ast_BracketList* > ()->exp_list.push_back(yystack_[1].value.as< ast_Expression* > ()); }
#line 1567 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 379 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:859
    { yylhs.value.as< ast_BracketList* > () = yystack_[3].value.as< ast_BracketList* > (); yylhs.value.as< ast_BracketList* > ()->exp_list.push_back(yystack_[1].value.as< ast_Expression* > ()); }
#line 1573 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
    break;


#line 1577 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int  Parser ::yypact_ninf_ = -145;

  const signed char  Parser ::yytable_ninf_ = -1;

  const short int
   Parser ::yypact_[] =
  {
      83,    41,   -25,    31,    42,    83,  -145,  -145,  -145,    35,
      20,    12,  -145,    61,  -145,  -145,  -145,  -145,    17,   117,
    -145,    43,   185,   101,    21,  -145,    44,    62,   169,    37,
    -145,    35,    65,    86,    63,  -145,   185,   185,   185,   185,
    -145,    98,   100,  -145,  -145,  -145,  -145,    70,    23,    97,
      -5,  -145,  -145,    23,   185,   101,    38,  -145,    86,   125,
     144,  -145,  -145,   169,  -145,   105,  -145,  -145,   120,    86,
     124,  -145,  -145,  -145,   185,   185,   185,   185,   185,   185,
     185,  -145,  -145,     7,  -145,   142,  -145,  -145,    86,  -145,
    -145,    10,  -145,   171,   145,    99,  -145,  -145,  -145,  -145,
     152,   149,  -145,  -145,  -145,    70,    70,   101,  -145,  -145,
    -145,   169,  -145,  -145,   160,   185,    44,   170,   172,   177,
     178,    47,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,   179,    54,   185,  -145,  -145,
    -145,  -145,  -145,   175,   185,   185,  -145,  -145,  -145,   181,
    -145,   185,  -145,  -145,   187,    23,    74,   126,   161,   166,
     193,  -145,   197,   146,   185,   185,   185,   185,   185,   185,
     185,   185,   146,  -145,   203,    23,    23,    23,    23,    74,
      74,   126,   161,  -145,   146,  -145
  };

  const unsigned char
   Parser ::yydefact_[] =
  {
       3,     0,     0,     0,     0,     2,     4,     5,     6,     0,
      23,     0,    20,     0,     1,     7,     8,     9,     0,     0,
      11,     0,     0,     0,    25,    22,     0,     0,     0,     0,
      10,     0,     0,     0,     0,    36,     0,     0,     0,     0,
      70,    65,    68,    71,    67,    80,    72,    84,    99,     0,
       0,    24,    29,    63,     0,     0,    23,    21,     0,     0,
       0,    13,    15,     0,    12,    38,    41,    34,     0,     0,
       0,    73,    74,    75,    77,     0,     0,     0,     0,     0,
       0,   100,    30,     0,    27,     0,    26,    32,     0,    16,
      18,     0,    14,     0,    39,     0,    37,    35,    69,    78,
       0,     0,    81,    82,    83,    85,    86,     0,    31,   101,
      33,     0,    17,   102,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    40,    44,    45,    47,    43,    46,    52,
      53,    54,    50,    51,    49,     0,    68,     0,    76,    66,
      28,    19,   103,     0,     0,     0,    55,    56,    57,     0,
      48,     0,    79,   104,     0,    87,    92,    95,    97,    64,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    62,    59,    88,    89,    90,    91,    93,
      94,    96,    98,    61,     0,    60
  };

  const short int
   Parser ::yypgoto_[] =
  {
    -145,  -145,  -145,    -4,  -145,   182,   -48,  -145,  -145,    -3,
     188,  -145,   -47,   210,   189,   150,   -23,  -145,  -145,  -144,
    -145,  -145,  -145,  -145,  -145,  -145,   -31,    77,   -91,  -145,
    -145,   -21,  -145,  -145,    89,   -22,     6,    49,    52,  -145,
     -15,   206,  -145
  };

  const short int
   Parser ::yydefgoto_[] =
  {
      -1,     4,     5,     6,    19,    20,    61,    91,    11,     7,
      12,    83,    51,     8,    34,    35,   126,    95,   127,   128,
     129,   130,   131,   132,   133,   134,    52,   154,    42,    43,
      44,    45,    46,   100,    47,    53,   156,   157,   158,   159,
      62,    24,    94
  };

  const unsigned char
   Parser ::yytable_[] =
  {
      48,    15,    16,    84,   136,    70,    48,    49,    86,    36,
      67,    10,    90,    50,    82,    92,    71,    72,    73,   174,
     107,    37,    38,   111,    25,    26,   108,    39,   183,   112,
      40,    41,    48,    22,    21,    87,    22,    54,    48,    85,
     185,    48,    14,    99,   101,     9,    97,    32,    28,    79,
      80,    23,    55,    54,    22,   102,   103,   104,    33,   148,
     140,    36,   114,   141,   135,   110,    32,    13,    63,    23,
      75,    18,   136,    37,    38,    27,    68,    58,    69,    39,
      56,   136,    40,    41,   143,   151,     1,     2,     3,    48,
     149,   124,   125,   136,   164,   165,   166,   167,    76,    77,
      78,    65,     1,   116,    66,   117,   152,   118,   119,   120,
     121,   122,    74,    36,    81,    36,    75,    66,   123,    50,
     162,    93,   155,   155,    32,    37,    38,    37,    38,    30,
      31,    39,   135,    39,    40,    41,    40,    41,    68,    98,
      88,   135,   175,   176,   177,   178,   155,   155,   155,   155,
     168,   169,   117,   135,   118,   119,   120,   121,    36,   109,
      36,   115,    60,    89,    66,   137,   139,   138,   105,   106,
      37,    38,    37,    38,   179,   180,    39,   142,    39,    40,
      41,    40,    41,    36,   144,    36,   145,    60,   113,   146,
     147,   150,   153,   161,   170,    37,    38,    37,    38,    36,
     171,    39,   163,    39,    40,    41,    40,    41,   172,   173,
     184,    37,    38,    64,    57,    17,    59,    39,    96,   181,
      40,    41,   160,   182,    29
  };

  const unsigned char
   Parser ::yycheck_[] =
  {
      22,     5,     5,    50,    95,    36,    28,    22,    55,    14,
      33,    36,    60,    18,    19,    63,    37,    38,    39,   163,
      13,    26,    27,    13,    12,    13,    19,    32,   172,    19,
      35,    36,    54,    16,    14,    58,    16,    16,    60,    54,
     184,    63,     0,    74,    75,     4,    69,     4,    31,    26,
      27,    31,    31,    16,    16,    76,    77,    78,    15,    12,
     107,    14,    93,   111,    95,    88,     4,    36,    31,    31,
      16,    36,   163,    26,    27,    14,    13,    15,    15,    32,
      36,   172,    35,    36,   115,    31,     3,     4,     5,   111,
     121,    95,    95,   184,    20,    21,    22,    23,    28,    29,
      30,    36,     3,     4,    18,     6,   137,     8,     9,    10,
      11,    12,    14,    14,    17,    14,    16,    18,    19,    18,
     151,    16,   144,   145,     4,    26,    27,    26,    27,    12,
      13,    32,   163,    32,    35,    36,    35,    36,    13,    15,
      15,   172,   164,   165,   166,   167,   168,   169,   170,   171,
      24,    25,     6,   184,     8,     9,    10,    11,    14,    17,
      14,    16,    18,    19,    18,    13,    17,    15,    79,    80,
      26,    27,    26,    27,   168,   169,    32,    17,    32,    35,
      36,    35,    36,    14,    14,    14,    14,    18,    17,    12,
      12,    12,    17,    12,    33,    26,    27,    26,    27,    14,
      34,    32,    15,    32,    35,    36,    35,    36,    15,    12,
       7,    26,    27,    31,    26,     5,    27,    32,    68,   170,
      35,    36,   145,   171,    18
  };

  const unsigned char
   Parser ::yystos_[] =
  {
       0,     3,     4,     5,    42,    43,    44,    50,    54,     4,
      36,    49,    51,    36,     0,    44,    50,    54,    36,    45,
      46,    14,    16,    31,    82,    12,    13,    14,    31,    82,
      12,    13,     4,    15,    55,    56,    14,    26,    27,    32,
      35,    36,    69,    70,    71,    72,    73,    75,    76,    81,
      18,    53,    67,    76,    16,    31,    36,    51,    15,    55,
      18,    47,    81,    31,    46,    36,    18,    57,    13,    15,
      67,    72,    72,    72,    14,    16,    28,    29,    30,    26,
      27,    17,    19,    52,    53,    81,    53,    57,    15,    19,
      47,    48,    47,    16,    83,    58,    56,    57,    15,    67,
      74,    67,    72,    72,    72,    75,    75,    13,    19,    17,
      57,    13,    19,    17,    67,    16,     4,     6,     8,     9,
      10,    11,    12,    19,    44,    50,    57,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    69,    13,    15,    17,
      53,    47,    17,    67,    14,    14,    12,    12,    12,    67,
      12,    31,    67,    17,    68,    76,    77,    78,    79,    80,
      68,    12,    67,    15,    20,    21,    22,    23,    24,    25,
      33,    34,    15,    12,    60,    76,    76,    76,    76,    77,
      77,    78,    79,    60,     7,    60
  };

  const unsigned char
   Parser ::yyr1_[] =
  {
       0,    41,    42,    43,    43,    43,    43,    43,    43,    43,
      44,    45,    45,    46,    46,    47,    47,    47,    48,    48,
      49,    49,    50,    51,    51,    51,    51,    52,    52,    53,
      53,    53,    54,    54,    54,    54,    55,    55,    56,    56,
      57,    58,    58,    58,    59,    59,    59,    60,    60,    60,
      60,    60,    60,    60,    60,    61,    62,    63,    63,    64,
      64,    65,    66,    67,    68,    69,    69,    70,    70,    70,
      71,    72,    72,    72,    72,    72,    73,    74,    74,    74,
      75,    75,    75,    75,    76,    76,    76,    77,    77,    77,
      77,    77,    78,    78,    78,    79,    79,    80,    80,    81,
      82,    82,    83,    83,    83
  };

  const unsigned char
   Parser ::yyr2_[] =
  {
       0,     2,     1,     0,     1,     1,     1,     2,     2,     2,
       4,     1,     3,     3,     4,     1,     2,     3,     1,     3,
       1,     3,     3,     1,     3,     2,     4,     1,     3,     1,
       2,     3,     5,     6,     5,     6,     1,     3,     2,     3,
       3,     0,     2,     2,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     3,     5,
       7,     5,     4,     1,     1,     1,     4,     1,     1,     3,
       1,     1,     1,     2,     2,     2,     4,     0,     1,     3,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     4,     2,     3,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "END", "error", "$undefined", "CONST", "INT", "VOID", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "RETURN", "SEMI", "COMMA", "L_PAREN",
  "R_PAREN", "L_BRACKET", "R_BRACKET", "L_BRACE", "R_BRACE", "GT", "LT",
  "GTE", "LTE", "EQ", "NEQ", "ADD", "SUB", "MUL", "DIV", "MOD", "ASSIGN",
  "NOT", "AND", "OR", "INTCONST", "IDENT", "EOL", "ABS", "\"|\"", "NEG",
  "$accept", "st", "compUnit", "constDecl", "constDefList", "constDef",
  "constInitVal", "constInitList", "varDefList", "varDecl", "varDef",
  "initList", "initVal", "funcDef", "funcFParams", "funcFParam", "block",
  "blockItems", "blockItem", "stmt", "breakStmt", "continueStmt",
  "returnStmt", "selectStmt", "iterationStmt", "assignStmt", "exp", "cond",
  "lVal", "primaryExp", "number", "unaryExp", "funCall", "funcRParams",
  "mulExp", "addExp", "relExp", "eqExp", "landExp", "lorExp", "constExp",
  "const_bracketList", "func_bracketList", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   Parser ::yyrline_[] =
  {
       0,   183,   183,   195,   196,   197,   198,   199,   200,   201,
     205,   208,   209,   212,   213,   216,   217,   218,   221,   222,
     225,   226,   229,   232,   233,   234,   235,   238,   239,   242,
     243,   244,   247,   248,   249,   250,   253,   254,   257,   258,
     261,   264,   265,   266,   270,   271,   272,   275,   276,   277,
     278,   279,   280,   281,   282,   285,   288,   291,   292,   295,
     296,   299,   302,   305,   308,   311,   312,   316,   317,   318,
     321,   324,   325,   326,   327,   328,   331,   334,   335,   336,
     339,   340,   341,   342,   345,   346,   347,   350,   351,   352,
     353,   354,   357,   358,   359,   362,   363,   366,   367,   370,
     373,   374,   377,   378,   379
  };

  // Print the state stack on the debug stream.
  void
   Parser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   Parser ::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 5 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:1167
} // Marker
#line 2087 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.cpp" // lalr1.cc:1167
#line 382 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:1168


void Marker::Parser::error(const Marker::location& location,const std::string& message){
  std::cout<<"msg:"<<message
           <<", error happened at: "<<location<<std::endl;
}

