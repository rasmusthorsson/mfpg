![ubuntu](https://github.com/rasmusthorsson/mfpg/actions/workflows/ubuntu.yml/badge.svg)
![windows](https://github.com/rasmusthorsson/mfpg/actions/workflows/windows.yml/badge.svg)

# Music Fingering Position Generator

A personal project with the goal of creating software to automically construct a 
fingering position sequence for a given	music score (only for a single bowed string 
instrument currently). By using user defined preferences and instrument definitions 
the software should be able to give a good base of fingering positions when fed a 
sheet music MusicXML file. Uses the **mx** library (found at 
https://github.com/webern/mx) for MusicXML parsing.

The program is available through binaries for Linux and Windows, either using a 
command-line interface or a GUI which can be found under the <i>Releases</i> 
section. If you want to compile it yourself the easiest method is to clone the
repo and use CMake. 

For more information, useful links, guides, and tutorials, check out the GitHub pages 
webpage at https://rasmusthorsson.github.io/mfpg/

