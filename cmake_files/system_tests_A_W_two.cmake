execute_process(
		COMMAND ${CMAKE_BINARY_DIR}/mfpr -t 2 -o ${CMAKE_BINARY_DIR}/A_W_two.csv 
		--csv --greedy ../resources/A_W.xml
	       )
execute_process(
		COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
		${CMAKE_BINARY_DIR}/A_W_two.csv
		../resources/tests/A_W_two.csv RESULT_VARIABLE res
	       )

file(REMOVE ${CMAKE_BINARY_DIR}/A_W_two.csv)

if (res)
	message("csv non-match")
else ()
	message("csv match")
endif()

