if (UNIX)
	set(MFPR_PATH ${CMAKE_BINARY_DIR}/mfpr)
else(MSVC)
	set(MFPR_PATH ${CMAKE_BINARY_DIR}/Release/mfpr)
endif()

execute_process(
	COMMAND ${MFPR_PATH} -t 1 -o ${CMAKE_BINARY_DIR}/A_D_o_F_config.csv --csv --greedy
			../tests/cases/A_D_o_F.xml)

execute_process(
	COMMAND ${MFPR_PATH} -t 1 -o ${CMAKE_BINARY_DIR}/A_W_config.csv --csv --greedy
			../tests/cases/A_W.xml)

execute_process(
	COMMAND ${MFPR_PATH} -d ../resources/dsl_files/DSL_test_configuration_1.mfpg -o ${CMAKE_BINARY_DIR}/A_D_o_F_DSL.csv --csv --greedy
			../tests/cases/A_D_o_F.xml)

execute_process(
	COMMAND ${MFPR_PATH} -d ../resources/dsl_files/DSL_test_configuration_1.mfpg -o ${CMAKE_BINARY_DIR}/A_W_DSL.csv --csv --greedy
			../tests/cases/A_W.xml)

execute_process(
	COMMAND ${MFPR_PATH} -d ../resources/dsl_files/DSL_test_configuration_1.mfpg -o ${CMAKE_BINARY_DIR}/A_W_DSL_sps.csv --csv --shortest-path=2
			../tests/cases/A_W.xml)

execute_process(
	COMMAND ${MFPR_PATH} -t 1 -o ${CMAKE_BINARY_DIR}/A_W_config_sps.csv --csv --shortest-path=2
			../tests/cases/A_W.xml)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_BINARY_DIR}/A_D_o_F_config.csv ${CMAKE_BINARY_DIR}/A_D_o_F_DSL.csv RESULT_VARIABLE A_D_o_F_res)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_BINARY_DIR}/A_W_config.csv ${CMAKE_BINARY_DIR}/A_W_DSL.csv RESULT_VARIABLE A_W_res)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_BINARY_DIR}/A_W_config_sps.csv ${CMAKE_BINARY_DIR}/A_W_DSL_sps.csv RESULT_VARIABLE A_W_sps_res)

file(REMOVE ${CMAKE_BINARY_DIR}/A_D_o_F_DSL.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/A_D_o_F_config.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/A_W_DSL.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/A_W_config.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/A_W_DSL_sps.csv)
file(REMOVE ${CMAKE_BINARY_DIR}/A_W_config_sps.csv)

if (NOT A_D_o_F_res) 
	if (NOT A_W_res)
		if (NOT A_W_sps_res)
			message("csv match")
		else()
			message("csv non-match on A_W_sps")
		endif()
	else ()
		message("csv non-match on A_D_o_F")
	endif()
else()
	message("csv non-match on A_W")
endif()
