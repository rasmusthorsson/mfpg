if (UNIX)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/mfpg)
else(MSVC)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/Release/mfpg)
endif()

execute_process(
		COMMAND ${MFPG_PATH} -t 2 -o ${CMAKE_BINARY_DIR}/Air_lines_v1.csv --csv --greedy 
			-i "Violin 1"
			../tests/cases/Air.xml
	       )
execute_process(
		COMMAND ${MFPG_PATH} -t 2 -o ${CMAKE_BINARY_DIR}/Air_lines_v2.csv --csv --greedy 
			-i "Violin 2"
			../tests/cases/Air.xml
	       )
execute_process(
		COMMAND wc -l ${CMAKE_BINARY_DIR}/Air_lines_v1.csv RESULT_VARIABLE res
	       )

file(REMOVE ${CMAKE_BINARY_DIR}/Air_lines_v1.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/Air_lines_v2.csv)

if (res EQUAL "196 Air_lines_v1.csv")
	message("line match")
else ()
	message("line non-match")
endif()

