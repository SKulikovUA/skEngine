#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "../interface/IModel.hpp"
#include <assimp/scene.h>

class Model: public IModel
{
protected:
    struct Vertex
    {
        glm::vec3 mPosition;
        glm::vec3 mNormal;
        glm::vec2 mTextCoord;

        Vertex()
        {
            mPosition = glm::vec3();
            mNormal = glm::vec3();
            mTextCoord = glm::vec2();
        }
    };

    using TVertexList = std::vector<Vertex>;
    using TIndicesList = std::vector<uint32_t>;

public:
    Model();

    virtual bool loadFromFile(const std::string& fileName) override final;
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
