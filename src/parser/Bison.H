/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_MFPG_DSL_BISON_H_INCLUDED
# define YY_MFPG_DSL_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int mfpg_dsl_debug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    _ERROR_ = 258,                 /* _ERROR_  */
    _BANGEQ = 259,                 /* _BANGEQ  */
    _DAMP = 260,                   /* _DAMP  */
    _LPAREN = 261,                 /* _LPAREN  */
    _RPAREN = 262,                 /* _RPAREN  */
    _STAR = 263,                   /* _STAR  */
    _PLUS = 264,                   /* _PLUS  */
    _COMMA = 265,                  /* _COMMA  */
    _MINUS = 266,                  /* _MINUS  */
    _DMINUS = 267,                 /* _DMINUS  */
    _RARROW = 268,                 /* _RARROW  */
    _COLON = 269,                  /* _COLON  */
    _DCOLON = 270,                 /* _DCOLON  */
    _SEMI = 271,                   /* _SEMI  */
    _LT = 272,                     /* _LT  */
    _LDARROW = 273,                /* _LDARROW  */
    _EQ = 274,                     /* _EQ  */
    _DEQ = 275,                    /* _DEQ  */
    _GT = 276,                     /* _GT  */
    _GTEQ = 277,                   /* _GTEQ  */
    _KW_A = 278,                   /* _KW_A  */
    _KW_As = 279,                  /* _KW_As  */
    _KW_B = 280,                   /* _KW_B  */
    _KW_C = 281,                   /* _KW_C  */
    _KW_Cs = 282,                  /* _KW_Cs  */
    _KW_D = 283,                   /* _KW_D  */
    _KW_Ds = 284,                  /* _KW_Ds  */
    _KW_E = 285,                   /* _KW_E  */
    _KW_F = 286,                   /* _KW_F  */
    _KW_Fs = 287,                  /* _KW_Fs  */
    _KW_G = 288,                   /* _KW_G  */
    _KW_Gs = 289,                  /* _KW_Gs  */
    _LBRACK = 290,                 /* _LBRACK  */
    _RBRACK = 291,                 /* _RBRACK  */
    _UNDERSCORE = 292,             /* _UNDERSCORE  */
    _KW_b = 293,                   /* _KW_b  */
    _KW_d = 294,                   /* _KW_d  */
    _KW_double = 295,              /* _KW_double  */
    _KW_false = 296,               /* _KW_false  */
    _KW_i = 297,                   /* _KW_i  */
    _KW_int = 298,                 /* _KW_int  */
    _KW_true = 299,                /* _KW_true  */
    _LBRACE = 300,                 /* _LBRACE  */
    _DBAR = 301,                   /* _DBAR  */
    _RBRACE = 302,                 /* _RBRACE  */
    _STRING_ = 303,                /* _STRING_  */
    _INTEGER_ = 304,               /* _INTEGER_  */
    _DOUBLE_ = 305                 /* _DOUBLE_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "mfpg_dsl.y"

  int    _int;
  char   _char;
  double _double;
  char*  _string;
  Input* input_;
  Output* output_;
  AttrDecl* attrdecl_;
  ListAttrDecl* listattrdecl_;
  IStr* istr_;
  ListIStr* lististr_;
  SPos* spos_;
  Note* note_;
  NoteBase* notebase_;
  AttrType* attrtype_;
  Act* act_;
  ActionName* actionname_;
  ListAct* listact_;
  DFun* dfun_;
  CFun* cfun_;
  Attr* attr_;
  CompOp* compop_;
  BoolOp* boolop_;
  Num* num_;
  Exp* exp_;
  Scale* scale_;
  Bool* bool_;

#line 143 "Bison.H"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int mfpg_dsl_parse (yyscan_t scanner, YYSTYPE *result);


#endif /* !YY_MFPG_DSL_BISON_H_INCLUDED  */
