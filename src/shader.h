#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
    enum class SHADER_TYPE
    {
        UNKNOWN = -1,
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        TESSELATION_CONTROL,
        TESSELATION_EVAL,
        COMPUTE
    };
public:
    Shader(const SHADER_TYPE type, const std::string& fileName);

private:
    const SHADER_TYPE mShaderType;
    GLuint mShaderHandle;
};

