# Changes after build for Windows

mfpg_dsl_lex_destroy in parser returns an _int_ not a _void_ (line 93)\
\_STRING\_ in Bison.H can not be named that, remove last \_ (line 103)\
also apply this change to Lexer.C (line 1420)\
For the Lexer UNISTD does work on vscode, io.h needs to be used (line 817).\
    #define YY_NO_UNISTD_H
    #include <io.h>
For the same reason, replace isatty with _isatty (line 2053).\