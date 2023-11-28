cmake_minimum_required(VERSION 3.17)

if(REBUILD_MX)
  target_link_libraries(tests mx)
  target_link_libraries(mfpr mx)
else()
  target_link_libraries(tests ${CMAKE_SOURCE_DIR}/libs/a/libmx.a)
  target_link_libraries(mfpr ${CMAKE_SOURCE_DIR}/libs/a/libmx.a)
endif()  

target_include_directories(mfpr 
	PRIVATE "${CMAKE_SOURCE_DIR}/libs/mx/Sourcecode/include/")
target_include_directories(tests 
	PRIVATE "${CMAKE_SOURCE_DIR}/libs/mx/Sourcecode/include/")
