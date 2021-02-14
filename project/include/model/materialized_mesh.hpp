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
    MaterializedMesh(MeshPtr mesh, MaterialSPtr material)
        : mesh(std::move(mesh)), material(material) {}
    ~MaterializedMesh() {}
    const Mesh& getMesh() const { return *mesh; }
    Material& getMaterial() const { return *material; }

private:
    MeshPtr mesh;
    MaterialSPtr material;
};

using MaterializedMeshPtr = std::unique_ptr<MaterializedMesh>;
using MaterializedMeshSPtr = std::shared_ptr<MaterializedMesh>;

}  // namespace game_engine