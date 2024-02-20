if (UNIX)
	set(MFPR_PATH ${CMAKE_BINARY_DIR}/mfpr)
else(MSVC)
	set(MFPR_PATH ${CMAKE_BINARY_DIR}/Release/mfpr)
endif()

execute_process(
	COMMAND ${MFPR_PATH} -t 1 -o ${CMAKE_BINARY_DIR}/A_D_o_F.csv --csv --greedy 
		../tests/cases/A_D_o_F.xml)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_BINARY_DIR}/A_D_o_F.csv
		../tests/outputs/A_D_o_F.csv RESULT_VARIABLE res)

file(REMOVE ${CMAKE_BINARY_DIR}/A_D_o_F.csv)

if (res)
	message("csv non-match")
else ()
	message("csv match")
endif()

