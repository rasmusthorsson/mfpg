execute_process(
	COMMAND ${CMAKE_BINARY_DIR}/mfpr -o ${CMAKE_BINARY_DIR}/A_D_o_F.csv --csv 
		--greedy ../resources/A_D_o_F.xml
)
execute_process(
	COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
		${CMAKE_BINARY_DIR}/A_D_o_F.csv
		../resources/tests/A_D_o_F.csv RESULT_VARIABLE res
)

file(REMOVE ${CMAKE_BINARY_DIR}/A_D_o_F.csv)

if (res)
	message("csv non-match")
else ()
	message("csv match")
endif()

