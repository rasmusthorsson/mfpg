# CLI Guide

The Command-Line Interface (**CLI**) is an interface to use MFPG via a terminal or 
text-based interface.

## Usage

Usage might vary depending on operating system.

### Linux

Download or compile the binary and use bash to run it with arguments of your choice.

### Windows

TODO

## Available Options

- **score**: The input file, must be an XML file in the form of musicXML, implicitly the last argument of the program and must be supplied.
- **--version**: Check compiled version of MFPG.
- **-h** or **--help**: Outputs all options.
- **-c** or **--csv**: direct the program to output the results in a CSV format.
- **-v integer** or **--verbose=integer**: Sets verbosity to different levels, 0 is silent, 1 is errors, 2 is everything.
- **--greedy**: Directs the program to use the greedy solver instead of a shortest path solver, this is primarily used for testing.
- **shortest-path=integer**: Sets the solver to be the shortest path solver with an optimization level. 0 is no optimization, 1 is invalidation of all previous layers on complete visitation of a layer, and 2 is stop when one solution has been found (and 1).
- **-o filepath** or **--output=filepath**: Directs the program to write the output to filepath.
- **-d dsl_file** or **--dsl=dsl_file**: Use an instrument defined in the DSL\_file instead of the default one.
- **-t integer** or **--test=integer**: Use a test configuration (1 or 2), these are two instrument configurations hardcoded into the program and used to test various parts.
- **-n notemapper_csv_file** or **--notemapper=notemapper_csv_file**: Directs the program to use the CSVNoteMapper using the notemapper\_csv\_file supplied as the notemapper instead of the hardcoded one.
- **--interactive**: Rudimentary interactive mode which is used to explore transitions of a constructed layerlist. Primarily used for debugging.
