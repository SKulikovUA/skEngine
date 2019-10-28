#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <iostream>

Model::Model()
{
}

bool Model::loadFromFile(const std::string& fileName)
{
    bool result = false;
    Assimp::Importer importer;

    const aiScene* pScene = importer.ReadFile(
        fileName, 
        aiProcess_Triangulate | 
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices);
    
    if(pScene != nullptr)
    {
        std::cout << "Model meshes count : " << pScene->mNumMeshes << std::endl;
        for(int i = 0; i < pScene->mNumMeshes; ++i)
        {
            if(pScene->mMeshes[i]->HasPositions())
            {
                std::cout << "Model " << i <<" has positions" << std::endl;
            }
            if(pScene->mMeshes[i]->HasTextureCoords(0))
            {
                std::cout << "Model " << i <<" has texture coords" << std::endl;
            }
        }
        result = true;
    }
    return result;
}

void Model::draw()
{
    //
}