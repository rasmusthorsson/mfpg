/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         mfpg_dsl_parse
#define yylex           mfpg_dsl_lex
#define yyerror         mfpg_dsl_error
#define yydebug         mfpg_dsl_debug
#define yynerrs         mfpg_dsl_nerrs

/* First part of user prologue.  */
#line 20 "mfpg_dsl.y"

/* Begin C preamble code */

#include <algorithm> /* for std::reverse */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Absyn.H"

#define YYMAXDEPTH 10000000

/* The type yyscan_t is defined by flex, but we need it in the parser already. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE mfpg_dsl__scan_string(const char *str, yyscan_t scanner);
extern void mfpg_dsl__delete_buffer(YY_BUFFER_STATE buf, yyscan_t scanner);

extern void mfpg_dsl_lex_destroy(yyscan_t scanner);
extern char* mfpg_dsl_get_text(yyscan_t scanner);

extern yyscan_t mfpg_dsl__initialize_lexer(FILE * inp);

/* End C preamble code */

#line 105 "Parser.C"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "Bison.H"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL__ERROR_ = 3,                    /* _ERROR_  */
  YYSYMBOL__BANGEQ = 4,                    /* _BANGEQ  */
  YYSYMBOL__DAMP = 5,                      /* _DAMP  */
  YYSYMBOL__LPAREN = 6,                    /* _LPAREN  */
  YYSYMBOL__RPAREN = 7,                    /* _RPAREN  */
  YYSYMBOL__STAR = 8,                      /* _STAR  */
  YYSYMBOL__PLUS = 9,                      /* _PLUS  */
  YYSYMBOL__COMMA = 10,                    /* _COMMA  */
  YYSYMBOL__MINUS = 11,                    /* _MINUS  */
  YYSYMBOL__DMINUS = 12,                   /* _DMINUS  */
  YYSYMBOL__RARROW = 13,                   /* _RARROW  */
  YYSYMBOL__COLON = 14,                    /* _COLON  */
  YYSYMBOL__DCOLON = 15,                   /* _DCOLON  */
  YYSYMBOL__SEMI = 16,                     /* _SEMI  */
  YYSYMBOL__LT = 17,                       /* _LT  */
  YYSYMBOL__LDARROW = 18,                  /* _LDARROW  */
  YYSYMBOL__EQ = 19,                       /* _EQ  */
  YYSYMBOL__DEQ = 20,                      /* _DEQ  */
  YYSYMBOL__GT = 21,                       /* _GT  */
  YYSYMBOL__GTEQ = 22,                     /* _GTEQ  */
  YYSYMBOL__KW_A = 23,                     /* _KW_A  */
  YYSYMBOL__KW_As = 24,                    /* _KW_As  */
  YYSYMBOL__KW_B = 25,                     /* _KW_B  */
  YYSYMBOL__KW_C = 26,                     /* _KW_C  */
  YYSYMBOL__KW_Cs = 27,                    /* _KW_Cs  */
  YYSYMBOL__KW_D = 28,                     /* _KW_D  */
  YYSYMBOL__KW_Ds = 29,                    /* _KW_Ds  */
  YYSYMBOL__KW_E = 30,                     /* _KW_E  */
  YYSYMBOL__KW_F = 31,                     /* _KW_F  */
  YYSYMBOL__KW_Fs = 32,                    /* _KW_Fs  */
  YYSYMBOL__KW_G = 33,                     /* _KW_G  */
  YYSYMBOL__KW_Gs = 34,                    /* _KW_Gs  */
  YYSYMBOL__LBRACK = 35,                   /* _LBRACK  */
  YYSYMBOL__RBRACK = 36,                   /* _RBRACK  */
  YYSYMBOL__UNDERSCORE = 37,               /* _UNDERSCORE  */
  YYSYMBOL__KW_b = 38,                     /* _KW_b  */
  YYSYMBOL__KW_d = 39,                     /* _KW_d  */
  YYSYMBOL__KW_double = 40,                /* _KW_double  */
  YYSYMBOL__KW_false = 41,                 /* _KW_false  */
  YYSYMBOL__KW_i = 42,                     /* _KW_i  */
  YYSYMBOL__KW_int = 43,                   /* _KW_int  */
  YYSYMBOL__KW_true = 44,                  /* _KW_true  */
  YYSYMBOL__LBRACE = 45,                   /* _LBRACE  */
  YYSYMBOL__DBAR = 46,                     /* _DBAR  */
  YYSYMBOL__RBRACE = 47,                   /* _RBRACE  */
  YYSYMBOL__STRING_ = 48,                  /* _STRING_  */
  YYSYMBOL__INTEGER_ = 49,                 /* _INTEGER_  */
  YYSYMBOL__DOUBLE_ = 50,                  /* _DOUBLE_  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_Input = 52,                     /* Input  */
  YYSYMBOL_Output = 53,                    /* Output  */
  YYSYMBOL_AttrDecl = 54,                  /* AttrDecl  */
  YYSYMBOL_ListAttrDecl = 55,              /* ListAttrDecl  */
  YYSYMBOL_IStr = 56,                      /* IStr  */
  YYSYMBOL_ListIStr = 57,                  /* ListIStr  */
  YYSYMBOL_SPos = 58,                      /* SPos  */
  YYSYMBOL_Note = 59,                      /* Note  */
  YYSYMBOL_NoteBase = 60,                  /* NoteBase  */
  YYSYMBOL_AttrType = 61,                  /* AttrType  */
  YYSYMBOL_Act = 62,                       /* Act  */
  YYSYMBOL_ActionName = 63,                /* ActionName  */
  YYSYMBOL_ListAct = 64,                   /* ListAct  */
  YYSYMBOL_DFun = 65,                      /* DFun  */
  YYSYMBOL_DFun1 = 66,                     /* DFun1  */
  YYSYMBOL_DFun2 = 67,                     /* DFun2  */
  YYSYMBOL_CFun = 68,                      /* CFun  */
  YYSYMBOL_CFun1 = 69,                     /* CFun1  */
  YYSYMBOL_CFun2 = 70,                     /* CFun2  */
  YYSYMBOL_Attr = 71,                      /* Attr  */
  YYSYMBOL_CompOp = 72,                    /* CompOp  */
  YYSYMBOL_BoolOp = 73,                    /* BoolOp  */
  YYSYMBOL_Num = 74,                       /* Num  */
  YYSYMBOL_Exp = 75,                       /* Exp  */
  YYSYMBOL_Scale = 76,                     /* Scale  */
  YYSYMBOL_Bool = 77                       /* Bool  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 79 "mfpg_dsl.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, mfpg_dsl_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 228 "Parser.C"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   100

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   171,   171,   173,   174,   176,   178,   179,   180,   181,
     183,   185,   186,   187,   188,   190,   192,   193,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     208,   209,   210,   212,   214,   216,   217,   218,   219,   221,
     223,   224,   226,   227,   228,   229,   231,   233,   234,   236,
     237,   238,   239,   240,   242,   244,   245,   246,   247,   248,
     249,   251,   252,   254,   255,   257,   258,   260,   262,   263
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "_ERROR_", "_BANGEQ",
  "_DAMP", "_LPAREN", "_RPAREN", "_STAR", "_PLUS", "_COMMA", "_MINUS",
  "_DMINUS", "_RARROW", "_COLON", "_DCOLON", "_SEMI", "_LT", "_LDARROW",
  "_EQ", "_DEQ", "_GT", "_GTEQ", "_KW_A", "_KW_As", "_KW_B", "_KW_C",
  "_KW_Cs", "_KW_D", "_KW_Ds", "_KW_E", "_KW_F", "_KW_Fs", "_KW_G",
  "_KW_Gs", "_LBRACK", "_RBRACK", "_UNDERSCORE", "_KW_b", "_KW_d",
  "_KW_double", "_KW_false", "_KW_i", "_KW_int", "_KW_true", "_LBRACE",
  "_DBAR", "_RBRACE", "_STRING_", "_INTEGER_", "_DOUBLE_", "$accept",
  "Input", "Output", "AttrDecl", "ListAttrDecl", "IStr", "ListIStr",
  "SPos", "Note", "NoteBase", "AttrType", "Act", "ActionName", "ListAct",
  "DFun", "DFun1", "DFun2", "CFun", "CFun1", "CFun2", "Attr", "CompOp",
  "BoolOp", "Num", "Exp", "Scale", "Bool", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-58)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       5,   -38,    13,   -58,   -58,    43,   -58,    17,    49,    22,
      41,    29,   -58,   -58,   -58,    51,    49,    49,    26,    19,
     -58,   -58,    33,   -58,   -58,   -58,    25,    28,    69,    33,
      33,    36,     0,   -58,   -58,   -58,     6,    66,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,    73,    50,    36,    36,    -2,     0,    39,   -58,
     -58,    -2,   -58,   -58,     1,   -58,    -1,   -58,   -58,   -58,
      82,     2,   -58,    -5,   -58,    -2,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -12,    19,   -58,    -5,   -58,   -58,
       3,   -58,     3,   -58,   -58,   -58,    52,    83,     3,    -5,
      19,   -12,   -58,   -58,    84,   -58,   -58,   -12,   -58
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     3,     4,     0,     1,     0,     0,     0,
       6,     0,    32,    31,    30,     0,     0,     8,     0,     0,
       7,     9,     0,    54,     5,    15,    11,     0,     0,     0,
      13,    37,     0,    12,    14,    34,    35,     0,     2,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    16,     0,     0,    37,    37,     0,     0,     0,    36,
      38,     0,    69,    68,     0,    47,    53,    52,    10,    17,
       0,    46,    61,     0,    62,     0,    56,    66,    65,    58,
      60,    55,    57,    59,     0,     0,    49,     0,    63,    64,
      33,    40,     0,    45,    48,    51,     0,     0,    39,     0,
       0,     0,    42,    41,    44,    50,    67,     0,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -58,   -58,   -58,   -58,    46,   -58,    47,   -58,    34,   -58,
     -58,   -58,   -58,    24,   -58,     7,    -6,   -58,    35,    20,
     -19,     4,   -58,   -48,   -57,   -58,   -58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     5,    10,    11,    26,    27,    28,    52,    53,
      15,    36,    37,    38,    97,    90,    91,    70,    64,    65,
      66,    84,    75,    93,    99,   107,    67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      24,    87,     3,    76,    61,     4,    72,    72,    77,    85,
      78,     1,    77,     6,    78,    73,    79,    80,    54,    81,
      82,    83,    55,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,   100,    95,    88,    89,    62,
      29,    30,    63,    23,    88,    89,    23,    74,    74,    51,
       7,    16,     8,   105,    92,     9,    76,    17,    19,   108,
      12,    13,    20,    21,    14,    18,    96,    23,    92,    79,
      80,    22,    81,    82,    83,    31,    33,    34,    59,    60,
      92,   104,    25,    32,    35,    56,    57,    58,    69,    86,
     102,    68,   106,   103,    98,    94,    71,     0,     0,     0,
     101
};

static const yytype_int8 yycheck[] =
{
      19,     6,    40,     4,     6,    43,     5,     5,     9,    66,
      11,     6,     9,     0,    11,    14,    17,    18,    12,    20,
      21,    22,    16,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    92,    84,    49,    50,    41,
      15,    16,    44,    48,    49,    50,    48,    46,    46,    49,
       7,    10,    35,   101,    73,     6,     4,    16,     7,   107,
      38,    39,    16,    17,    42,    36,    85,    48,    87,    17,
      18,    45,    20,    21,    22,    47,    29,    30,    54,    55,
      99,   100,    49,    14,    48,    19,    13,    37,    49,     7,
       7,    57,     8,    99,    87,    75,    61,    -1,    -1,    -1,
      96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    52,    40,    43,    53,     0,     7,    35,     6,
      54,    55,    38,    39,    42,    61,    10,    16,    36,     7,
      55,    55,    45,    48,    71,    49,    56,    57,    58,    15,
      16,    47,    14,    57,    57,    48,    62,    63,    64,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    49,    59,    60,    12,    16,    19,    13,    37,    64,
      64,     6,    41,    44,    69,    70,    71,    77,    59,    49,
      68,    69,     5,    14,    46,    73,     4,     9,    11,    17,
      18,    20,    21,    22,    72,    75,     7,     6,    49,    50,
      66,    67,    71,    74,    70,    74,    71,    65,    66,    75,
      75,    72,     7,    67,    71,    74,     8,    76,    74
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    55,    55,    55,    55,
      56,    57,    57,    57,    57,    58,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    61,    61,    62,    63,    64,    64,    64,    64,    65,
      66,    66,    67,    67,    67,    67,    68,    69,    69,    70,
      70,    70,    70,    70,    71,    72,    72,    72,    72,    72,
      72,    73,    73,    74,    74,    75,    75,    76,    77,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,    10,     1,     1,     4,     1,     3,     2,     3,
       5,     1,     3,     2,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     1,     1,     3,     0,     3,     1,
       1,     3,     3,     5,     3,     1,     1,     1,     3,     3,
       5,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, scanner, result, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner, result); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (result);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner, result);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, yyscan_t scanner, YYSTYPE *result)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner, result);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, result); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (result);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, YYSTYPE *result)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Input: _LPAREN Output _RPAREN _LBRACK ListAttrDecl _RBRACK _LBRACE ListIStr _RBRACE ListAct  */
