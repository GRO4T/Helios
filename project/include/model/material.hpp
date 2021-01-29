#pragma once

#include <iostream>
#include <texture/texture.hpp>
#include <vector>

#include "opengl_all.hpp"

namespace game_engine {

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float alpha;
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, float alpha,
             Texture& texture)
        : ambient(ambient),
          diffuse(diffuse),
          specular(specular),
          shininess(shininess),
          alpha(alpha),
          texture(texture) {}
    Texture& texture;
};

using MaterialSPtr = std::shared_ptr<Material>;

}  // namespace game_engine