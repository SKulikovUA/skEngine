#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <iostream>

VertexAttributeFormat::VertexAttributeFormat(TVertexComponentList vertexAttr)
{
   mVertexAttributes = std::move(vertexAttr);
   std::sort(mVertexAttributes.begin(), mVertexAttributes.end());
}

const TVertexComponentList &VertexAttributeFormat::vertexAttributesList() const
{
   return mVertexAttributes;
}

GLsizei VertexAttributeFormat::stride() const
{
   GLsizei result = 0;
   for (const auto &vComponent : mVertexAttributes)
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
    : mVertices(), mIndices(), mVAO(0), mVBO(0), mEBO(0)
{
}

bool Model::loadFromFile(const std::string &fileName, const IVertexComponents *vertexFormat)
{
   bool result = false;
   Assimp::Importer importer;

   auto proccessModel = [this](const aiMesh *mesh, const IVertexComponents *vertexFormat) {
      if (mesh != nullptr)
      {
         std::cout << mesh->mName.C_Str() << std::endl;
         uint32_t indexBase = static_cast<uint32_t>(mIndices.size());
         for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
         {
            const aiFace &face = mesh->mFaces[i];
            mIndices.push_back(indexBase + face.mIndices[0]);
            mIndices.push_back(indexBase + face.mIndices[1]);
            mIndices.push_back(indexBase + face.mIndices[2]);
         }

         const aiVector3D Zero(0.0f, 0.0f, 0.0f);
         const aiColor4D DefColor(1.0f, 1.0f, 1.0f, 1.0f);
         std::cout << "Num vertices : " << mesh->mNumVertices << std::endl;
         for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
         {
            const aiVector3D *pos = mesh->HasPositions() ? &(mesh->mVertices[i]) : &Zero;
            const aiVector3D *norm = mesh->HasNormals() ? &(mesh->mNormals[i]) : &Zero;
            const aiVector3D *texCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero;
            const aiColor4D *color = mesh->HasVertexColors(0) ? &(mesh->mColors[0][i]) : &DefColor;
            const aiVector3D *tangent = mesh->HasTangentsAndBitangents() ? &(mesh->mTangents[i]) : &Zero;
            const aiVector3D *biTangent = mesh->HasTangentsAndBitangents() ? &(mesh->mBitangents[i]) : &Zero;

            auto pushVec3DInVertexArray = [this](const aiVector3D *val) {
               mVertices.push_back(val->x);
               mVertices.push_back(val->y);
               mVertices.push_back(val->z);
            };

            for (const auto &vComp : vertexFormat->vertexAttributesList())
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

   auto createVertexBuffers = [this](const IVertexComponents *vertexAttributes) {
      
   };

   const aiScene *pScene = importer.ReadFile(
         fileName,
         aiProcess_Triangulate |
         aiProcess_GenSmoothNormals |
         aiProcess_PreTransformVertices |
         aiProcess_FlipUVs);

   if (pScene != nullptr)
   {
      std::cout << "Model meshes count : " << pScene->mNumMeshes << std::endl;
      for (unsigned int i = 0; i < pScene->mNumMeshes; ++i)
      {
         proccessModel(pScene->mMeshes[i], vertexFormat);
      }
      result = true;
      std::cout << "Scene triangle count : " << mIndices.size() / 3 << std::endl;
      createVertexArrayObject(vertexFormat);
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
   glBindVertexArray(mVAO);
   glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, (GLsizei*)0);
   glBindVertexArray(0);
}

Model::~Model()
{
   if (mVAO != 0)
   {
      glBindVertexArray(0);
      glDeleteVertexArrays(1, &mVAO);
   }

   if (mVBO != 0)
   {
      glDeleteBuffers(1, &mVBO);
   }

   if (mEBO != 0)
   {
      glDeleteBuffers(1, &mEBO);
   }
}

void Model::setupVertexBuffers()
{
   glGenBuffers(1, &mVBO);
   glGenBuffers(1, &mEBO);

   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float),
                mVertices.data(), GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                mIndices.size() * sizeof(uint32_t), mIndices.data(), GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::createVertexArrayObject(const IVertexComponents* vertexFormat)
{
   glGenVertexArrays(1, &mVAO);

   glBindVertexArray(mVAO);
   uint32_t stride = vertexFormat->stride();

   setupVertexBuffers();
   uint32_t localOffset = 0;
   GLuint attrIndex = 0;
   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   for (const auto &component : vertexFormat->vertexAttributesList())
   {
      intptr_t offset = 0;
      switch (component)
      {
      case VertexComponent::VF_POSITION:
         offset = localOffset * sizeof(GLfloat);
         glEnableVertexAttribArray(0);
         glVertexAttribPointer(
               0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
         attrIndex++;
         localOffset += 3;
         break;

      case VertexComponent::VF_NORMAL:
         offset = localOffset * sizeof(GLfloat);
         glEnableVertexAttribArray(attrIndex);
         glVertexAttribPointer(
             attrIndex, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
         attrIndex++;
         localOffset += 3;
         break;

      case VertexComponent::VF_COLOR:
         offset = localOffset * sizeof(GLfloat);
         glVertexAttribPointer(
            attrIndex, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offset));
         glEnableVertexAttribArray(attrIndex);
         attrIndex++;
         localOffset += 4;
         break;

         case VertexComponent::VF_TEX_COORD:
            offset = localOffset * sizeof(GLfloat);
            glVertexAttribPointer(
                attrIndex, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offset));
            glEnableVertexAttribArray(attrIndex);
            attrIndex++;
            localOffset += 2;
            break;

         case VertexComponent::VF_TANGENT:
            offset = localOffset * sizeof(GLfloat);
            glVertexAttribPointer(
                attrIndex, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offset));
            glEnableVertexAttribArray(attrIndex);
            attrIndex++;
            localOffset += 3;
            break;

         case VertexComponent::VF_BITANGENT:
            offset = localOffset * sizeof(GLfloat);
            glVertexAttribPointer(
                attrIndex, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(offset));
            glEnableVertexAttribArray(attrIndex);
            attrIndex++;
            localOffset += 3;
            break;

         default:
            break;
         }
      }
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
      glBindVertexArray(0);
}