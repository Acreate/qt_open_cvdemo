
get_current_dir_name( prject_name ${CMAKE_CURRENT_SOURCE_DIR} )
message( "============ ${prject_name}" )
message( "name =" ${prject_name} )
project( ${prject_name} VERSION 0.1 LANGUAGES CXX )
message( "============ ${CURRENT_FOLDER}" )

# # 插件的头文件
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins/001/openCVInterface001 )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../plugins/002/openCVInterface002 )

# 当前目录下也有代码
FILE( GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h" "*.ui" )

if( ${QT_VERSION_MAJOR} GREATER_EQUAL 6 )
	qt_add_executable( ${PROJECT_NAME}
		MANUAL_FINALIZATION
		${SRC_LIST}
	)
else()
	if( ANDROID )
		add_library( ${PROJECT_NAME} SHARED
			${SRC_LIST}
		)
	else()
		add_executable( ${PROJECT_NAME} ${SRC_LIST} )
	endif()
endif()

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Core
	${OpenCV_LIBS}
)
add_dependencies( ${PROJECT_NAME}
	openCVInterface001
	medianFilterPlugin001
	openCVInterface002
	colorPlugin002
	copymakeborderPlugin002
	filterPlugin002
	fourierPlugin002
	segmentationPlugin002
	templatePlugin002
	transformPlugin002
)

set_target_properties( ${PROJECT_NAME} PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

if( QT_VERSION_MAJOR EQUAL 6 )
	qt_finalize_executable( ${PROJECT_NAME} )
endif()

add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:opencv_world> "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)


#  DLL 复制
set_target_properties(${PROJECT_NAME}  PROPERTIES
     WIN32_EXECUTABLE TRUE
     MACOSX_BUNDLE TRUE
)


set( MY_APP ${PROJECT_NAME} )

if( APPLE )
	set( executable_path "$<TARGET_FILE_NAME:${MY_APP}>.app" )
else()
	set( executable_path "\${QT_DEPLOY_BIN_DIR}/$<TARGET_FILE_NAME:${MY_APP}>" )
endif()

set( deploy_script "${CMAKE_CURRENT_BINARY_DIR}/deploy_${MY_APP}.cmake" )

file( GENERATE OUTPUT ${deploy_script} CONTENT "
message(\"=================\")
message(\"============	> 执行 : ${executable_path}\")
message(\"=================\")
include(\"${QT_DEPLOY_SUPPORT}\")
qt_deploy_runtime_dependencies(
    EXECUTABLE \"${executable_path}\"
    PLUGINS_DIR bin
)
" )
install( TARGETS ${MY_APP} DESTINATION bin )
install( SCRIPT ${deploy_script} )
