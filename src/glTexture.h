#pragma once

#include "../interface/ITexture.h"

class glTexture : public ITexture
{
public:
    glTexture(const GLenum target);
    virtual bool loadFromFile(const std::string& fileName) override;
    virtual void bind(const GLuint tmuNumber) override;
    virtual void unbind() override;

    virtual ~glTexture();

private:
    bool isCompressedTexture(const std::string& fileName);
    bool loadCompressedTexture(const std::string& fileName);
    bool loadUnCompressedTexture(const std::string& fileName);

private:
    GLuint mTextureHandle;
    GLenum mTarget;
};