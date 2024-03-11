if (UNIX)
	set(MFPR_PATH ${CMAKE_BINARY_DIR}/mfpr)
else(MSVC)
	set(MFPR_PATH ${CMAKE_BINARY_DIR}/Release/mfpr)
endif()

execute_process(
		COMMAND ${MFPR_PATH} -t 2 -o ${CMAKE_BINARY_DIR}/A_W_sps_two_one.csv --csv --shortest-path=0 
			../tests/cases/A_W.xml
	       )
execute_process(
		COMMAND ${MFPR_PATH} -t 2 -o ${CMAKE_BINARY_DIR}/A_W_sps_two_two.csv --csv --shortest-path=1
			../tests/cases/A_W.xml
	       )
execute_process(
		COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol 
			${CMAKE_BINARY_DIR}/A_W_sps_two_one.csv
			../tests/outputs/A_W_sps_two.csv RESULT_VARIABLE res_one
	       )
execute_process(
		COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol 
			${CMAKE_BINARY_DIR}/A_W_sps_two_two.csv
			../tests/outputs/A_W_sps_two.csv RESULT_VARIABLE res_two
	       )

file(REMOVE ${CMAKE_BINARY_DIR}/A_W_sps_two_one.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/A_W_sps_two_two.csv)

if (res_one AND res_two)
	if (res_one) 
		message("csv non-match for sps opt = 0")
	else ()
		message("csv non-match for sps opt = 1")
	endif()
else ()
	message("csv match")
endif()

