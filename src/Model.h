#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "../interface/IModel.hpp"
#include <assimp/scene.h>

class Model: public IModel
{
public:
    Model();

    virtual bool loadFromFile(const std::string& fileName) override final;
    virtual void draw() override final;

    virtual ~Model()
    {
    }

private:
    bool proccessModel(const aiScene* scene);

private:
    std::vector<glm::vec3> mPositions;
};
