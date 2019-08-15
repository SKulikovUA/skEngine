file(GLOB SRC "*.cpp")

include_directories(
                    ${PROJECT_SOURCE_DIR}/externals/glew/include
                    ${PROJECT_SOURCE_DIR}/externals/glm/
                    ${PROJECT_SOURCE_DIR}/externals/gli/
                    ${PROJECT_SOURCE_DIR}/externals/stb/
                    )
add_library(src STATIC ${SRC})
