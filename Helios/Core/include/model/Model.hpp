#pragma once

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <iostream>
#include <sstream>

#include "Utils.hpp"
#include "model/MaterializedMesh.hpp"

namespace helios {

class Model {
public:
    Model(const std::vector<MaterializedMeshSharedPtr>& meshes) : meshes(meshes) {}
    Model(const std::string& path);
    void load(const std::string& path);

    std::vector<MaterializedMeshSharedPtr> meshes;

private:
    void processNode(aiNode* node, const aiScene* scene);
    MaterializedMeshSharedPtr processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<TextureSPtr> loadMaterialTextures(aiMaterial* mat,
                                                  aiTextureType type);

    std::string directory;
};

using ModelPtr = std::unique_ptr<Model>;

}  // namespace helios