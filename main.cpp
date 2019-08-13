#include <iostream>
#include <sstream>
#include <string>
#include <memory>

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
#include "src/glTexture2D.h"

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


void errorCallback(int, const char* err)
{
    std::cerr << err << std::endl;
}

int main()
{
    Assimp::Importer importer;

    std::string extensions;
    importer.GetExtensionList(extensions);
    std::istringstream strstream(extensions);
#if 0
    std::cout << offsetof(vertex, mPosition) << std::endl;
    std::cout << offsetof(vertex, mNormal) << std::endl;
    std::cout << offsetof(vertex, mTexCoords) << std::endl;


    std::string ext;
    while(std::getline(strstream, ext, ';'))
    {
        std::cout << ext << std::endl;
    }
#endif
    glTexture tex;
    tex.loadFromFile("./../textures/gridlines.ktx");  

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

    GLFWwindow* window = glfwCreateWindow(1280, 720, "SK Engine", nullptr, nullptr);
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

    std::unique_ptr<IShaderProgram> shaderProgram(new GLSLProgram);
    if(shaderProgram != nullptr)
    {
        bool result = shaderProgram->attachShader(GL_VERTEX_SHADER, "../shaders/test.vert");
        if(!result)
        {
            std::cout << shaderProgram->getErrorDescription() << std::endl;
        }

        result = shaderProgram->attachShader(GL_FRAGMENT_SHADER, "../shaders/test.frag");
        if(!result)
        {
            std::cout << shaderProgram->getErrorDescription() << std::endl;
        }

        result = shaderProgram->linkProgramm();
        if(!result)
        {
            std::cout << shaderProgram->getErrorDescription();
        }

        std::cout << shaderProgram->getUniformLocation("cameraPos") << std::endl;
        std::cout << shaderProgram->getUniformLocation("someUniform") << std::endl;
    }
    
    glClearColor(0.0f, 0.0f, 0.15f, 1.0f);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return EXIT_SUCCESS;
}