#line 171 "mfpg_dsl.y"
                                                                                             { std::reverse((yyvsp[-5].listattrdecl_)->begin(),(yyvsp[-5].listattrdecl_)->end()) ; std::reverse((yyvsp[-2].lististr_)->begin(),(yyvsp[-2].lististr_)->end()) ; std::reverse((yyvsp[0].listact_)->begin(),(yyvsp[0].listact_)->end()) ;(yyval.input_) = new BInput((yyvsp[-8].output_), (yyvsp[-5].listattrdecl_), (yyvsp[-2].lististr_), (yyvsp[0].listact_)); result->input_ = (yyval.input_); }
#line 1384 "Parser.C"
    break;

  case 3: /* Output: _KW_double  */
#line 173 "mfpg_dsl.y"
                    { (yyval.output_) = new DOutput(); result->output_ = (yyval.output_); }
#line 1390 "Parser.C"
    break;

  case 4: /* Output: _KW_int  */
#line 174 "mfpg_dsl.y"
            { (yyval.output_) = new IOutput(); result->output_ = (yyval.output_); }
#line 1396 "Parser.C"
    break;

  case 5: /* AttrDecl: _LPAREN AttrType _RPAREN Attr  */
#line 176 "mfpg_dsl.y"
                                         { (yyval.attrdecl_) = new DAttr((yyvsp[-2].attrtype_), (yyvsp[0].attr_)); result->attrdecl_ = (yyval.attrdecl_); }
