#pragma once

#include <iostream>
#include <texture/texture.hpp>
#include <texture/texture_manager.hpp>
#include <vector>

#include "opengl_all.hpp"

namespace game_engine {

struct Material {
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, float alpha,
             Texture* texture)
        : ambient(ambient),
          diffuse(diffuse),
          specular(specular),
          shininess(shininess),
          alpha(alpha),
          texture(texture) {}

    Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
             const glm::vec4& base_color)
        : ambient(ambient), diffuse(diffuse), specular(specular), base_color(base_color) {
        texture = &TextureManager::getInstance().getTexture("res/white.jpg");
    }

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float alpha;
    glm::vec4 base_color;
    Texture* texture;
};

using MaterialSPtr = std::shared_ptr<Material>;

}  // namespace game_engine