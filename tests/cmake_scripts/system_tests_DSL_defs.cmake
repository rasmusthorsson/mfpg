if (UNIX)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/mfpg)
else(MSVC)
	set(MFPG_PATH ${CMAKE_BINARY_DIR}/Release/mfpg)
endif()

execute_process(
	COMMAND ${MFPG_PATH} -d ../resources/dsl_files/DSL_test_configuration_defs.mfpg -o ${CMAKE_BINARY_DIR}/A_D_o_F_DSL_defs.csv --csv --shortest-path=2
			../tests/cases/A_D_o_F.xml)

execute_process(
	COMMAND ${MFPG_PATH} -d ../resources/dsl_files/DSL_test_configuration_defs.mfpg -o ${CMAKE_BINARY_DIR}/A_W_DSL_defs.csv --csv --shortest-path=2
			../tests/cases/A_W.xml)


execute_process(
	COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_BINARY_DIR}/A_W_DSL_defs.csv
	../tests/outputs/A_W_defs.csv RESULT_VARIABLE A_W_res)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_BINARY_DIR}/A_D_o_F_defs.csv
	../tests/outputs/A_D_o_F_DSL_defs.csv RESULT_VARIABLE A_D_o_F_res)

file(REMOVE ${CMAKE_BINARY_DIR}/A_D_o_F_DSL_defs.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/A_W_DSL_defs.csv)

if (NOT A_D_o_F_res) 
	if (NOT A_W_res)
		message("csv match")
	else ()
		message("csv non-match on A_D_o_F")
	endif()
else()
	message("csv non-match on A_W")
endif()
