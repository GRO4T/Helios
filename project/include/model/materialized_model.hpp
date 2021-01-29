#pragma once

#include <iostream>
#include <vector>

#include "model/material.hpp"
#include "model/model.hpp"
#include "texture/texture.hpp"
#include "texture/texture_manager.hpp"

namespace game_engine {

class MaterializedModel {
public:
    MaterializedModel(ModelPtr model, MaterialSPtr material)
        : model(std::move(model)), material(material) {}
    ~MaterializedModel() {}
    const Model& getModel() { return *model; }
    Material& getMaterial() const { return *material; }

private:
    ModelPtr model;
    MaterialSPtr material;
};

using MaterializedModelPtr = std::unique_ptr<MaterializedModel>;
using MaterializedModelSPtr = std::shared_ptr<MaterializedModel>;

}  // namespace game_engine