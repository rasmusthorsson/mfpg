cmake_minimum_required(VERSION 3.17)

project(mfpr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SRC_BASE src/main.cpp src/SimplifiedNote.cpp src/MXConverter.cpp
	src/ConversionException.cpp src/NoteList.cpp src/IString.cpp 
	src/BasicNoteMapper.cpp src/Instrument.cpp src/SolverException.cpp)
file(GLOB_RECURSE TEST_BASE src/tests.cpp src/SimplifiedNote.cpp src/MXConverter.cpp 
	src/ConversionException.cpp src/NoteList.cpp src/IString.cpp 
	src/BasicNoteMapper.cpp src/Instrument.cpp src/SolverException.cpp)

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
 
 #add_subdirectory(deps/mx) 
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

add_test(NAME fewer_args COMMAND mfpr)
add_test(NAME many_args COMMAND mfpr one two)

set_tests_properties(fewer_args
	PROPERTIES PASS_REGULAR_EXPRESSION "Please specify an input MusicXML file.\n"
)

set_tests_properties(many_args
	PROPERTIES PASS_REGULAR_EXPRESSION "Too many arguments.\n"
)

