#pragma once

#include <GL/glew.h>
#include <string>

class ITexture
{
public:
   virtual void bind(const GLuint tmuNumber) = 0;
   virtual void unbind() = 0;
   virtual bool loadFromFile(const std::string &fileName) = 0;
   virtual ~ITexture() = default;
};
