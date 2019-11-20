file(GLOB SRC "*.cpp")

set(DEF_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/externals/glfw/include/
							${PROJECT_SOURCE_DIR}/externals/glm/
							${PROJECT_SOURCE_DIR}/externals/glew/include/
							${PROJECT_SOURCE_DIR}/externals/gli/
							${PROJECT_SOURCE_DIR}/externals/stb/
						)
          
if(NOT MSVC)
	include_directories(
						${DEF_INCLUDE_DIRECTORIES}
						)
else(NOT MSVC)
	include_directories(
						${PROJECT_SOURCE_DIR}/externals/assimp/include/
						${DEF_INCLUDE_DIRECTORIES}
						)
endif(NOT MSVC)

add_library(src STATIC ${SRC})
