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

add_executable(mfpr_count src/main.cpp src/SimplifiedNote.cpp src/MXConverter.cpp 
	src/ConversionException.cpp src/NoteList.cpp)
add_executable(tests src/tests.cpp src/SimplifiedNote.cpp src/MXConverter.cpp src/ConversionException.cpp src/NoteList.cpp)

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
add_test(NAME A_W COMMAND mfpr_count "${CMAKE_SOURCE_DIR}/resources/A_W.xml")
add_test(NAME A_D_o_F COMMAND mfpr_count "${CMAKE_SOURCE_DIR}/resources/A_D_o_F.xml")

set_tests_properties(fewer_args
	PROPERTIES PASS_REGULAR_EXPRESSION "Please specify an input MusicXML file.\n"
)

set_tests_properties(many_args
	PROPERTIES PASS_REGULAR_EXPRESSION "Too many arguments.\n"
)

set_tests_properties(A_W
	PROPERTIES PASS_REGULAR_EXPRESSION "56.\n"
)

set_tests_properties(A_D_o_F
	PROPERTIES PASS_REGULAR_EXPRESSION "68.\n"
)
