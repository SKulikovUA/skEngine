#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "../interface/IModel.hpp"
#include <assimp/scene.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

class VertexAttributeFormat : public IVertexComponents
{
public:
    VertexAttributeFormat(TVertexComponentList vertexAttr);
    virtual const TVertexComponentList& vertexAttributesList() const override;
    virtual uint32_t stride() override;

private:
    TVertexComponentList mVertexAttributes;
};

class Model: public IModel
{
protected:
    using TVertexList = std::vector<float>;
    using TIndicesList = std::vector<uint32_t>;

public:
    Model();

    virtual bool loadFromFile(const std::string& fileName, const IVertexComponents& vertexFormat) override final;
    virtual void draw() override final;

    virtual ~Model()
    {
    }

private:
    TVertexList mVertices;
    TIndicesList mIndices;
    GLuint mVboId;
    GLuint mIboId; 
};
