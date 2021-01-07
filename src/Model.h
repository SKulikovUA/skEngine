#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "../interface/IModel.hpp"
#include <GL/glew.h>
#include <assimp/scene.h>

class VertexAttributeFormat : public IVertexComponents
{
public:
   VertexAttributeFormat(TVertexComponentList vertexAttr);
   virtual const TVertexComponentList &vertexAttributesList() const override;
   virtual GLsizei stride() const override;

private:
   TVertexComponentList mVertexAttributes;
};

class Model : public IModel
{
protected:
   using TVertexList = std::vector<float>;
   using TIndicesList = std::vector<uint32_t>;

public:
   Model();

   virtual bool loadFromFile(const std::string &fileName, const IVertexComponents* vertexFormat) override final;
   virtual void draw() override final;
   virtual ~Model();

private:
   void setupVertexBuffers();
   void createVertexArrayObject(const IVertexComponents* vertexFormat);

private:
   TVertexList mVertices;
   TIndicesList mIndices;
   GLuint mVAO;
   GLuint mVBO;
   GLuint mEBO;
};
