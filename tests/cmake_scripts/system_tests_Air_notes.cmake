if (UNIX)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/mfpg)
else(MSVC)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/Release/mfpg)
endif()

execute_process(
		COMMAND ${MFPG_PATH} -t 2 -o ${CMAKE_BINARY_DIR}/Air_notes_v1.csv --csv=NOTE --greedy 
			-i "Violin 1"
			../tests/cases/Air.xml
	       )
execute_process(
		COMMAND ${MFPG_PATH} -t 2 -o ${CMAKE_BINARY_DIR}/Air_notes_v2.csv --csv=NOTE --greedy 
			-i "Violin 2"
			../tests/cases/Air.xml
	       )

execute_process(
		COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_BINARY_DIR}/Air_notes_v1.csv
			../tests/outputs/Air_notes_v1.csv RESULT_VARIABLE res_one
	       )
execute_process(
		COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_BINARY_DIR}/Air_notes_v2.csv
			../tests/outputs/Air_notes_v2.csv RESULT_VARIABLE res_two
	       )

file(REMOVE ${CMAKE_BINARY_DIR}/Air_notes_v1.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/Air_notes_v2.csv)

if (res_one AND res_two)
	if (res_one) 
		message("csv non-match instrument violin 1")
	else ()
		message("csv non-match instrument violin 2")
	endif()
else ()
	message("csv match")
endif()

