if (UNIX)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/mfpg)
else(MSVC)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/Release/mfpg)
endif()

execute_process(
		COMMAND ${MFPG_PATH} -t 1 -o ${CMAKE_BINARY_DIR}/A_W_tls_one.csv --format=csv --tls-solver
			../tests/cases/A_W.xml
	       )
execute_process(
		COMMAND ${MFPG_PATH} -t 2 -o ${CMAKE_BINARY_DIR}/A_W_tls_two.csv --format=csv --tls-solver
			../tests/cases/A_W.xml
	       )
execute_process(
		COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol 
			${CMAKE_BINARY_DIR}/A_W_tls_one.csv
			../tests/outputs/A_W_tls_one.csv RESULT_VARIABLE res_one
	       )
execute_process(
		COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol 
			${CMAKE_BINARY_DIR}/A_W_tls_two.csv
			../tests/outputs/A_W_tls_two.csv RESULT_VARIABLE res_two
	       )

file(REMOVE ${CMAKE_BINARY_DIR}/A_W_tls_one.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/A_W_tls_two.csv)

if (res_one AND res_two)
	if (res_one) 
		message("csv non-match for tls one")
	else ()
		message("csv non-match for tls two")
	endif()
else ()
	message("csv match")
endif()