#line 1402 "Parser.C"
    break;

  case 6: /* ListAttrDecl: AttrDecl  */
#line 178 "mfpg_dsl.y"
                        { (yyval.listattrdecl_) = new ListAttrDecl(); (yyval.listattrdecl_)->push_back((yyvsp[0].attrdecl_)); result->listattrdecl_ = (yyval.listattrdecl_); }
#line 1408 "Parser.C"
    break;

  case 7: /* ListAttrDecl: AttrDecl _COMMA ListAttrDecl  */
#line 179 "mfpg_dsl.y"
                                 { (yyvsp[0].listattrdecl_)->push_back((yyvsp[-2].attrdecl_)); (yyval.listattrdecl_) = (yyvsp[0].listattrdecl_); result->listattrdecl_ = (yyval.listattrdecl_); }
#line 1414 "Parser.C"
    break;

  case 8: /* ListAttrDecl: AttrDecl _SEMI  */
#line 180 "mfpg_dsl.y"
                   { (yyval.listattrdecl_) = new ListAttrDecl(); (yyval.listattrdecl_)->push_back((yyvsp[-1].attrdecl_)); result->listattrdecl_ = (yyval.listattrdecl_); }
#line 1420 "Parser.C"
    break;

  case 9: /* ListAttrDecl: AttrDecl _SEMI ListAttrDecl  */
