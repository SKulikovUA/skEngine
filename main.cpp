#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>

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
#include "src/glTexture.h"
#include "src/Model.h"

struct vertex
{
   glm::vec3 mPosition;
   glm::vec3 mNormal;
   glm::vec2 mTexCoords;
};

std::ostream &operator<<(std::ostream &os, const glm::mat3 &m)
{
   os << "[" << m[0][0] << "," << m[0][1] << "," << m[0][2] << "]" << std::endl;
   os << "[" << m[1][0] << "," << m[1][1] << "," << m[1][2] << "]" << std::endl;
   os << "[" << m[2][0] << "," << m[2][1] << "," << m[2][2] << "]" << std::endl;
   return os;
}

std::ostream &operator<<(std::ostream &os, const glm::mat4 &m)
{
   os << "[" << m[0][0] << "," << m[0][1] << "," << m[0][2] << ", " << m[0][3] << "]" << std::endl;
   os << "[" << m[1][0] << "," << m[1][1] << "," << m[1][2] << ", " << m[0][3] << "]" << std::endl;
   os << "[" << m[2][0] << "," << m[2][1] << "," << m[2][2] << ", " << m[0][3] << "]" << std::endl;
   os << "[" << m[3][0] << "," << m[3][1] << "," << m[3][2] << ", " << m[3][3] << "]" << std::endl;
   return os;
}

std::ostream &operator<<(std::ostream &os, const glm::vec4 &v)
{
   std::cout << "Vec4: "
             << "x=" << v.x << " y=" << v.y << " z=" << v.z << " w=" << v.w << std::endl;
   return os;
}

void errorCallback(int, const char *err)
{
   std::cerr << err << std::endl;
}

void setupMatrices(GLFWwindow* win, IShaderProgram* shader)
{
   if(win != nullptr)
   {
      int w,h;
      glfwGetFramebufferSize(win, &w, &h);
      glViewport(0, 0, w, h);
      float aspect = static_cast<float>(w) / static_cast<float>(h);
      glm::mat4x4 projMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.001f, 100000.0f);
      glm::vec3 viewPos(0.0f, 0.0f, 15.0f);
      glm::mat4x4 viewMatrix = glm::lookAt(
         viewPos, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      glm::mat4x4 model = glm::mat4x4(1.0f);
      model = glm::translate(model, glm::vec3(0.0f, -1.75f, 10.0f)); // translate it down so it's at the center of the scene
      model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

      shader->setUniformValue(std::string("projection"), projMatrix);
      shader->setUniformValue(std::string("view"), viewMatrix);
      shader->setUniformValue(std::string("model"), model);
      glm::vec3 lightPos(viewPos);
      shader->setUniformValue(std::string("lightPos"), lightPos);
      shader->setUniformValue(std::string("viewPos"), viewPos);
   }
}

int main()
{
#if 0
    std::cout << offsetof(vertex, mPosition) << std::endl;
    std::cout << offsetof(vertex, mNormal) << std::endl;
    std::cout << offsetof(vertex, mTexCoords) << std::endl;


    std::string ext;
    while(std::getline(strstream, ext, ';'))
    {
        std::cout << ext << std::endl;
    }

   glTexture tex(GL_TEXTURE_2D);
   tex.loadFromFile("../assets/textures/gridlines.ktx");
#endif
   if (glfwInit() == GLFW_FALSE)
   {
      std::cerr << "GLFW init failed";
      return EXIT_FAILURE;
   }
   glfwSetErrorCallback(errorCallback);

   glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow *window = glfwCreateWindow(1280, 720, "SK Engine", nullptr, nullptr);
   if (window == nullptr)
   {
      glfwTerminate();
      return EXIT_FAILURE;
   }
   glfwMakeContextCurrent(window);

   GLenum error = glewInit();
   if (error != GLEW_OK)
   {
      std::cerr << "GLEW init failed: " << glewGetErrorString(error) << std::endl;
      glfwTerminate();
      return EXIT_FAILURE;
   }

   std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

   std::unique_ptr<IShaderProgram> shaderProgram = std::make_unique<GLSLProgram>();
   if (shaderProgram != nullptr)
   {
      bool result = shaderProgram->attachShader(GL_VERTEX_SHADER, "../assets/shaders/test.vert");
      if (!result)
      {
         std::cout << shaderProgram->getErrorDescription() << std::endl;
      }

      result = shaderProgram->attachShader(GL_FRAGMENT_SHADER, "../assets/shaders/test.frag");
      if (!result)
      {
         std::cout << shaderProgram->getErrorDescription() << std::endl;
      }

      result = shaderProgram->linkProgramm();
      if (!result)
      {
         std::cout << shaderProgram->getErrorDescription();
      }
   }

   glClearColor(0.0f, 0.0f, 0.15f, 1.0f);

   std::unique_ptr<Model> pModel = std::make_unique<Model>();
   if (pModel)
   {
      VertexAttributeFormat fmt =
          VertexAttributeFormat(
             {VertexComponent::VF_POSITION,
             VertexComponent::VF_NORMAL});
      if (pModel->loadFromFile(std::string("../assets/models/nanosuit.obj"), &fmt))
      {
         std::cout << "Model loaded" << std::endl;
         std::cout << "Vertex format stride : " << fmt.stride() << std::endl;
      }
      else
      {
         std::cout << "Failed to load model" << std::endl;
      }
   }

   while (!glfwWindowShouldClose(window))
   {
      glfwPollEvents();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_CULL_FACE);
      //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glEnable(GL_DEPTH_TEST);
      if(pModel != nullptr && shaderProgram != nullptr)
      {
         shaderProgram->bind();
         setupMatrices(window, shaderProgram.get());
         pModel->draw();
         shaderProgram->unbind();
      }
      glfwSwapBuffers(window);
   }
   glfwTerminate();
   return EXIT_SUCCESS;
}
