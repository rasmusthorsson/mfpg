if (UNIX)
	set(MFPR_PATH ${CMAKE_BINARY_DIR}/mfpr)
else(MSVC)
	set(MFPR_PATH ${CMAKE_BINARY_DIR}/Release/mfpr)
endif()

execute_process(
	COMMAND ${MFPR_PATH} -t 2 -o ${CMAKE_BINARY_DIR}/CSV_Basic.csv --csv --shortest-path=2 --notemapper=../resources/dsl_files/BasicNoteMapper.csv
			../tests/cases/A_W.xml
	       )
execute_process(
		COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol 
		${CMAKE_BINARY_DIR}/CSV_Basic.csv
			../tests/outputs/A_W_sps_two.csv RESULT_VARIABLE res_one
	       )
file(REMOVE ${CMAKE_BINARY_DIR}/CSV_Basic.csv)

if (res_one)
	if (res_one) 
		message("Basic CSV not matched")
	endif()
else ()
	message("csv match")
endif()