#line 181 "mfpg_dsl.y"
                                { (yyvsp[0].listattrdecl_)->push_back((yyvsp[-2].attrdecl_)); (yyval.listattrdecl_) = (yyvsp[0].listattrdecl_); result->listattrdecl_ = (yyval.listattrdecl_); }
#line 1426 "Parser.C"
    break;

  case 10: /* IStr: SPos _COLON Note _RARROW Note  */
#line 183 "mfpg_dsl.y"
                                     { (yyval.istr_) = new StringDef((yyvsp[-4].spos_), (yyvsp[-2].note_), (yyvsp[0].note_)); result->istr_ = (yyval.istr_); }
#line 1432 "Parser.C"
    break;

  case 11: /* ListIStr: IStr  */
#line 185 "mfpg_dsl.y"
                { (yyval.lististr_) = new ListIStr(); (yyval.lististr_)->push_back((yyvsp[0].istr_)); result->lististr_ = (yyval.lististr_); }
#line 1438 "Parser.C"
    break;

  case 12: /* ListIStr: IStr _DCOLON ListIStr  */
#line 186 "mfpg_dsl.y"
                          { (yyvsp[0].lististr_)->push_back((yyvsp[-2].istr_)); (yyval.lististr_) = (yyvsp[0].lististr_); result->lististr_ = (yyval.lististr_); }
#line 1444 "Parser.C"
    break;

  case 13: /* ListIStr: IStr _SEMI  */
#line 187 "mfpg_dsl.y"
               { (yyval.lististr_) = new ListIStr(); (yyval.lististr_)->push_back((yyvsp[-1].istr_)); result->lististr_ = (yyval.lististr_); }
#line 1450 "Parser.C"
    break;

  case 14: /* ListIStr: IStr _SEMI ListIStr  */
#line 188 "mfpg_dsl.y"
                        { (yyvsp[0].lististr_)->push_back((yyvsp[-2].istr_)); (yyval.lististr_) = (yyvsp[0].lististr_); result->lististr_ = (yyval.lististr_); }
#line 1456 "Parser.C"
    break;

  case 15: /* SPos: _INTEGER_  */
#line 190 "mfpg_dsl.y"
                 { (yyval.spos_) = new ISPos((yyvsp[0]._int)); result->spos_ = (yyval.spos_); }
#line 1462 "Parser.C"
    break;

  case 16: /* Note: _INTEGER_  */
#line 192 "mfpg_dsl.y"
                 { (yyval.note_) = new INote((yyvsp[0]._int)); result->note_ = (yyval.note_); }
#line 1468 "Parser.C"
    break;

  case 17: /* Note: NoteBase _UNDERSCORE _INTEGER_  */
#line 193 "mfpg_dsl.y"
                                   { (yyval.note_) = new NNote((yyvsp[-2].notebase_), (yyvsp[0]._int)); result->note_ = (yyval.note_); }
#line 1474 "Parser.C"
    break;

  case 18: /* NoteBase: _KW_A  */
#line 195 "mfpg_dsl.y"
                 { (yyval.notebase_) = new NoteBase_A(); result->notebase_ = (yyval.notebase_); }
#line 1480 "Parser.C"
    break;

  case 19: /* NoteBase: _KW_As  */
#line 196 "mfpg_dsl.y"
           { (yyval.notebase_) = new NoteBase_As(); result->notebase_ = (yyval.notebase_); }
#line 1486 "Parser.C"
    break;

  case 20: /* NoteBase: _KW_B  */
