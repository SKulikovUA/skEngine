file(GLOB SRC "*.cpp")

include_directories(
                    ${PROJECT_SOURCE_DIR}/externals/glew/include
                    )
add_library(src STATIC ${SRC})
