#pragma once

#include <iostream>
#include <texture/texture.hpp>
#include <texture/texture_manager.hpp>
#include <vector>

#include "opengl_all.hpp"

namespace game_engine {

class Material {
public:
    void setDiffuseMaps(const std::vector<std::string>& tex_paths) {
        for (const auto& tp : tex_paths) {
            diffuse_maps.push_back(&TextureManager::getInstance().getTexture(tp));
        }
    }

    void setSpecularMaps(const std::vector<std::string>& tex_paths) {
        for (const auto& tp : tex_paths) {
            specular_maps.push_back(&TextureManager::getInstance().getTexture(tp));
        }
    }

    glm::vec3 ambient;
    std::vector<Texture*> diffuse_maps;
    glm::vec3 diffuse;
    std::vector<Texture*> specular_maps;
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