#line 197 "mfpg_dsl.y"
          { (yyval.notebase_) = new NoteBase_B(); result->notebase_ = (yyval.notebase_); }
#line 1492 "Parser.C"
    break;

  case 21: /* NoteBase: _KW_C  */
#line 198 "mfpg_dsl.y"
          { (yyval.notebase_) = new NoteBase_C(); result->notebase_ = (yyval.notebase_); }
#line 1498 "Parser.C"
    break;

  case 22: /* NoteBase: _KW_Cs  */
#line 199 "mfpg_dsl.y"
           { (yyval.notebase_) = new NoteBase_Cs(); result->notebase_ = (yyval.notebase_); }
#line 1504 "Parser.C"
    break;

  case 23: /* NoteBase: _KW_D  */
#line 200 "mfpg_dsl.y"
          { (yyval.notebase_) = new NoteBase_D(); result->notebase_ = (yyval.notebase_); }
#line 1510 "Parser.C"
    break;

  case 24: /* NoteBase: _KW_Ds  */
#line 201 "mfpg_dsl.y"
           { (yyval.notebase_) = new NoteBase_Ds(); result->notebase_ = (yyval.notebase_); }
#line 1516 "Parser.C"
    break;

  case 25: /* NoteBase: _KW_E  */
#line 202 "mfpg_dsl.y"
          { (yyval.notebase_) = new NoteBase_E(); result->notebase_ = (yyval.notebase_); }
#line 1522 "Parser.C"
    break;

  case 26: /* NoteBase: _KW_F  */
#line 203 "mfpg_dsl.y"
          { (yyval.notebase_) = new NoteBase_F(); result->notebase_ = (yyval.notebase_); }
#line 1528 "Parser.C"
    break;

  case 27: /* NoteBase: _KW_Fs  */
#line 204 "mfpg_dsl.y"
           { (yyval.notebase_) = new NoteBase_Fs(); result->notebase_ = (yyval.notebase_); }
#line 1534 "Parser.C"
    break;

  case 28: /* NoteBase: _KW_G  */
#line 205 "mfpg_dsl.y"
          { (yyval.notebase_) = new NoteBase_G(); result->notebase_ = (yyval.notebase_); }
#line 1540 "Parser.C"
    break;

  case 29: /* NoteBase: _KW_Gs  */
#line 206 "mfpg_dsl.y"
           { (yyval.notebase_) = new NoteBase_Gs(); result->notebase_ = (yyval.notebase_); }
#line 1546 "Parser.C"
    break;

  case 30: /* AttrType: _KW_i  */
#line 208 "mfpg_dsl.y"
                 { (yyval.attrtype_) = new AttrType_i(); result->attrtype_ = (yyval.attrtype_); }
#line 1552 "Parser.C"
    break;

  case 31: /* AttrType: _KW_d  */
#line 209 "mfpg_dsl.y"
          { (yyval.attrtype_) = new AttrType_d(); result->attrtype_ = (yyval.attrtype_); }
#line 1558 "Parser.C"
    break;

  case 32: /* AttrType: _KW_b  */
#line 210 "mfpg_dsl.y"
          { (yyval.attrtype_) = new AttrType_b(); result->attrtype_ = (yyval.attrtype_); }
#line 1564 "Parser.C"
    break;

  case 33: /* Act: ActionName _EQ CFun1 _COLON DFun1  */
#line 212 "mfpg_dsl.y"
                                        { (yyval.act_) = new FunList((yyvsp[-4].actionname_), (yyvsp[-2].cfun_), (yyvsp[0].dfun_)); result->act_ = (yyval.act_); }
#line 1570 "Parser.C"
    break;

  case 34: /* ActionName: _STRING_  */
#line 214 "mfpg_dsl.y"
                      { (yyval.actionname_) = new AName((yyvsp[0]._string)); result->actionname_ = (yyval.actionname_); }
#line 1576 "Parser.C"
    break;

  case 35: /* ListAct: Act  */
#line 216 "mfpg_dsl.y"
              { (yyval.listact_) = new ListAct(); (yyval.listact_)->push_back((yyvsp[0].act_)); result->listact_ = (yyval.listact_); }
#line 1582 "Parser.C"
    break;

  case 36: /* ListAct: Act _DMINUS ListAct  */
#line 217 "mfpg_dsl.y"
                        { (yyvsp[0].listact_)->push_back((yyvsp[-2].act_)); (yyval.listact_) = (yyvsp[0].listact_); result->listact_ = (yyval.listact_); }
#line 1588 "Parser.C"
    break;

  case 37: /* ListAct: %empty  */
#line 218 "mfpg_dsl.y"
                { (yyval.listact_) = new ListAct(); result->listact_ = (yyval.listact_); }
#line 1594 "Parser.C"
    break;

  case 38: /* ListAct: Act _SEMI ListAct  */
#line 219 "mfpg_dsl.y"
                      { (yyvsp[0].listact_)->push_back((yyvsp[-2].act_)); (yyval.listact_) = (yyvsp[0].listact_); result->listact_ = (yyval.listact_); }
