# Changes after build for Windows

mfpg\_dsl\_lex\_destroy in parser returns an _int_ not a _void_ (line 93)\
For the Lexer UNISTD does work on vscode, io.h needs to be used (line 817).\
    #define YY\_NO\_UNISTD\_H
    #include <io.h>
