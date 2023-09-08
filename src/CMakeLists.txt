cmake_minimum_required(VERSION 3.17)

target_link_libraries(tests mx)
target_link_libraries(mfpr_count mx)
target_include_directories(mfpr_count 
	PRIVATE "${CMAKE_SOURCE_DIR}/mx/Sourcecode/include")
