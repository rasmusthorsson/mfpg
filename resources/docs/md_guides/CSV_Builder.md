# CSV Note Mapper File Generator

This minor program is meant to help with generation of CSV Note Mapper files. 

**The Builder.cpp** file contains an example notemapper that defines the **BasicNoteMapper** as a CSV file. 
This CSV file can then be used with the _"--notemapper=FILENAME"_ flag for the MFPG program to use notes 
defined there as the notemapper. There is a custom function that can be used to define a custom notemapper 
in the **Builder.cpp** file. 

To define a custom notemapper, define it in the **Builder.cpp** file in the _build_file_CUSTOM_ function, 
then uncomment the _#define CUSTOM_ comment at the start of the **Builder.h** file.

The program is compiled using the **make** command in the terminal, and the program is then used by
running it with a file name where the output is to be written. If no output is given then the program
defaults to outputting to _CSV_Map.csv_.
