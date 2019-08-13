#pragma once

#include "../interface/ITexture.h"

class glTexture : public ITexture
{
public:
    glTexture();
    virtual bool loadFromFile(const std::string& fileName);
    virtual void bind(const GLuint tmuNumber);
    virtual void unbind();

    virtual ~glTexture();

private:
    GLuint mTextureHandle;
};