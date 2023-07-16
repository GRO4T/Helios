#pragma once

#include <iostream>
#include <vector>

#include "Helios/Core/model/Material.hpp"
#include "Helios/Core/model/Mesh.hpp"
#include "Helios/Core/texture/Texture.hpp"
#include "Helios/Core/texture/TextureManager.hpp"

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
