#include <iostream>
#include <GL/glew.h>
#include <gli/gli.hpp>

#include "glTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


glTexture::glTexture(const GLenum target)
: mTarget(target)
{
    glGenTextures(1, &mTextureHandle);
}

bool glTexture::loadFromFile(const std::string& fileName)
{
    bool compressed = isCompressedTexture(fileName);
    if(compressed)
    {
        std::cout << "Compressed texture" << std::endl;
    }
    else
    {
        std::cout << "Uncompressed texture" << std::endl;
    }

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
    glBindTexture(mTarget, mTextureHandle);
}

void glTexture::unbind()
{
    glBindTexture(mTarget, 0);
}

glTexture::~glTexture()
{
    glDeleteTextures(1, &mTextureHandle);
    mTextureHandle = 0;
}

bool glTexture::isCompressedTexture(const std::string& fileName)
{
    bool result = false;
    const std::string compressedExtensions[] = {std::string("dds"), std::string("ktx")};

    std::string ext = fileName.substr(fileName.find_last_of(".") + 1);

    for(auto cExt : compressedExtensions)
    {
        if(ext == cExt)
        {
            result = true;
            break;
        }
    }

    return result;
}

bool glTexture::loadCompressedTexture(const std::string& fileName)
{
    bool result = false;

    return result;
}

bool glTexture::loadUnCompressedTexture(const std::string& fileName)
{
    bool result = false;

    return result;
}