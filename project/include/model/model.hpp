#pragma once

#include <iostream>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>

#include "model/materialized_mesh.hpp"

namespace game_engine {

class Model {
public:
    Model(const std::vector<MaterializedMeshSPtr>& meshes): meshes(meshes) {}
    Model(const std::string& path) { load(path); }
    void load(const std::string& path) {
        Assimp::Importer import;
        const aiScene* scene =
            import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
            !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    std::vector<MaterializedMeshSPtr> meshes;

private:
    void processNode(aiNode* node, const aiScene* scene) {
        std::cout << "num meshes: " << node->mNumMeshes << std::endl;
        for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
            std::cout << "i: " << i << std::endl;
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        std::cout << "num children: " << node->mNumChildren << std::endl;
        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            std::cout << "CHILD: " << i << std::endl;
            processNode(node->mChildren[i], scene);
        }
    }
    MaterializedMeshSPtr processMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        MaterialSPtr material = std::make_shared<Material>();

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            Vertex vertex;
            glm::vec3 vec3d;
            vec3d.x = mesh->mVertices[i].x;
            vec3d.y = mesh->mVertices[i].y;
            vec3d.z = mesh->mVertices[i].z;
            vertex.position = vec3d;
            vec3d.x = mesh->mNormals[i].x;
            vec3d.y = mesh->mNormals[i].y;
            vec3d.z = mesh->mNormals[i].z;
            if (mesh->mTextureCoords[0]) {
                glm::vec2 vec2d;
                vec2d.x = mesh->mTextureCoords[0][i].x;
                vec2d.y = mesh->mTextureCoords[0][i].y;
                vertex.uv = vec2d;
            } else
                vertex.uv = glm::vec2(0, 0);
            vertices.push_back(vertex);
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* ai_material = scene->mMaterials[mesh->mMaterialIndex];
            material->diffuse_maps =
                loadMaterialTextures(ai_material, aiTextureType_DIFFUSE);
            material->specular_maps =
                loadMaterialTextures(ai_material, aiTextureType_SPECULAR);
            // tmp
            material->ambient = glm::vec3(0.1f, 0.1f, 0.1f);
            material->shininess = 51.2f;
        }
        return std::make_shared<MaterializedMesh>(
            std::move(std::make_unique<IndexedMesh>(vertices, indices)),
            material);
    }

    std::vector<TextureSPtr> loadMaterialTextures(aiMaterial* mat,
                                                  aiTextureType type) {
        std::vector<TextureSPtr> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            auto& texture_manager = TextureManager::getInstance();
            aiString str;
            mat->GetTexture(type, i, &str);
            TextureSPtr texture = texture_manager.getTexture(directory + "/" + str.C_Str());
            textures.push_back(texture);
        }
        return textures;
    }

    std::string directory;
};

using ModelPtr = std::unique_ptr<Model>;

}  // namespace game_engine