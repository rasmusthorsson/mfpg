cmake_minimum_required(VERSION 3.17)

project(mfpr_count)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571
)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SRC_BASE src/main.cpp src/SimplifiedNote.cpp src/MXConverter.cpp
	src/ConversionException.cpp src/NoteList.cpp src/IString.cpp src/NoteMapper.cpp)
file(GLOB_RECURSE TEST_BASE src/tests.cpp src/SimplifiedNote.cpp src/MXConverter.cpp 
	src/ConversionException.cpp src/NoteList.cpp src/IString.cpp src/NoteMapper.cpp)

add_executable(mfpr_count ${SRC_BASE})
add_executable(tests ${TEST_BASE}) 

add_subdirectory(libs/mx)
add_subdirectory(src)

target_link_libraries(
	tests
	GTest::gtest_main
)

include(GoogleTest)

enable_testing()

gtest_discover_tests(tests)

add_test(NAME fewer_args COMMAND mfpr_count)
add_test(NAME many_args COMMAND mfpr_count one two)

set_tests_properties(fewer_args
	PROPERTIES PASS_REGULAR_EXPRESSION "Please specify an input MusicXML file.\n"
)

set_tests_properties(many_args
	PROPERTIES PASS_REGULAR_EXPRESSION "Too many arguments.\n"
)

