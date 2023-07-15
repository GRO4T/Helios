#pragma once

#include <iostream>
#include <vector>

#include "model/Material.hpp"
#include "model/Mesh.hpp"
#include "texture/Texture.hpp"
#include "texture/TextureManager.hpp"

namespace helios {

class MaterializedMesh {
public:
    MaterializedMesh(MeshPtr mesh, MaterialSharedPtr material)
        : mesh(std::move(mesh)), material(material) {}
    ~MaterializedMesh() {}
    const Mesh& getMesh() const { return *mesh; }
    Material& getMaterial() const { return *material; }

private:
 MeshPtr mesh;
 MaterialSharedPtr material;
};

using MaterializedMeshPtr = std::unique_ptr<MaterializedMesh>;
using MaterializedMeshSharedPtr = std::shared_ptr<MaterializedMesh>;

}  // namespace helios