#line 1600 "Parser.C"
    break;

  case 39: /* DFun: DFun1  */
#line 221 "mfpg_dsl.y"
             { (yyval.dfun_) = (yyvsp[0].dfun_); result->dfun_ = (yyval.dfun_); }
#line 1606 "Parser.C"
    break;

  case 40: /* DFun1: DFun2  */
#line 223 "mfpg_dsl.y"
              { (yyval.dfun_) = (yyvsp[0].dfun_); result->dfun_ = (yyval.dfun_); }
#line 1612 "Parser.C"
    break;

  case 41: /* DFun1: DFun1 Exp DFun2  */
#line 224 "mfpg_dsl.y"
                    { (yyval.dfun_) = new CombDist((yyvsp[-2].dfun_), (yyvsp[-1].exp_), (yyvsp[0].dfun_)); result->dfun_ = (yyval.dfun_); }
#line 1618 "Parser.C"
    break;

  case 42: /* DFun2: _LPAREN DFun _RPAREN  */
#line 226 "mfpg_dsl.y"
                             { (yyval.dfun_) = (yyvsp[-1].dfun_); result->dfun_ = (yyval.dfun_); }
#line 1624 "Parser.C"
    break;

  case 43: /* DFun2: Attr Exp Attr Scale Num  */
#line 227 "mfpg_dsl.y"
                            { (yyval.dfun_) = new ScaledDist((yyvsp[-4].attr_), (yyvsp[-3].exp_), (yyvsp[-2].attr_), (yyvsp[-1].scale_), (yyvsp[0].num_)); result->dfun_ = (yyval.dfun_); }
#line 1630 "Parser.C"
    break;

  case 44: /* DFun2: Attr Exp Attr  */
#line 228 "mfpg_dsl.y"
                  { (yyval.dfun_) = new DirectDist((yyvsp[-2].attr_), (yyvsp[-1].exp_), (yyvsp[0].attr_)); result->dfun_ = (yyval.dfun_); }
#line 1636 "Parser.C"
    break;

  case 45: /* DFun2: Num  */
#line 229 "mfpg_dsl.y"
        { (yyval.dfun_) = new ConstDist((yyvsp[0].num_)); result->dfun_ = (yyval.dfun_); }
#line 1642 "Parser.C"
    break;

  case 46: /* CFun: CFun1  */
#line 231 "mfpg_dsl.y"
             { (yyval.cfun_) = (yyvsp[0].cfun_); result->cfun_ = (yyval.cfun_); }
#line 1648 "Parser.C"
    break;

  case 47: /* CFun1: CFun2  */
#line 233 "mfpg_dsl.y"
              { (yyval.cfun_) = (yyvsp[0].cfun_); result->cfun_ = (yyval.cfun_); }
#line 1654 "Parser.C"
    break;

  case 48: /* CFun1: CFun1 BoolOp CFun2  */
#line 234 "mfpg_dsl.y"
                       { (yyval.cfun_) = new CombCond((yyvsp[-2].cfun_), (yyvsp[-1].boolop_), (yyvsp[0].cfun_)); result->cfun_ = (yyval.cfun_); }
#line 1660 "Parser.C"
    break;

  case 49: /* CFun2: _LPAREN CFun _RPAREN  */
#line 236 "mfpg_dsl.y"
                             { (yyval.cfun_) = (yyvsp[-1].cfun_); result->cfun_ = (yyval.cfun_); }
#line 1666 "Parser.C"
    break;

  case 50: /* CFun2: Attr Exp Attr CompOp Num  */
#line 237 "mfpg_dsl.y"
                             { (yyval.cfun_) = new CompCond((yyvsp[-4].attr_), (yyvsp[-3].exp_), (yyvsp[-2].attr_), (yyvsp[-1].compop_), (yyvsp[0].num_)); result->cfun_ = (yyval.cfun_); }
#line 1672 "Parser.C"
    break;

  case 51: /* CFun2: Attr CompOp Num  */
#line 238 "mfpg_dsl.y"
                    { (yyval.cfun_) = new ValueCond((yyvsp[-2].attr_), (yyvsp[-1].compop_), (yyvsp[0].num_)); result->cfun_ = (yyval.cfun_); }
#line 1678 "Parser.C"
    break;

  case 52: /* CFun2: Bool  */
#line 239 "mfpg_dsl.y"
         { (yyval.cfun_) = new BoolCond((yyvsp[0].bool_)); result->cfun_ = (yyval.cfun_); }
#line 1684 "Parser.C"
    break;

  case 53: /* CFun2: Attr  */
#line 240 "mfpg_dsl.y"
         { (yyval.cfun_) = new AttrCond((yyvsp[0].attr_)); result->cfun_ = (yyval.cfun_); }
#line 1690 "Parser.C"
    break;

  case 54: /* Attr: _STRING_  */
