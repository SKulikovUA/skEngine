cmake_minimum_required(VERSION 3.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_PROJECT_VERSION)

if( NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Release)
endif()

project(skEngine)

if(NOT MSVC)
    find_package(ASSIMP REQUIRED)
    set(OpenGL_GL_PREFERENCE GLVND)
else(NOT MSVC)
	find_library(ASSIMP_LIBRARIES NAMES assimp-vc141-mt PATHS ${CMAKE_SOURCE_DIR}/externals/assimp/lib/)
endif(NOT MSVC)


option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_INSTALL OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/externals/glfw)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/externals/bullet3d)

add_subdirectory(${PROJECT_SOURCE_DIR}/externals/glew)
add_subdirectory(src)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11 -g")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif(NOT WIN32)
endif(MSVC)

set(DEF_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/externals/glfw/include/
							${PROJECT_SOURCE_DIR}/externals/glm/
							${PROJECT_SOURCE_DIR}/externals/glew/include/
							${PROJECT_SOURCE_DIR}/externals/gli/
							${PROJECT_SOURCE_DIR}/externals/stb/
						)
if(NOT MSVC)
	include_directories( ${DEF_INCLUDE_DIRECTORIES} )
else(NOT MSVC)
	include_directories(
						${DEF_INCLUDE_DIRECTORIES}
						${PROJECT_SOURCE_DIR}/externals/assimp/include/
						)
endif(NOT MSVC)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} src ${ASSIMP_LIBRARIES} glfw libglew_static)
if(MSVC)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif(MSVC)

#SET(B_T "")
string(TOLOWER ${CMAKE_BUILD_TYPE} B_T)
message(WARNING ${CMAKE_BUILD_TYPE})
if(${B_T} STREQUAL "debug")
	set(ASSIMP_LIBRARY_NAME "assimp-vc141-mtd.dll")
else()
	set(ASSIMP_LIBRARY_NAME "assimp-vc141-mt.dll")
endif()

message(WARNING ${ASSIMP_LIBRARY_NAME})

if(MSVC)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
  		COMMAND ${CMAKE_COMMAND} -E copy 
    	${CMAKE_CURRENT_SOURCE_DIR}/externals/assimp/bin/${ASSIMP_LIBRARY_NAME}
		${CMAKE_SOURCE_DIR}/bin

		COMMAND ${CMAKE_COMMAND} -E copy 
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}
		${CMAKE_SOURCE_DIR}/bin
	)

else(MSVC)
	add_custom_command(
  		TARGET ${PROJECT_NAME} POST_BUILD
  		COMMAND ${CMAKE_COMMAND} -E copy 
    	$<TARGET_FILE_DIR:${PROJECT_NAME}>
		$(CMAKE_SOURCE_DIR)/bin)
endif(MSVC)
