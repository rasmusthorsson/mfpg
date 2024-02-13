cmake_minimum_required(VERSION 3.17)

if(REBUILD_MX)
  target_link_libraries(tests mx cxxopts)
  target_link_libraries(mfpr mx cxxopts)
else()
  if (UNIX)
    target_link_libraries(tests ${CMAKE_SOURCE_DIR}/deps/a/libmx.a cxxopts)
    target_link_libraries(mfpr ${CMAKE_SOURCE_DIR}/deps/a/libmx.a cxxopts)
  elseif(MSVC)
    target_link_libraries(tests ${CMAKE_SOURCE_DIR}/deps/a/mx_r.lib cxxopts)
    target_link_libraries(mfpr ${CMAKE_SOURCE_DIR}/deps/a/mx_r.lib cxxopts)
  endif()
endif()  

target_include_directories(mfpr 
	PRIVATE "${CMAKE_SOURCE_DIR}/deps/mx/Sourcecode/include/")
target_include_directories(tests 
	PRIVATE "${CMAKE_SOURCE_DIR}/deps/mx/Sourcecode/include/")
