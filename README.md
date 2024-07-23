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
section.

## Manual Compilation

If you want to compile it yourself the easiest method is to clone the
repo and use CMake. This can be done by first creating a <i>build</i> directory in 
the root directory for the repo, then in the new build directory configure cmake using 
<i>cmake ..</i>, and finally building using <i>cmake --build .</i> in the build 
directory. To build the GUI you will need wxWidgets installed at (on linux) 
<i>/usr/local/wx_build/lib/cmake/WxWidgets/</i>. This can be achieved by specifying
the <b>CMAKE_INSTALL_PREFIX</b> variable to be <i>/usr/local/wx_build/</i> when 
configuring the WxWidget cmake project prior to installing it. For more information 
on how to install WxWidget for cmake, see 
https://docs.wxwidgets.org/latest/overview\_cmake.html . Alternatively, building the
GUI can be disabled by specifying <b>-DBUILD_GUI=OFF</b> when configuring the MFPG
cmake project (i.e. <i>cmake .. <b>-DBUILD_GUI=OFF</b></i>). If there is a problem
with the MX library when trying to build the project, using the <b>REBUILD_MX</b>
(in the same way as the <b>BUILD_GUI</b> option previously mentioned) option can
be turned on to rebuild the entire **mx** library, this is a lengthy process. Tests
can also be turned off by specifying the <b>BUILD_TESTS</b> to be <b>OFF</b>.

Using other installation methods of WxWidgets has worked in the past, although then
some changes to the CMakeLists.txt file in the MFPG root directory might be needed 
(More information will be added in the future about compiling the software from scratch).

## GitHub Pages

For more information, useful links, guides, and tutorials, check out the GitHub pages 
webpage at https://rasmusthorsson.github.io/mfpg/
