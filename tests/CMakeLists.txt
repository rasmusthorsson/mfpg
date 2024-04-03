
cmake_minimum_required(VERSION 3.17)

if(REBUILD_MX)
  target_link_libraries(tests_mfpg mx cxxopts)
else()
  if (UNIX)
    target_link_libraries(tests_mfpg ${CMAKE_SOURCE_DIR}/deps/a/libmx.a cxxopts)
  elseif(MSVC)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
     target_link_libraries(tests_mfpg ${CMAKE_SOURCE_DIR}/deps/a/mx_64.lib cxxopts)
    elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
      target_link_libraries(tests_mfpg ${CMAKE_SOURCE_DIR}/deps/a/mx_r.lib cxxopts)
    endif()
  endif()
endif()  

target_include_directories(tests_mfpg 
	PRIVATE "${CMAKE_SOURCE_DIR}/deps/mx/Sourcecode/include/")
target_include_directories(tests_mfpg 
	PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_include_directories(tests_mfpg 
	PRIVATE "${CMAKE_SOURCE_DIR}/src/parser")
