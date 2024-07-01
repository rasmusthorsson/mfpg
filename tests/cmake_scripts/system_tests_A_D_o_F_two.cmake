if (UNIX)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/mfpg)
else(MSVC)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/Release/mfpg)
endif()

execute_process(
	COMMAND ${MFPG_PATH} -t 2 -o ${CMAKE_BINARY_DIR}/A_D_o_F_two.csv --format=csv --greedy 
		../tests/cases/A_D_o_F.xml)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_BINARY_DIR}/A_D_o_F_two.csv 
		../tests/outputs/A_D_o_F_two.csv RESULT_VARIABLE res)

file(REMOVE ${CMAKE_BINARY_DIR}/A_D_o_F_two.csv)

if (res)
	message("csv non-match")
else ()
	message("csv match")
endif()

