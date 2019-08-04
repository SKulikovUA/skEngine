#include "glslprogram.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

GLSLProgram::GLSLProgram()
{
    mProgramHandle = glCreateProgram();
}

GLSLProgram::~GLSLProgram()
{
    glDeleteProgram(mProgramHandle);
}

bool GLSLProgram::attachShader(GLenum shaderType, const std::string &fileName)
{
    bool result = false;
    if(mProgramHandle != 0)
    {
        Shader shader(shaderType);
        if(shader.loadFromFile(fileName, mErrorDescription))
        {
            glAttachShader(mProgramHandle, shader.shaderHandle());
            result = true;
        }
    }
    else
    {
        mErrorDescription = std::string("Invalid programm handle");
    }
    return result;
}

bool GLSLProgram::linkProgramm()
{
    bool result = false;
    if(mProgramHandle != 0)
    {
        int success = 0;
        char linkStatus[INFO_LOG_LENGTH] = {0};
        glLinkProgram(mProgramHandle);
        glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(mProgramHandle, INFO_LOG_LENGTH, nullptr, linkStatus);
            mErrorDescription = std::string(linkStatus);
        }
        else
        {
            result = true;
        }
    }
    return result;
}

const std::string& GLSLProgram::getErrorDescription() const
{
    return  mErrorDescription;
}

void GLSLProgram::bind()
{
    glUseProgram(mProgramHandle);
}

void GLSLProgram::unbind()
{
    glUseProgram(0);
}

int GLSLProgram::getUniformLocation(const std::string& name)
{
    int result = -1;
    if(mProgramHandle != 0)
    {
        result = glGetUniformLocation(mProgramHandle, name.c_str());
    }

    return result;
}

bool GLSLProgram::setUniformValue(const std::string& name, const bool value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniform1i(loc, value);
        result = true;
    }
    return result;
}

bool GLSLProgram::setUniformValue(const std::string& name, const int value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniform1i(loc, value);
        result = true;
    }
    return result;
}

bool GLSLProgram::setUniformValue(const std::string& name, const GLuint value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniform1ui(loc, value);
        result = true;
    }
    return result;
}

bool GLSLProgram::setUniformValue(const std::string& name, const float value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniform1f(loc, value);
        result = true;
    }
    return result;
}

bool GLSLProgram::setUniformValue(const std::string& name, const glm::vec2& value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniform2fv(loc, 1, glm::value_ptr(value));
    }
    return result;
}

bool GLSLProgram::setUniformValue(const std::string& name, const glm::vec3& value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniform3fv(loc, 1, glm::value_ptr(value));
        result = true;
    }
    return result;
}

bool GLSLProgram::setUniformValue(const std::string& name, const glm::vec4& value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniform4fv(loc, 1, glm::value_ptr(value));
        result = true;
    }
    return result;
}

bool GLSLProgram::setUniformValue(const std::string &name, const glm::mat2 &value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        result = true;
    }
    return result;
}

bool GLSLProgram::setUniformValue(const std::string &name, const glm::mat3 &value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        result = true;
    }
    return result;
}

bool GLSLProgram::setUniformValue(const std::string &name, const glm::mat4 &value)
{
    bool result = false;
    int loc = getUniformLocation(name);
    if(loc != -1)
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        result = true;
    }
    return result;
}

//Shader implementation
GLSLProgram::Shader::Shader(const GLenum type)
: mShaderType(type)
, mShaderHandle(0)
{
}

GLSLProgram::Shader::~Shader()
{
    if(mShaderHandle != 0)
    {
        glDeleteShader(mShaderHandle);
    }
}

bool GLSLProgram::Shader::loadFromFile(const std::string& fileName, std::string& error)
{
    bool result = false;
    error = std::string();
    std::string shaderCode;
    result = readCodeFromFile(fileName, shaderCode);
    !result ? error = std::string("Failed read shader file ") + fileName : std::string();
    if(result)
    {
        mShaderHandle = glCreateShader(mShaderType);
        if(mShaderHandle != 0)
        {
            int success = 0;
            char compileStatus[INFO_LOG_LENGTH] = {0};
            const char* sc = shaderCode.c_str();
            glShaderSource(mShaderHandle, 1, &sc, nullptr);
            glCompileShader(mShaderHandle);
            glGetShaderiv(mShaderHandle, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(mShaderHandle, INFO_LOG_LENGTH, nullptr, compileStatus);
                error = std::string(compileStatus);
                result = false;
            }
        }
    }

    return result;
}

bool GLSLProgram::Shader::readCodeFromFile(const std::string &fileName, std::string& shaderCode)
{
    bool result = false;
    std::ifstream fs;
    fs.open(fileName);
    if(fs.is_open())
    {
        std::string str;
        std::stringstream codeStream;
        codeStream << fs.rdbuf();
        shaderCode = codeStream.str();
        result = true;
    }
    return result;
}

GLuint GLSLProgram::Shader::shaderHandle() const
{
    return mShaderHandle;
}

GLenum GLSLProgram::Shader::shaderType() const
{
    return mShaderType;
}
