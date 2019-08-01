#include "shader.h"

#include <iostream>
#include <fstream>


Shader::Shader(const GLenum type)
: mShaderType(type)
, mShaderHandle(0)
, mFileName(std::string())
{
}

Shader::~Shader()
{
    if(mShaderHandle != 0)
    {
        glDeleteShader(mShaderHandle);
    }
}

bool Shader::loadFromFile(const std::string& fileName, std::string& error)
{
    bool result = false;
    error = std::string();
    mFileName = fileName;
    result = readCodeFromFile(fileName);
    !result ? error = std::string("Failed read shader file ") + mFileName : error;
    if(result)
    {
        mShaderHandle = glCreateShader(mShaderType);
        if(mShaderHandle != 0)
        {
            //glShaderSource(mShaderHandle, )
        }
    }

    return result;
}

bool Shader::readCodeFromFile(const std::string &fileName)
{
    bool result = false;
    std::ifstream fs;
    fs.open(fileName);
    if(fs.is_open())
    {
        std::string str;
        while(std::getline(fs, str))
        {
            std::cout << str << std::endl;
        }
        result = true;
    }
    return result;
}
