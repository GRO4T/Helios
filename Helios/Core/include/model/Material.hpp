#pragma once

#include <iostream>
#include <texture/Texture.hpp>
#include <texture/TextureManager.hpp>
#include <vector>

#include "opengl_all.hpp"

namespace game_engine {

class Material {
public:
    glm::vec3 ambient;
    std::vector<TextureSPtr> diffuse_maps;
    glm::vec3 diffuse;
    std::vector<TextureSPtr> specular_maps;
    glm::vec3 specular;
    float shininess;
};

using MaterialSPtr = std::shared_ptr<Material>;

namespace material {

struct Gold : public Material {
    Gold() {
        ambient = glm::vec3(0.24725, 0.1995, 0.0745);
        diffuse = glm::vec3(0.75164, 0.60648, 0.22648);
        specular = glm::vec3(0.628281, 0.555802, 0.366065);
        shininess = 51.2f;
    }
};

struct Silver : public Material {
    Silver() {
        ambient = glm::vec3(0.19225, 0.19225, 0.19225);
        diffuse = glm::vec3(0.50754, 0.50754, 0.50754);
        specular = glm::vec3(0.508273, 0.508273, 0.508273);
        shininess = 51.2f;
    }
};

}  // namespace material

}  // namespace game_engine