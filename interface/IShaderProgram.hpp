#pragma once

#include <string>
#include <GL/gl.h>
#include <glm/glm.hpp>

class IShaderProgram
{
public:

    virtual ~IShaderProgram()
    {
    }

    virtual bool attachShader(GLenum shaderType, const std::string& fileName) = 0;
    virtual bool linkProgramm() = 0;
    virtual const std::string& getErrorDescription() const = 0;
    virtual void bind() = 0;
    virtual void unbind() = 0;

    //Uniforms
    virtual int getUniformLocation(const std::string& name) = 0;
    virtual bool setUniformValue(const std::string& name, const bool value) = 0;
    virtual bool setUniformValue(const std::string& name, const int value) = 0;
    virtual bool setUniformValue(const std::string& name, const GLuint value) = 0;
    virtual bool setUniformValue(const std::string& name, const float value)= 0;
    virtual bool setUniformValue(const std::string& name, const glm::vec2& value) = 0;
    virtual bool setUniformValue(const std::string& name, const glm::vec3& value) = 0;
    virtual bool setUniformValue(const std::string& name, const glm::vec4& value) = 0;
    virtual bool setUniformValue(const std::string& name, const glm::mat2& value) = 0;
    virtual bool setUniformValue(const std::string& name, const glm::mat3& value) = 0;
    virtual bool setUniformValue(const std::string& name, const glm::mat4& value) = 0;
};
