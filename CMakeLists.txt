CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

find_package(CmakeFuncs REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/CmakeFuncs/")


get_current_dir_name(prject_name ${CMAKE_CURRENT_SOURCE_DIR})
message("============ ${prject_name}")
message("name =" ${prject_name})
project(${prject_name} VERSION 0.1 LANGUAGES CXX)
message("============ ${CURRENT_FOLDER}")

SET( QT_VERSION_MAJOR 6 )
SET( DEPLOY_QT_HOME "C:/Qt/6.4.2/msvc2019_64/" )
SET( Qt6_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt6" )
SET( Qt6CoreTools_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt6CoreTools")
SET( Qt6GuiTools_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt6GuiTools" )

SET( OpenCV_DIR "C:/libs/opencv/build/")

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR} )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR} )
SET( CMAKE_INSTALL_BINDIR ./)
SET( CMAKE_INSTALL_LIBDIR ./)
SET( CMAKE_INSTALL_PREFIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

SET( CMAKE_AUTOUIC ON )
SET( CMAKE_AUTOMOC ON )
SET( CMAKE_AUTORCC ON )

## 添加 cv 包
FIND_PACKAGE(OpenCV REQUIRED)
## 包含 cv 头文件
include_directories(${OpenCV_INCLUDE_DIRS}) 

get_current_path_dirs(out_path_list ${CMAKE_CURRENT_SOURCE_DIR}/src/uis "CMakeLists.txt")
get_current_path_dirs(out_path_list ${CMAKE_CURRENT_SOURCE_DIR}/src/libs "CMakeLists.txt")
foreach(out_dir ${out_path_list})
	string(REPLACE ${CMAKE_SOURCE_DIR}/ "./" out_path ${out_dir})
	message(STATUS "正在添加路径 :\t" ${out_path})
	ADD_SUBDIRECTORY(${out_path})
endforeach()


message("CMAKE_RUNTIME_OUTPUT_DIRECTORY = " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY = " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

message("CMAKE_INSTALL_BINDIR = " ${CMAKE_INSTALL_BINDIR})
message("CMAKE_INSTALL_LIBDIR = " ${CMAKE_INSTALL_LIBDIR})

message("CMAKE_INSTALL_PREFIX = " ${CMAKE_INSTALL_PREFIX})
message("EXECUTABLE_OUTPUT_PATH = " ${EXECUTABLE_OUTPUT_PATH})
