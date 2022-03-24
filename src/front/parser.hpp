// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file /home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.hpp
 ** Define the Marker::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_HOME_WXZ_SLC_SYS_Y_LANGUAGE_COMPILER_SRC_FRONT_FLEX_BISON_PARSER_HPP_INCLUDED
# define YY_YY_HOME_WXZ_SLC_SYS_Y_LANGUAGE_COMPILER_SRC_FRONT_FLEX_BISON_PARSER_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 13 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:377

	/*requires中的内容会放在YYLTYPE与YYSTPYPE定义前*/
	#include <iostream>
	#include <string>
	#include <vector>
	#include <stdint.h>
  	#include <cmath>

	#include "Ast.hpp"
	#include "Type.hpp"

  	using namespace std;

  	namespace Marker { /*避免包含头文件时冲突*/
		class Scanner;
		class Driver;
  	}

#line 63 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.hpp" // lalr1.cc:377

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 5 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:377
namespace Marker {
#line 140 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.hpp" // lalr1.cc:377



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class  Parser 
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // assignStmt
      char dummy1[sizeof(ast_AssignStmt*)];

      // block
      char dummy2[sizeof(ast_Block*)];

      // blockItem
      char dummy3[sizeof(ast_BlockItem*)];

      // blockItems
      char dummy4[sizeof(ast_BlockItems*)];

      // func_bracketList
      char dummy5[sizeof(ast_BracketList*)];

      // breakStmt
      char dummy6[sizeof(ast_BreakStmt*)];

      // st
      // compUnit
      char dummy7[sizeof(ast_CompUnit*)];

      // const_bracketList
      char dummy8[sizeof(ast_ConstBracketList*)];

      // constDecl
      char dummy9[sizeof(ast_ConstDecl*)];

      // constDef
      char dummy10[sizeof(ast_ConstDef*)];

      // constDefList
      char dummy11[sizeof(ast_ConstDefList*)];

      // constInitList
      char dummy12[sizeof(ast_ConstInitList*)];

      // constInitVal
      char dummy13[sizeof(ast_ConstInitVal*)];

      // continueStmt
      char dummy14[sizeof(ast_ContinueStmt*)];

      // exp
      // cond
      // primaryExp
      // unaryExp
      // mulExp
      // addExp
      // relExp
      // eqExp
      // landExp
      // lorExp
      // constExp
      char dummy15[sizeof(ast_Expression*)];

      // funCall
      char dummy16[sizeof(ast_FunCall*)];

      // funcDef
      char dummy17[sizeof(ast_FuncDef*)];

      // funcFParam
      char dummy18[sizeof(ast_FuncFParam*)];

      // funcFParams
      char dummy19[sizeof(ast_FuncFParams*)];

      // funcRParams
      char dummy20[sizeof(ast_FuncRParams*)];

      // initList
      char dummy21[sizeof(ast_InitList*)];

      // initVal
      char dummy22[sizeof(ast_InitVal*)];

      // iterationStmt
      char dummy23[sizeof(ast_IterationStmt*)];

      // lVal
      char dummy24[sizeof(ast_LVal*)];

      // number
      char dummy25[sizeof(ast_Number*)];

      // returnStmt
      char dummy26[sizeof(ast_ReturnStmt*)];

      // selectStmt
      char dummy27[sizeof(ast_SelectStmt*)];

      // stmt
      char dummy28[sizeof(ast_Stmt*)];

      // varDecl
      char dummy29[sizeof(ast_VarDecl*)];

      // varDef
      char dummy30[sizeof(ast_VarDef*)];

      // varDefList
      char dummy31[sizeof(ast_VarDefList*)];

      // INTCONST
      char dummy32[sizeof(int)];

