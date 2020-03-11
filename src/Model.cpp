#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <iostream>

Model::Model()
: mVertices()
, mIndices()
{
}

bool Model::loadFromFile(const std::string& fileName)
{
    bool result = false;
    Assimp::Importer importer;

    auto proccessModel = [ this ](const aiMesh* mesh)
    {
        if(mesh != nullptr)
        {
            std::cout << mesh->mName.C_Str() << std::endl;
            for(uint32_t i = 0; i < mesh->mNumFaces; ++i)
            {
                for(uint32_t j=0;  j < mesh->mFaces[j].mNumIndices;++j)
                {
                    mIndices.push_back(mesh->mFaces[i].mIndices[j]);
                }
            }

            for(uint32_t i = 0; i < mesh->mNumVertices; ++i)
            {
                Vertex v;
                v.mPosition = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
                v.mNormal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
                if(mesh->mTextureCoords[0] != nullptr )
                {
                    v.mTextCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y); 
                }
                mVertices.push_back(v);
            }
        }
    };

    const aiScene* pScene = importer.ReadFile(
        fileName, 
        aiProcess_Triangulate | 
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices);
    
    if(pScene != nullptr)
    {
        std::cout << "Model meshes count : " << pScene->mNumMeshes << std::endl;
        for(unsigned int i = 0; i < pScene->mNumMeshes; ++i)
        {
            proccessModel(pScene->mMeshes[i]);
        }
        result = true;
        std::cout << "Scene triangle count : " << mIndices.size() / 3 << std::endl;
    }
    return result;
}

void Model::draw()
{
    //@TODO
}

