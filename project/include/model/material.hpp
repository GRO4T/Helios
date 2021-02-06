#pragma once

#include <iostream>
#include <texture/texture.hpp>
#include <texture/texture_manager.hpp>
#include <vector>

#include "opengl_all.hpp"

namespace game_engine {

struct Material {
    Material(const glm::vec3& ambient, const glm::vec3& diffuse,
             const glm::vec3& specular, float shininess, Texture* texture)
        : ambient(ambient),
          diffuse(diffuse),
          specular(specular),
          shininess(shininess),
          texture(texture) {}

    Material(const glm::vec3& ambient, const glm::vec3& diffuse,
             const glm::vec3& specular, float shininess)
        : ambient(ambient),
          diffuse(diffuse),
          specular(specular),
          shininess(shininess) {
        texture = &TextureManager::getInstance().getTexture("res/white.jpg");
    }

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    Texture* texture;
};

using MaterialSPtr = std::shared_ptr<Material>;

namespace material {

struct Gold : public Material {
    Gold()
        : Material(glm::vec3(0.24725, 0.1995, 0.0745),
                   glm::vec3(0.75164, 0.60648, 0.22648),
                   glm::vec3(0.628281, 0.555802, 0.366065), 51.2f) {}
    Gold(Texture* texture)
        : Material(glm::vec3(0.24725, 0.1995, 0.0745),
                   glm::vec3(0.75164, 0.60648, 0.22648),
                   glm::vec3(0.628281, 0.555802, 0.366065), 51.2f, texture) {}
};

struct Silver : public Material {
    Silver()
        : Material(glm::vec3(0.19225, 0.19225, 0.19225),
                   glm::vec3(0.50754, 0.50754, 0.50754),
                   glm::vec3(0.508273, 0.508273, 0.508273), 51.2f) {}
    Silver(Texture* texture)
        : Material(glm::vec3(0.19225, 0.19225, 0.19225),
                   glm::vec3(0.50754, 0.50754, 0.50754),
                   glm::vec3(0.508273, 0.508273, 0.508273), 51.2f, texture) {}
};

}  // namespace material

}  // namespace game_engine