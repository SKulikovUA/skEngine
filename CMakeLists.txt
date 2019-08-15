cmake_minimum_required(VERSION 2.8)

project(skEngine)

option(BUILD_SHARED_LIBS OFF)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/externals/assimp)

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

include_directories(
                    ${PROJECT_SOURCE_DIR}/externals/assimp/include/
                    ${PROJECT_SOURCE_DIR}/externals/glfw/include/
                    ${PROJECT_SOURCE_DIR}/externals/glm/
                    ${PROJECT_SOURCE_DIR}/externals/glew/include
                    ${PROJECT_SOURCE_DIR}/externals/gli/gli
                    ${PROJECT_SOURCE_DIR}/externals/stb/
                    )

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} src assimp glfw libglew_static)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif(WIN32)

