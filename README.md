![ubuntu](https://github.com/rasmusthorsson/mfpg/actions/workflows/ubuntu.yml/badge.svg)
![windows](https://github.com/rasmusthorsson/mfpg/actions/workflows/windows.yml/badge.svg)
![version](/resources/docs/images/Version_Badge.png)

# Music Fingering Position Generator

A personal project with the goal of creating software to automically construct a 
fingering position sequence for a given	music score (for a single bowed string 
instrument currently). By using user defined preferences and instrument definitions 
the software should be able to give a good base of fingering positions when fed a sheet 
music MusicXML file. Uses the **mx** library (found at https://github.com/webern/mx) for 
MusicXML parsing. Also uses the **cxxopts** library for parsing inputs and managing
options (https://github.com/jarro2783/cxxopts). **gtest** is used for unit- and integration
tests.

For more information, useful links, guides, and tutorials, check out the GitHub pages 
webpage at https://rasmusthorsson.github.io/mfpg/

**Note that this program is not yet ready for release**