#line 242 "mfpg_dsl.y"
                { (yyval.attr_) = new EAttr((yyvsp[0]._string)); result->attr_ = (yyval.attr_); }
#line 1696 "Parser.C"
    break;

  case 55: /* CompOp: _DEQ  */
#line 244 "mfpg_dsl.y"
              { (yyval.compop_) = new Eq(); result->compop_ = (yyval.compop_); }
#line 1702 "Parser.C"
    break;

  case 56: /* CompOp: _BANGEQ  */
#line 245 "mfpg_dsl.y"
            { (yyval.compop_) = new NEq(); result->compop_ = (yyval.compop_); }
#line 1708 "Parser.C"
    break;

  case 57: /* CompOp: _GT  */
#line 246 "mfpg_dsl.y"
        { (yyval.compop_) = new Gt(); result->compop_ = (yyval.compop_); }
#line 1714 "Parser.C"
    break;

  case 58: /* CompOp: _LT  */
#line 247 "mfpg_dsl.y"
        { (yyval.compop_) = new Lt(); result->compop_ = (yyval.compop_); }
#line 1720 "Parser.C"
    break;

  case 59: /* CompOp: _GTEQ  */
#line 248 "mfpg_dsl.y"
          { (yyval.compop_) = new Gte(); result->compop_ = (yyval.compop_); }
#line 1726 "Parser.C"
    break;

  case 60: /* CompOp: _LDARROW  */
#line 249 "mfpg_dsl.y"
             { (yyval.compop_) = new Lte(); result->compop_ = (yyval.compop_); }
#line 1732 "Parser.C"
    break;

  case 61: /* BoolOp: _DAMP  */
#line 251 "mfpg_dsl.y"
               { (yyval.boolop_) = new And(); result->boolop_ = (yyval.boolop_); }
#line 1738 "Parser.C"
    break;

  case 62: /* BoolOp: _DBAR  */
#line 252 "mfpg_dsl.y"
          { (yyval.boolop_) = new Or(); result->boolop_ = (yyval.boolop_); }
#line 1744 "Parser.C"
    break;

  case 63: /* Num: _INTEGER_  */
#line 254 "mfpg_dsl.y"
                { (yyval.num_) = new CInt((yyvsp[0]._int)); result->num_ = (yyval.num_); }
#line 1750 "Parser.C"
    break;

  case 64: /* Num: _DOUBLE_  */
#line 255 "mfpg_dsl.y"
             { (yyval.num_) = new CDouble((yyvsp[0]._double)); result->num_ = (yyval.num_); }
#line 1756 "Parser.C"
    break;

  case 65: /* Exp: _MINUS  */
#line 257 "mfpg_dsl.y"
             { (yyval.exp_) = new ESub(); result->exp_ = (yyval.exp_); }
#line 1762 "Parser.C"
    break;

  case 66: /* Exp: _PLUS  */
#line 258 "mfpg_dsl.y"
          { (yyval.exp_) = new EPlus(); result->exp_ = (yyval.exp_); }
#line 1768 "Parser.C"
    break;

  case 67: /* Scale: _STAR  */
#line 260 "mfpg_dsl.y"
              { (yyval.scale_) = new SMul(); result->scale_ = (yyval.scale_); }
#line 1774 "Parser.C"
    break;

  case 68: /* Bool: _KW_true  */
#line 262 "mfpg_dsl.y"
                { (yyval.bool_) = new VTrue(); result->bool_ = (yyval.bool_); }
#line 1780 "Parser.C"
    break;

  case 69: /* Bool: _KW_false  */
#line 263 "mfpg_dsl.y"
              { (yyval.bool_) = new VFalse(); result->bool_ = (yyval.bool_); }
#line 1786 "Parser.C"
    break;


#line 1790 "Parser.C"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (&yylloc, scanner, result, YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner, result);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, result, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, result);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 266 "mfpg_dsl.y"



/* Entrypoint: parse Input* from file. */
Input* pInput(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.input_;
  }
}

/* Entrypoint: parse Input* from string. */
Input* psInput(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.input_;
  }
}

/* Entrypoint: parse Output* from file. */
Output* pOutput(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.output_;
  }
}

/* Entrypoint: parse Output* from string. */
Output* psOutput(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.output_;
  }
}

/* Entrypoint: parse AttrDecl* from file. */
AttrDecl* pAttrDecl(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.attrdecl_;
  }
}

/* Entrypoint: parse AttrDecl* from string. */
AttrDecl* psAttrDecl(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.attrdecl_;
  }
}

/* Entrypoint: parse ListAttrDecl* from file. */
ListAttrDecl* pListAttrDecl(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listattrdecl_->begin(), result.listattrdecl_->end());
    return result.listattrdecl_;
  }
}

/* Entrypoint: parse ListAttrDecl* from string. */
ListAttrDecl* psListAttrDecl(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listattrdecl_->begin(), result.listattrdecl_->end());
    return result.listattrdecl_;
  }
}

/* Entrypoint: parse IStr* from file. */
IStr* pIStr(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.istr_;
  }
}

