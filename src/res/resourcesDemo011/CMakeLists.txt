
message("============ ${CURRENT_FOLDER}")
STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
message("name =" ${CURRENT_FOLDER})
project(${CURRENT_FOLDER}  VERSION 0.1 LANGUAGES CXX)
message("============ ${CURRENT_FOLDER}")

execute_process(
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/themes/Dark.thm" "${EXECUTABLE_OUTPUT_PATH}/themes/Dark.thm"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/themes/Light.thm" "${EXECUTABLE_OUTPUT_PATH}/themes/Light.thm"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/languages/Turkish - TR.qm" "${EXECUTABLE_OUTPUT_PATH}/languages/Turkish - TR.qm" 
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/themes/Light.thm" "${EXECUTABLE_OUTPUT_PATH}/themes/Light.thm"
)
