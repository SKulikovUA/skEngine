#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{

public:
    Shader(const GLenum type);
    ~Shader();
    bool loadFromFile(const std::string& fileName, std::string& error);

    //Forbid copy
    Shader(const Shader&) = delete;
    Shader& operator = (const Shader&) = delete;



private:
    bool readCodeFromFile(const std::string& fileName);

private:
    const GLenum mShaderType;
    GLuint mShaderHandle;
    std::string mFileName;
};

