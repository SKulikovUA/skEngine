#include <iostream>
#include <sstream>
#include <string>

#include <assimp/Importer.hpp>

#ifdef _WIN32
    #define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/matrix.hpp>

#include "src/glslprogram.h"
#include "src/shader.h"

struct vertex
{
    glm::vec3 mPosition;
    glm::vec3 mNormal;
    glm::vec2 mTexCoords;
};

std::ostream& operator << (std::ostream& os, const glm::mat3& m)
{
    os << "[" << m[0][0] << "," << m[0][1] << "," << m[0][2] << "]" <<std::endl;
    os << "[" << m[1][0] << "," << m[1][1] << "," << m[1][2] << "]" <<std::endl;
    os << "[" << m[2][0] << "," << m[2][1] << "," << m[2][2] << "]" <<std::endl;
    return os;
}

std::ostream& operator << (std::ostream& os, const glm::mat4& m)
{
    os << "[" << m[0][0] << "," << m[0][1] << "," << m[0][2] << ", " << m[0][3] << "]" <<std::endl;
    os << "[" << m[1][0] << "," << m[1][1] << "," << m[1][2] << ", " << m[0][3] << "]" <<std::endl;
    os << "[" << m[2][0] << "," << m[2][1] << "," << m[2][2] << ", " << m[0][3] << "]" <<std::endl;
    os << "[" << m[3][0] << "," << m[3][1] << "," << m[3][2] << ", " << m[3][3] << "]" <<std::endl;
    return os;
}

std::ostream& operator << (std::ostream& os, const glm::vec4& v)
{
    std::cout << "Vec4: " << "x=" << v.x << " y=" << v.y << " z=" << v.z <<" w="<< v.w << std::endl;
    return os;
}
void testMath()
{
    glm::vec2 v1(1.0f, 2.0f);
    glm::vec2 v2(5.0f, 0.0f);

    glm::vec2 v = v2 - v1;

    std::cout << v.x << ","<< v.y << " Length:"<< glm::distance(v2, v1) << std::endl;

    glm::vec4 v3(2.0f, 3.0f, 4.0f, 5.0f);
    glm::mat4 m = glm::mat4(1.0f);
    std::cout << m << v3;
    std::cout << v3 * m;
}

void errorCallback(int, const char* err)
{
    std::cerr << err << std::endl;
}

int main()
{
    testMath();
    Assimp::Importer importer;

    std::string extensions;
    importer.GetExtensionList(extensions);
    std::istringstream strstream(extensions);

    std::cout << offsetof(vertex, mPosition) << std::endl;
    std::cout << offsetof(vertex, mNormal) << std::endl;
    std::cout << offsetof(vertex, mTexCoords) << std::endl;

#if 0
    std::string ext;
    while(std::getline(strstream, ext, ';'))
    {
        std::cout << ext << std::endl;
    }
#endif
    if(glfwInit() == GLFW_FALSE)
    {
        std::cerr << "GLFW init failed";
        return EXIT_FAILURE;
    }
    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Model converter", nullptr, nullptr);
    if(window == nullptr)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    GLenum error = glewInit();
    if(error != GLEW_OK)
    {
        std::cerr << "GLEW init failed: " << glewGetErrorString(error) << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    if(GLEW_ARB_get_program_binary)
    {
        std::cout << "Support binary shaders" << std::endl;
    }

    Shader vShader(GL_VERTEX_SHADER);
    std::string errorString;
    vShader.loadFromFile("./shaders/test.vert", errorString);
    std::cout << errorString;

    Shader fShader(GL_FRAGMENT_SHADER);
    GLSLProgram shaderProgram;

    glClearColor(0.0f, 0.0f, 0.75f, 1.0f);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return EXIT_SUCCESS;
}
