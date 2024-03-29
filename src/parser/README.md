# Changes after build for Windows

mfpg\_dsl\_lex\_destroy in Parser.C returns an _int_ not a _void_ (line 93)\

For the Lexer UNISTD does work on vscode, io.h needs to be used (line 817).\
    #define YY\_NO\_UNISTD\_H
    #include <io.h>

The second part is automatically fixed using the makefile, the first must be done 
manually
