#pragma once

#include <GL/glew.h>

class GLSLProgram
{
public:
    GLSLProgram();
    ~GLSLProgram();

private:
    GLuint mProgramHandle;
};

