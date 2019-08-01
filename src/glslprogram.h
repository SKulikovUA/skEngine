#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

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

