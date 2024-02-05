cmake_minimum_required(VERSION 3.17)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 01)
set(VERSION_MFPG ${VERSION_MAJOR}.${VERSION_MINOR})

configure_file(conf/conf_cmake.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/conf_cmake.h)

project(mfpr VERSION ${VERSION_MFPG})

#MX library is not compatible with g++-13.
set(CMAKE_CXX_COMPILER /usr/bin/g++-12 CACHE PATH "")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)


include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571
)
FetchContent_Declare(
	cxxopts
	GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
	GIT_TAG eb787304d67ec22f7c3a184ee8b4c481d04357fd
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(cxxopts)

file(GLOB_RECURSE SRC_BASE src/main.cpp src/SimplifiedNote.cpp src/MXConverter.cpp
	src/ConversionException.cpp src/NoteList.cpp src/IString.cpp 
	src/BasicNoteMapper.cpp src/Instrument.cpp src/SolverException.cpp
	src/GreedySolver.cpp)
file(GLOB_RECURSE TEST_BASE src/tests.cpp src/SimplifiedNote.cpp src/MXConverter.cpp 
	src/ConversionException.cpp src/NoteList.cpp src/IString.cpp 
	src/BasicNoteMapper.cpp src/Instrument.cpp src/SolverException.cpp
	src/GreedySolver.cpp)

add_executable(mfpr ${SRC_BASE})
add_executable(tests ${TEST_BASE}) 

option(REBUILD_MX "Recompile mx library .a file" OFF)

if(REBUILD_MX)

 FetchContent_Declare(
        mx
	 GIT_REPOSITORY https://github.com/webern/mx.git
	 GIT_TAG c6144d229d9c976833b80de0d25e2636acf7f323
 )
 FetchContent_MakeAvailable(mx)
 
# add_subdirectory(deps/mx)
endif()

add_subdirectory(src)

target_link_libraries(
	tests
	GTest::gtest_main
	GTest::gmock_main
)

include(GoogleTest)

enable_testing()

gtest_discover_tests(tests)

#add_test(NAME fewer_args COMMAND mfpr)

#set_tests_properties(fewer_args
#	PROPERTIES PASS_REGULAR_EXPRESSION "Please specify an input MusicXML file.\n"
#)

