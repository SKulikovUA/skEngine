#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <iostream>

VertexAttributeFormat::VertexAttributeFormat(TVertexComponentList vertexAttr)
{
    mVertexAttributes = std::move(vertexAttr);
}

const TVertexComponentList& VertexAttributeFormat::vertexAttributesList() const
{
    return mVertexAttributes;
}

uint32_t VertexAttributeFormat::stride()
{
    uint32_t result = 0;
    for(const auto& vComponent : mVertexAttributes)
    {
        switch (vComponent)
        {
        case VertexComponent::VF_POSITION:
        case VertexComponent::VF_NORMAL:
        case VertexComponent::VF_TANGENT:
        case VertexComponent::VF_BITANGENT:
            result += 3 * sizeof(float);
            break;

        case VertexComponent::VF_COLOR:
            result += 4 * sizeof(float);
        
        case VertexComponent::VF_TEX_COORD:
            result += 2 * sizeof(float);
        
        default:
            break;
        }
    }
    return result;
}

Model::Model()
: mVertices()
, mIndices()
{
}

bool Model::loadFromFile(const std::string& fileName, const IVertexComponents& vertexFormat)
{
    bool result = false;
    Assimp::Importer importer;

    auto proccessModel = [ this, &vertexFormat ](const aiMesh* mesh)
    {
        if(mesh != nullptr)
        {
            std::cout << mesh->mName.C_Str() << std::endl;
            uint32_t indexBase = static_cast<uint32_t>(mIndices.size());
            for(uint32_t i = 0; i < mesh->mNumFaces; ++i)
            {
                const aiFace& face = mesh->mFaces[i];
                if(face.mNumIndices == 3)
                {
                    mIndices.push_back(indexBase + face.mIndices[0]);
                    mIndices.push_back(indexBase + face.mIndices[1]);
                    mIndices.push_back(indexBase + face.mIndices[2]);
                }
                else
                {
                    continue;
                }
            }

            const aiVector3D Zero(0.0f, 0.0f, 0.0f);
            const aiColor4D DefColor(1.0f, 1.0f, 1.0f, 1.0f);
            for(uint32_t i = 0; i < mesh->mNumVertices; ++i)
            {
                const aiVector3D* pos = mesh->HasPositions() ? &(mesh->mVertices[i]) : &Zero;
                const aiVector3D* norm = mesh->HasNormals() ? &(mesh->mNormals[i]) : &Zero;
                const aiVector3D* texCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero;
                const aiColor4D* color = mesh->HasVertexColors(0) ? &(mesh->mColors[0][i]) : &DefColor;
                const aiVector3D* tangent = mesh->HasTangentsAndBitangents() ? &(mesh->mTangents[i]) : &Zero;
                const aiVector3D* biTangent = mesh->HasTangentsAndBitangents() ? &(mesh->mBitangents[i]) : &Zero;

                auto pushVec3DInVertexArray = [ this ](const aiVector3D* val)
                {
                        mVertices.push_back(val->x);
                        mVertices.push_back(val->y);
                        mVertices.push_back(val->z);
                };

                for(const auto& vComp : vertexFormat.vertexAttributesList())
                {
                    switch (vComp)
                    {
                    case VertexComponent::VF_POSITION:
                        pushVec3DInVertexArray(pos);
                        break;

                    case VertexComponent::VF_NORMAL:
                        pushVec3DInVertexArray(norm);
                        break;
                    
                    case VertexComponent::VF_TEX_COORD:
                        mVertices.push_back(texCoord->x);
                        mVertices.push_back(texCoord->y);
                        break;

                    case VertexComponent::VF_COLOR:
                        mVertices.push_back(color->r);
                        mVertices.push_back(color->g);
                        mVertices.push_back(color->b);
                        mVertices.push_back(color->a);
                        break;

                    case VertexComponent::VF_TANGENT:
                        pushVec3DInVertexArray(tangent);
                        break;

                    case VertexComponent::VF_BITANGENT:
                        pushVec3DInVertexArray(biTangent);
                        break;

                    default:
                        break;
                    }
                }
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
    else
    {
        std::string error = importer.GetErrorString();
        std::cout << error << std::endl;
    }
    return result;
}

void Model::draw()
{
    //@TODO
}

