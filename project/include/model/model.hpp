#pragma once

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <iostream>
#include <sstream>

#include "model/materialized_mesh.hpp"
#include "utils.hpp"

namespace game_engine {

class Model {
public:
    Model(const std::vector<MaterializedMeshSPtr>& meshes) : meshes(meshes) {}
    Model(const std::string& path);
    void load(const std::string& path);

    std::vector<MaterializedMeshSPtr> meshes;

private:
    void processNode(aiNode* node, const aiScene* scene);
    MaterializedMeshSPtr processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<TextureSPtr> loadMaterialTextures(aiMaterial* mat,
                                                  aiTextureType type);

    std::string directory;
};

using ModelPtr = std::unique_ptr<Model>;

}  // namespace game_engine