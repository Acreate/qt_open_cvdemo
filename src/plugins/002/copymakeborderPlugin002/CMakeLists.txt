get_current_dir_name(prject_name ${CMAKE_CURRENT_SOURCE_DIR})
message("============ ${prject_name}")
message("name =" ${prject_name})
project(${prject_name}  VERSION 0.1 LANGUAGES CXX)
message("============ ${CURRENT_FOLDER}")

## 插件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../openCVInterface002) 

## 特别的输出
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/cvplugins/ )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/cvplugins/ )

# 当前目录下也有代码
FILE(GLOB SRC_LIST "*.cpp" "*.c" "*.hpp" "*.h" "*.ui" )

## add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
qt_add_plugin(${PROJECT_NAME} 
    CLASS_NAME ${PROJECT_NAME} 
)
target_sources(${PROJECT_NAME}  PRIVATE
    ${SRC_LIST}
)

target_link_libraries(
	${PROJECT_NAME} 
	PRIVATE 
		Qt${QT_VERSION_MAJOR}::Core
		Qt${QT_VERSION_MAJOR}::Widgets
		openCVInterface002
		${OpenCV_LIBS}
)

STRING(SUBSTRING "${PROJECT_NAME}" 0 1 exportFileStartName)
STRING(SUBSTRING "${PROJECT_NAME}" 1 -1 exportFileName)
STRING(TOUPPER ${exportFileStartName} exportFileStartName)
SET(exportFileName ${CMAKE_CURRENT_SOURCE_DIR}/${exportFileStartName}${exportFileName}_export.h)
GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
	EXPORT_FILE_NAME 
		${exportFileName} 
)
TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
