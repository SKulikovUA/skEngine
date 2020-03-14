#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>

enum class VertexComponent : uint32_t
{
   VF_POSITION = 1,
   VF_NORMAL = 2,
   VF_COLOR = 4,
   VF_TEX_COORD = 16,
   VF_TANGENT = 32,
   VF_BITANGENT = 64
};

using TVertexComponentList = std::vector<VertexComponent>;

class IVertexComponents
{
public:
   virtual const TVertexComponentList &vertexAttributesList() const = 0;
   virtual GLsizei stride() const = 0;

   virtual ~IVertexComponents() = default;
};

class IModel
{
public:
   virtual bool loadFromFile(const std::string &fileName, const IVertexComponents* vertexFormat) = 0;
   virtual void draw() = 0;

   virtual ~IModel() = default;
};