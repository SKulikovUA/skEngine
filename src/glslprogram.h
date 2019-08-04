#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

#include <glm/glm.hpp>

class GLSLProgram
{
public:
    static constexpr int INFO_LOG_LENGTH = 512;

public:
    GLSLProgram();
    ~GLSLProgram();

    bool attachShader(GLenum shaderType, const std::string& fileName);
    bool linkProgramm();
    const std::string& getErrorDescription() const;
    void bind();
    void unbind();

    //Uniforms
    int getUniformLocation(const std::string& name);
    bool setUniformValue(const std::string& name, const bool value);
    bool setUniformValue(const std::string& name, const int value);
    bool setUniformValue(const std::string& name, const GLuint value);
    bool setUniformValue(const std::string& name, const float value);
    bool setUniformValue(const std::string& name, const glm::vec2& value);
    bool setUniformValue(const std::string& name, const glm::vec3& value);
    bool setUniformValue(const std::string& name, const glm::vec4& value);
    bool setUniformValue(const std::string& name, const glm::mat2& value);
    bool setUniformValue(const std::string& name, const glm::mat3& value);
    bool setUniformValue(const std::string& name, const glm::mat4& value);


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
    GLuint mProgramHandle;
    std::string mErrorDescription;
};

