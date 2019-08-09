#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include "../interface/IShaderProgram.hpp"

class GLSLProgram : public IShaderProgram
{
public:
    GLSLProgram();
    virtual ~GLSLProgram();

    virtual bool attachShader(GLenum shaderType, const std::string& fileName);
    virtual bool linkProgramm();
    virtual const std::string& getErrorDescription() const;
    virtual void bind();
    virtual void unbind();

    //Uniforms
    virtual int getUniformLocation(const std::string& name);
    virtual bool setUniformValue(const std::string& name, const bool value);
    virtual bool setUniformValue(const std::string& name, const int value);
    virtual bool setUniformValue(const std::string& name, const GLuint value);
    virtual bool setUniformValue(const std::string& name, const float value);
    virtual bool setUniformValue(const std::string& name, const glm::vec2& value);
    virtual bool setUniformValue(const std::string& name, const glm::vec3& value);
    virtual bool setUniformValue(const std::string& name, const glm::vec4& value);
    virtual bool setUniformValue(const std::string& name, const glm::mat2& value);
    virtual bool setUniformValue(const std::string& name, const glm::mat3& value);
    virtual bool setUniformValue(const std::string& name, const glm::mat4& value);


private:
    class Shader
    {
    public:
        Shader(const GLenum type);
        ~Shader();
        bool loadFromFile(const std::string& fileName, std::string& error);

        //Forbid copy
        Shader(const Shader&) = delete;
        Shader& operator = (const Shader&) = delete;

        GLenum shaderType() const;
        GLuint shaderHandle() const;

    private:
        bool readCodeFromFile(const std::string& fileName, std::string& shaderCode);

    private:
        const GLenum mShaderType;
        GLuint mShaderHandle;
    };

private:
    GLuint mProgramHandle {0};
    std::string mErrorDescription;
};

