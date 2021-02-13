#pragma once

#include <iostream>
#include <vector>

#include "model/material.hpp"
#include "model/mesh.hpp"
#include "texture/texture.hpp"
#include "texture/texture_manager.hpp"

namespace game_engine {

class MaterializedMesh {
public:
    MaterializedMesh(MeshPtr model, MaterialSPtr material)
        : model(std::move(model)), material(material) {}
    ~MaterializedMesh() {}
    const Mesh& getModel() const { return *model; }
    Material& getMaterial() const { return *material; }

private:
    MeshPtr model;
    MaterialSPtr material;
};

using MaterializedMeshPtr = std::unique_ptr<MaterializedMesh>;
using MaterializedMeshSPtr = std::shared_ptr<MaterializedMesh>;

}  // namespace game_engine