/* Entrypoint: parse IStr* from string. */
IStr* psIStr(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.istr_;
  }
}

/* Entrypoint: parse ListIStr* from file. */
ListIStr* pListIStr(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.lististr_->begin(), result.lististr_->end());
    return result.lististr_;
  }
}

/* Entrypoint: parse ListIStr* from string. */
ListIStr* psListIStr(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.lististr_->begin(), result.lististr_->end());
    return result.lististr_;
  }
}

/* Entrypoint: parse SPos* from file. */
SPos* pSPos(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.spos_;
  }
}

/* Entrypoint: parse SPos* from string. */
SPos* psSPos(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.spos_;
  }
}

/* Entrypoint: parse Note* from file. */
Note* pNote(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.note_;
  }
}

/* Entrypoint: parse Note* from string. */
Note* psNote(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.note_;
  }
}

/* Entrypoint: parse NoteBase* from file. */
NoteBase* pNoteBase(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.notebase_;
  }
}

/* Entrypoint: parse NoteBase* from string. */
NoteBase* psNoteBase(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.notebase_;
  }
}

/* Entrypoint: parse AttrType* from file. */
AttrType* pAttrType(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.attrtype_;
  }
}

/* Entrypoint: parse AttrType* from string. */
AttrType* psAttrType(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.attrtype_;
  }
}

/* Entrypoint: parse Act* from file. */
Act* pAct(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.act_;
  }
}

/* Entrypoint: parse Act* from string. */
Act* psAct(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.act_;
  }
}

/* Entrypoint: parse ActionName* from file. */
ActionName* pActionName(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.actionname_;
  }
}

/* Entrypoint: parse ActionName* from string. */
ActionName* psActionName(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.actionname_;
  }
}

/* Entrypoint: parse ListAct* from file. */
ListAct* pListAct(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listact_->begin(), result.listact_->end());
    return result.listact_;
  }
}

/* Entrypoint: parse ListAct* from string. */
ListAct* psListAct(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listact_->begin(), result.listact_->end());
    return result.listact_;
  }
}

/* Entrypoint: parse DFun* from file. */
DFun* pDFun(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.dfun_;
  }
}

/* Entrypoint: parse DFun* from string. */
DFun* psDFun(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.dfun_;
  }
}

/* Entrypoint: parse DFun* from file. */
DFun* pDFun1(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.dfun_;
  }
}

/* Entrypoint: parse DFun* from string. */
DFun* psDFun1(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.dfun_;
  }
}

/* Entrypoint: parse DFun* from file. */
DFun* pDFun2(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.dfun_;
  }
}

/* Entrypoint: parse DFun* from string. */
DFun* psDFun2(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.dfun_;
  }
}

/* Entrypoint: parse CFun* from file. */
CFun* pCFun(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.cfun_;
  }
}

/* Entrypoint: parse CFun* from string. */
CFun* psCFun(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.cfun_;
  }
}

/* Entrypoint: parse CFun* from file. */
CFun* pCFun1(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.cfun_;
  }
}

/* Entrypoint: parse CFun* from string. */
CFun* psCFun1(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.cfun_;
  }
}

/* Entrypoint: parse CFun* from file. */
CFun* pCFun2(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.cfun_;
  }
}

/* Entrypoint: parse CFun* from string. */
CFun* psCFun2(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.cfun_;
  }
}

/* Entrypoint: parse Attr* from file. */
Attr* pAttr(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.attr_;
  }
}

/* Entrypoint: parse Attr* from string. */
Attr* psAttr(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.attr_;
  }
}

/* Entrypoint: parse CompOp* from file. */
CompOp* pCompOp(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.compop_;
  }
}

/* Entrypoint: parse CompOp* from string. */
CompOp* psCompOp(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.compop_;
  }
}

/* Entrypoint: parse BoolOp* from file. */
BoolOp* pBoolOp(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.boolop_;
  }
}

/* Entrypoint: parse BoolOp* from string. */
BoolOp* psBoolOp(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.boolop_;
  }
}

/* Entrypoint: parse Num* from file. */
Num* pNum(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.num_;
  }
}

/* Entrypoint: parse Num* from string. */
Num* psNum(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.num_;
  }
}

/* Entrypoint: parse Exp* from file. */
Exp* pExp(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.exp_;
  }
}

/* Entrypoint: parse Exp* from string. */
Exp* psExp(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.exp_;
  }
}

/* Entrypoint: parse Scale* from file. */
Scale* pScale(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.scale_;
  }
}

/* Entrypoint: parse Scale* from string. */
Scale* psScale(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.scale_;
  }
}

/* Entrypoint: parse Bool* from file. */
Bool* pBool(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.bool_;
  }
}

/* Entrypoint: parse Bool* from string. */
Bool* psBool(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = mfpg_dsl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = mfpg_dsl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  mfpg_dsl__delete_buffer(buf, scanner);
  mfpg_dsl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.bool_;
  }
}