      // IDENT
      char dummy33[sizeof(string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOKEN_END = 0,
        TOKEN_CONST = 258,
        TOKEN_INT = 259,
        TOKEN_VOID = 260,
        TOKEN_IF = 261,
        TOKEN_ELSE = 262,
        TOKEN_WHILE = 263,
        TOKEN_BREAK = 264,
        TOKEN_CONTINUE = 265,
        TOKEN_RETURN = 266,
        TOKEN_SEMI = 267,
        TOKEN_COMMA = 268,
        TOKEN_L_PAREN = 269,
        TOKEN_R_PAREN = 270,
        TOKEN_L_BRACKET = 271,
        TOKEN_R_BRACKET = 272,
        TOKEN_L_BRACE = 273,
        TOKEN_R_BRACE = 274,
        TOKEN_GT = 275,
        TOKEN_LT = 276,
        TOKEN_GTE = 277,
        TOKEN_LTE = 278,
        TOKEN_EQ = 279,
        TOKEN_NEQ = 280,
        TOKEN_ADD = 281,
        TOKEN_SUB = 282,
        TOKEN_MUL = 283,
        TOKEN_DIV = 284,
        TOKEN_MOD = 285,
        TOKEN_ASSIGN = 286,
        TOKEN_NOT = 287,
        TOKEN_AND = 288,
        TOKEN_OR = 289,
        TOKEN_INTCONST = 290,
        TOKEN_IDENT = 291,
        TOKEN_EOL = 292,
        TOKEN_ABS = 293,
        TOKEN_NEG = 295
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_AssignStmt* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_Block* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_BlockItem* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_BlockItems* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_BracketList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_BreakStmt* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_CompUnit* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_ConstBracketList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_ConstDecl* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_ConstDef* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_ConstDefList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_ConstInitList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_ConstInitVal* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_ContinueStmt* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_Expression* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_FunCall* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_FuncDef* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_FuncFParam* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_FuncFParams* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_FuncRParams* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_InitList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_InitVal* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_IterationStmt* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_LVal* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_Number* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_ReturnStmt* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_SelectStmt* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_Stmt* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_VarDecl* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_VarDef* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ast_VarDefList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const string v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_CONST (const location_type& l);

    static inline
    symbol_type
    make_INT (const location_type& l);

    static inline
    symbol_type
    make_VOID (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_WHILE (const location_type& l);

    static inline
    symbol_type
    make_BREAK (const location_type& l);

    static inline
    symbol_type
    make_CONTINUE (const location_type& l);

    static inline
    symbol_type
    make_RETURN (const location_type& l);

    static inline
    symbol_type
    make_SEMI (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_L_PAREN (const location_type& l);

    static inline
    symbol_type
    make_R_PAREN (const location_type& l);

    static inline
    symbol_type
    make_L_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_R_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_L_BRACE (const location_type& l);

    static inline
    symbol_type
    make_R_BRACE (const location_type& l);

    static inline
    symbol_type
    make_GT (const location_type& l);

    static inline
    symbol_type
    make_LT (const location_type& l);

    static inline
    symbol_type
    make_GTE (const location_type& l);

    static inline
    symbol_type
    make_LTE (const location_type& l);

    static inline
    symbol_type
    make_EQ (const location_type& l);

    static inline
    symbol_type
    make_NEQ (const location_type& l);

    static inline
    symbol_type
    make_ADD (const location_type& l);

    static inline
    symbol_type
    make_SUB (const location_type& l);

    static inline
    symbol_type
    make_MUL (const location_type& l);

    static inline
    symbol_type
    make_DIV (const location_type& l);

    static inline
    symbol_type
    make_MOD (const location_type& l);

    static inline
    symbol_type
    make_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_NOT (const location_type& l);

    static inline
    symbol_type
    make_AND (const location_type& l);

    static inline
    symbol_type
    make_OR (const location_type& l);

    static inline
    symbol_type
    make_INTCONST (const int& v, const location_type& l);

    static inline
    symbol_type
    make_IDENT (const string& v, const location_type& l);

    static inline
    symbol_type
    make_EOL (const location_type& l);

    static inline
    symbol_type
    make_ABS (const location_type& l);

    static inline
    symbol_type
    make_NEG (const location_type& l);


    /// Build a parser object.
     Parser  (Marker::Scanner& scanner_yyarg, Marker::Driver& driver_yyarg);
    virtual ~ Parser  ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
     Parser  (const  Parser &);
     Parser & operator= (const  Parser &);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short int yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const unsigned char yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 224,     ///< Last index in yytable_.
      yynnts_ = 43,  ///< Number of nonterminal symbols.
      yyfinal_ = 14, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 41  ///< Number of tokens.
    };


    // User arguments.
    Marker::Scanner& scanner;
    Marker::Driver& driver;
  };

  // Symbol number corresponding to token number t.
  inline
   Parser ::token_number_type
   Parser ::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
    };
    const unsigned int user_token_number_max_ = 295;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
   Parser ::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 66: // assignStmt
        value.copy< ast_AssignStmt* > (other.value);
        break;

      case 57: // block
        value.copy< ast_Block* > (other.value);
        break;

      case 59: // blockItem
        value.copy< ast_BlockItem* > (other.value);
        break;

      case 58: // blockItems
        value.copy< ast_BlockItems* > (other.value);
        break;

      case 83: // func_bracketList
        value.copy< ast_BracketList* > (other.value);
        break;

      case 61: // breakStmt
        value.copy< ast_BreakStmt* > (other.value);
        break;

      case 42: // st
      case 43: // compUnit
        value.copy< ast_CompUnit* > (other.value);
        break;

      case 82: // const_bracketList
        value.copy< ast_ConstBracketList* > (other.value);
        break;

      case 44: // constDecl
        value.copy< ast_ConstDecl* > (other.value);
        break;

      case 46: // constDef
        value.copy< ast_ConstDef* > (other.value);
        break;

      case 45: // constDefList
        value.copy< ast_ConstDefList* > (other.value);
        break;

      case 48: // constInitList
        value.copy< ast_ConstInitList* > (other.value);
        break;

      case 47: // constInitVal
        value.copy< ast_ConstInitVal* > (other.value);
        break;

      case 62: // continueStmt
        value.copy< ast_ContinueStmt* > (other.value);
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
        value.copy< ast_Expression* > (other.value);
        break;

      case 73: // funCall
        value.copy< ast_FunCall* > (other.value);
        break;

      case 54: // funcDef
        value.copy< ast_FuncDef* > (other.value);
        break;

      case 56: // funcFParam
        value.copy< ast_FuncFParam* > (other.value);
        break;

      case 55: // funcFParams
        value.copy< ast_FuncFParams* > (other.value);
        break;

      case 74: // funcRParams
        value.copy< ast_FuncRParams* > (other.value);
        break;

      case 52: // initList
        value.copy< ast_InitList* > (other.value);
        break;

      case 53: // initVal
        value.copy< ast_InitVal* > (other.value);
        break;

      case 65: // iterationStmt
        value.copy< ast_IterationStmt* > (other.value);
        break;

      case 69: // lVal
        value.copy< ast_LVal* > (other.value);
        break;

      case 71: // number
        value.copy< ast_Number* > (other.value);
        break;

      case 63: // returnStmt
        value.copy< ast_ReturnStmt* > (other.value);
        break;

      case 64: // selectStmt
        value.copy< ast_SelectStmt* > (other.value);
        break;

      case 60: // stmt
        value.copy< ast_Stmt* > (other.value);
        break;

      case 50: // varDecl
        value.copy< ast_VarDecl* > (other.value);
        break;

      case 51: // varDef
        value.copy< ast_VarDef* > (other.value);
        break;

      case 49: // varDefList
        value.copy< ast_VarDefList* > (other.value);
        break;

      case 35: // INTCONST
        value.copy< int > (other.value);
        break;

      case 36: // IDENT
        value.copy< string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 66: // assignStmt
        value.copy< ast_AssignStmt* > (v);
        break;

      case 57: // block
        value.copy< ast_Block* > (v);
        break;

      case 59: // blockItem
        value.copy< ast_BlockItem* > (v);
        break;

      case 58: // blockItems
        value.copy< ast_BlockItems* > (v);
        break;

      case 83: // func_bracketList
        value.copy< ast_BracketList* > (v);
        break;

      case 61: // breakStmt
        value.copy< ast_BreakStmt* > (v);
        break;

      case 42: // st
      case 43: // compUnit
        value.copy< ast_CompUnit* > (v);
        break;

      case 82: // const_bracketList
        value.copy< ast_ConstBracketList* > (v);
        break;

      case 44: // constDecl
        value.copy< ast_ConstDecl* > (v);
        break;

      case 46: // constDef
        value.copy< ast_ConstDef* > (v);
        break;

      case 45: // constDefList
        value.copy< ast_ConstDefList* > (v);
        break;

      case 48: // constInitList
        value.copy< ast_ConstInitList* > (v);
        break;

      case 47: // constInitVal
        value.copy< ast_ConstInitVal* > (v);
        break;

      case 62: // continueStmt
        value.copy< ast_ContinueStmt* > (v);
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
        value.copy< ast_Expression* > (v);
        break;

      case 73: // funCall
        value.copy< ast_FunCall* > (v);
        break;

      case 54: // funcDef
        value.copy< ast_FuncDef* > (v);
        break;

      case 56: // funcFParam
        value.copy< ast_FuncFParam* > (v);
        break;

      case 55: // funcFParams
        value.copy< ast_FuncFParams* > (v);
        break;

      case 74: // funcRParams
        value.copy< ast_FuncRParams* > (v);
        break;

      case 52: // initList
        value.copy< ast_InitList* > (v);
        break;

      case 53: // initVal
        value.copy< ast_InitVal* > (v);
        break;

      case 65: // iterationStmt
        value.copy< ast_IterationStmt* > (v);
        break;

      case 69: // lVal
        value.copy< ast_LVal* > (v);
        break;

      case 71: // number
        value.copy< ast_Number* > (v);
        break;

      case 63: // returnStmt
        value.copy< ast_ReturnStmt* > (v);
        break;

      case 64: // selectStmt
        value.copy< ast_SelectStmt* > (v);
        break;

      case 60: // stmt
        value.copy< ast_Stmt* > (v);
        break;

      case 50: // varDecl
        value.copy< ast_VarDecl* > (v);
        break;

      case 51: // varDef
        value.copy< ast_VarDef* > (v);
        break;

      case 49: // varDefList
        value.copy< ast_VarDefList* > (v);
        break;

      case 35: // INTCONST
        value.copy< int > (v);
        break;

      case 36: // IDENT
        value.copy< string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_AssignStmt* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_Block* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_BlockItem* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_BlockItems* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_BracketList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_BreakStmt* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_CompUnit* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_ConstBracketList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_ConstDecl* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_ConstDef* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_ConstDefList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_ConstInitList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_ConstInitVal* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_ContinueStmt* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_Expression* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_FunCall* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_FuncDef* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_FuncFParam* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_FuncFParams* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_FuncRParams* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_InitList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_InitVal* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_IterationStmt* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_LVal* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_Number* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_ReturnStmt* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_SelectStmt* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_Stmt* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_VarDecl* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_VarDef* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ast_VarDefList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
   Parser ::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 66: // assignStmt
        value.template destroy< ast_AssignStmt* > ();
        break;

      case 57: // block
        value.template destroy< ast_Block* > ();
        break;

      case 59: // blockItem
        value.template destroy< ast_BlockItem* > ();
        break;

      case 58: // blockItems
        value.template destroy< ast_BlockItems* > ();
        break;

      case 83: // func_bracketList
        value.template destroy< ast_BracketList* > ();
        break;

      case 61: // breakStmt
        value.template destroy< ast_BreakStmt* > ();
        break;

      case 42: // st
      case 43: // compUnit
        value.template destroy< ast_CompUnit* > ();
        break;

      case 82: // const_bracketList
        value.template destroy< ast_ConstBracketList* > ();
        break;

      case 44: // constDecl
        value.template destroy< ast_ConstDecl* > ();
        break;

      case 46: // constDef
        value.template destroy< ast_ConstDef* > ();
        break;

      case 45: // constDefList
        value.template destroy< ast_ConstDefList* > ();
        break;

      case 48: // constInitList
        value.template destroy< ast_ConstInitList* > ();
        break;

      case 47: // constInitVal
        value.template destroy< ast_ConstInitVal* > ();
        break;

      case 62: // continueStmt
        value.template destroy< ast_ContinueStmt* > ();
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
        value.template destroy< ast_Expression* > ();
        break;

      case 73: // funCall
        value.template destroy< ast_FunCall* > ();
        break;

      case 54: // funcDef
        value.template destroy< ast_FuncDef* > ();
        break;

      case 56: // funcFParam
        value.template destroy< ast_FuncFParam* > ();
        break;

      case 55: // funcFParams
        value.template destroy< ast_FuncFParams* > ();
        break;

      case 74: // funcRParams
        value.template destroy< ast_FuncRParams* > ();
        break;

      case 52: // initList
        value.template destroy< ast_InitList* > ();
        break;

      case 53: // initVal
        value.template destroy< ast_InitVal* > ();
        break;

      case 65: // iterationStmt
        value.template destroy< ast_IterationStmt* > ();
        break;

      case 69: // lVal
        value.template destroy< ast_LVal* > ();
        break;

      case 71: // number
        value.template destroy< ast_Number* > ();
        break;

      case 63: // returnStmt
        value.template destroy< ast_ReturnStmt* > ();
        break;

      case 64: // selectStmt
        value.template destroy< ast_SelectStmt* > ();
        break;

      case 60: // stmt
        value.template destroy< ast_Stmt* > ();
        break;

      case 50: // varDecl
        value.template destroy< ast_VarDecl* > ();
        break;

      case 51: // varDef
        value.template destroy< ast_VarDef* > ();
        break;

      case 49: // varDefList
        value.template destroy< ast_VarDefList* > ();
        break;

      case 35: // INTCONST
        value.template destroy< int > ();
        break;

      case 36: // IDENT
        value.template destroy< string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
   Parser ::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
   Parser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 66: // assignStmt
        value.move< ast_AssignStmt* > (s.value);
        break;

      case 57: // block
        value.move< ast_Block* > (s.value);
        break;

      case 59: // blockItem
        value.move< ast_BlockItem* > (s.value);
        break;

      case 58: // blockItems
        value.move< ast_BlockItems* > (s.value);
        break;

      case 83: // func_bracketList
        value.move< ast_BracketList* > (s.value);
        break;

      case 61: // breakStmt
        value.move< ast_BreakStmt* > (s.value);
        break;

      case 42: // st
      case 43: // compUnit
        value.move< ast_CompUnit* > (s.value);
        break;

      case 82: // const_bracketList
        value.move< ast_ConstBracketList* > (s.value);
        break;

      case 44: // constDecl
        value.move< ast_ConstDecl* > (s.value);
        break;

      case 46: // constDef
        value.move< ast_ConstDef* > (s.value);
        break;

      case 45: // constDefList
        value.move< ast_ConstDefList* > (s.value);
        break;

      case 48: // constInitList
        value.move< ast_ConstInitList* > (s.value);
        break;

      case 47: // constInitVal
        value.move< ast_ConstInitVal* > (s.value);
        break;

      case 62: // continueStmt
        value.move< ast_ContinueStmt* > (s.value);
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
        value.move< ast_Expression* > (s.value);
        break;

      case 73: // funCall
        value.move< ast_FunCall* > (s.value);
        break;

      case 54: // funcDef
        value.move< ast_FuncDef* > (s.value);
        break;

      case 56: // funcFParam
        value.move< ast_FuncFParam* > (s.value);
        break;

      case 55: // funcFParams
        value.move< ast_FuncFParams* > (s.value);
        break;

      case 74: // funcRParams
        value.move< ast_FuncRParams* > (s.value);
        break;

      case 52: // initList
        value.move< ast_InitList* > (s.value);
        break;

      case 53: // initVal
        value.move< ast_InitVal* > (s.value);
        break;

      case 65: // iterationStmt
        value.move< ast_IterationStmt* > (s.value);
        break;

      case 69: // lVal
        value.move< ast_LVal* > (s.value);
        break;

      case 71: // number
        value.move< ast_Number* > (s.value);
        break;

      case 63: // returnStmt
        value.move< ast_ReturnStmt* > (s.value);
        break;

      case 64: // selectStmt
        value.move< ast_SelectStmt* > (s.value);
        break;

      case 60: // stmt
        value.move< ast_Stmt* > (s.value);
        break;

      case 50: // varDecl
        value.move< ast_VarDecl* > (s.value);
        break;

      case 51: // varDef
        value.move< ast_VarDef* > (s.value);
        break;

      case 49: // varDefList
        value.move< ast_VarDefList* > (s.value);
        break;

      case 35: // INTCONST
        value.move< int > (s.value);
        break;

      case 36: // IDENT
        value.move< string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
   Parser ::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
   Parser ::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
   Parser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
   Parser ::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
   Parser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
   Parser ::by_type::type_get () const
  {
    return type;
  }

  inline
   Parser ::token_type
   Parser ::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
   Parser ::symbol_type
   Parser ::make_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_END, l);
  }

   Parser ::symbol_type
   Parser ::make_CONST (const location_type& l)
  {
    return symbol_type (token::TOKEN_CONST, l);
  }

   Parser ::symbol_type
   Parser ::make_INT (const location_type& l)
  {
    return symbol_type (token::TOKEN_INT, l);
  }

   Parser ::symbol_type
   Parser ::make_VOID (const location_type& l)
  {
    return symbol_type (token::TOKEN_VOID, l);
  }

   Parser ::symbol_type
   Parser ::make_IF (const location_type& l)
  {
    return symbol_type (token::TOKEN_IF, l);
  }

   Parser ::symbol_type
   Parser ::make_ELSE (const location_type& l)
  {
    return symbol_type (token::TOKEN_ELSE, l);
  }

   Parser ::symbol_type
   Parser ::make_WHILE (const location_type& l)
  {
    return symbol_type (token::TOKEN_WHILE, l);
  }

   Parser ::symbol_type
   Parser ::make_BREAK (const location_type& l)
  {
    return symbol_type (token::TOKEN_BREAK, l);
  }

   Parser ::symbol_type
   Parser ::make_CONTINUE (const location_type& l)
  {
    return symbol_type (token::TOKEN_CONTINUE, l);
  }

   Parser ::symbol_type
   Parser ::make_RETURN (const location_type& l)
  {
    return symbol_type (token::TOKEN_RETURN, l);
  }

   Parser ::symbol_type
   Parser ::make_SEMI (const location_type& l)
  {
    return symbol_type (token::TOKEN_SEMI, l);
  }

   Parser ::symbol_type
   Parser ::make_COMMA (const location_type& l)
  {
    return symbol_type (token::TOKEN_COMMA, l);
  }

   Parser ::symbol_type
   Parser ::make_L_PAREN (const location_type& l)
  {
    return symbol_type (token::TOKEN_L_PAREN, l);
  }

   Parser ::symbol_type
   Parser ::make_R_PAREN (const location_type& l)
  {
    return symbol_type (token::TOKEN_R_PAREN, l);
  }

   Parser ::symbol_type
   Parser ::make_L_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOKEN_L_BRACKET, l);
  }

   Parser ::symbol_type
   Parser ::make_R_BRACKET (const location_type& l)
  {
    return symbol_type (token::TOKEN_R_BRACKET, l);
  }

   Parser ::symbol_type
   Parser ::make_L_BRACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_L_BRACE, l);
  }

   Parser ::symbol_type
   Parser ::make_R_BRACE (const location_type& l)
  {
    return symbol_type (token::TOKEN_R_BRACE, l);
  }

   Parser ::symbol_type
   Parser ::make_GT (const location_type& l)
  {
    return symbol_type (token::TOKEN_GT, l);
  }

   Parser ::symbol_type
   Parser ::make_LT (const location_type& l)
  {
    return symbol_type (token::TOKEN_LT, l);
  }

   Parser ::symbol_type
   Parser ::make_GTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_GTE, l);
  }

   Parser ::symbol_type
   Parser ::make_LTE (const location_type& l)
  {
    return symbol_type (token::TOKEN_LTE, l);
  }

   Parser ::symbol_type
   Parser ::make_EQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_EQ, l);
  }

   Parser ::symbol_type
   Parser ::make_NEQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_NEQ, l);
  }

   Parser ::symbol_type
   Parser ::make_ADD (const location_type& l)
  {
    return symbol_type (token::TOKEN_ADD, l);
  }

   Parser ::symbol_type
   Parser ::make_SUB (const location_type& l)
  {
    return symbol_type (token::TOKEN_SUB, l);
  }

   Parser ::symbol_type
   Parser ::make_MUL (const location_type& l)
  {
    return symbol_type (token::TOKEN_MUL, l);
  }

   Parser ::symbol_type
   Parser ::make_DIV (const location_type& l)
  {
    return symbol_type (token::TOKEN_DIV, l);
  }

   Parser ::symbol_type
   Parser ::make_MOD (const location_type& l)
  {
    return symbol_type (token::TOKEN_MOD, l);
  }

   Parser ::symbol_type
   Parser ::make_ASSIGN (const location_type& l)
  {
    return symbol_type (token::TOKEN_ASSIGN, l);
  }

   Parser ::symbol_type
   Parser ::make_NOT (const location_type& l)
  {
    return symbol_type (token::TOKEN_NOT, l);
  }

   Parser ::symbol_type
   Parser ::make_AND (const location_type& l)
  {
    return symbol_type (token::TOKEN_AND, l);
  }

   Parser ::symbol_type
   Parser ::make_OR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OR, l);
  }

   Parser ::symbol_type
   Parser ::make_INTCONST (const int& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_INTCONST, v, l);
  }

   Parser ::symbol_type
   Parser ::make_IDENT (const string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_IDENT, v, l);
  }

   Parser ::symbol_type
   Parser ::make_EOL (const location_type& l)
  {
    return symbol_type (token::TOKEN_EOL, l);
  }

   Parser ::symbol_type
   Parser ::make_ABS (const location_type& l)
  {
    return symbol_type (token::TOKEN_ABS, l);
  }

   Parser ::symbol_type
   Parser ::make_NEG (const location_type& l)
  {
    return symbol_type (token::TOKEN_NEG, l);
  }


#line 5 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/bison.y" // lalr1.cc:377
} // Marker
#line 2269 "/home/wxz/桌面/slc_-sys-y_-language_-compiler/src/front/flex_bison/../parser.hpp" // lalr1.cc:377




#endif // !YY_YY_HOME_WXZ_SLC_SYS_Y_LANGUAGE_COMPILER_SRC_FRONT_FLEX_BISON_PARSER_HPP_INCLUDED
