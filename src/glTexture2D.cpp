#include <iostream>
#include <GL/glew.h>
#include <gli/gli.hpp>

#include "glTexture2D.h"


glTexture::glTexture()
{
    glGenTextures(1, &mTextureHandle);
}

bool glTexture::loadFromFile(const std::string& fileName)
{
    gli::texture texture = gli::load(fileName);
    gli::gl gl(gli::gl::PROFILE_GL33);

    GLenum target = gl.translate(texture.target());
    if(texture.empty())
    {
        std::cout << "Failed load texture" << std::endl;
        return false;
    }
    std::cout << texture.size() << std::endl;
    
    std::string str;
    (target == GL_TEXTURE_2D) ? str="Texture 2d" : str = "Other";
    std::cout <<  str << std::endl;
    return false;
}

void glTexture::bind(const GLuint tmuNumber)
{
    glBindTexture(GL_TEXTURE_2D, mTextureHandle);
}

void glTexture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

glTexture::~glTexture()
{
    glDeleteTextures(1, &mTextureHandle);
    mTextureHandle = 0;
}