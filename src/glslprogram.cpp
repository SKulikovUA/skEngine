#include "glslprogram.h"
#include <iostream>


GLSLProgram::GLSLProgram()
{
    mProgramHandle = glCreateProgram();
}

GLSLProgram::~GLSLProgram()
{
    glDeleteProgram(mProgramHandle);
}


