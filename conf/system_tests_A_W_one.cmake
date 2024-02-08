execute_process(
	COMMAND ${CMAKE_BINARY_DIR}/mfpr -o ${CMAKE_BINARY_DIR}/A_W.csv --csv --greedy
						../resources/A_W.xml
)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol
		${CMAKE_BINARY_DIR}/A_W.csv
		../resources/tests/A_W.csv RESULT_VARIABLE res
)

if (res)
	message("csv non-match")
else ()
	message("csv match")
endif()

