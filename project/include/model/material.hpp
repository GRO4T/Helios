#pragma once

#include <iostream>
#include <texture/texture.hpp>
#include <texture/texture_manager.hpp>
#include <vector>

#include "opengl_all.hpp"

namespace game_engine {

class Material {
public:
    Material& setAmbient(const glm::vec3& ambient) {
        this->ambient = ambient;
        return *this;
    }
    Material& setDiffuseMap(Texture* diffuse_map) {
        this->diffuse_map = diffuse_map;
        is_diffuse_map = true;
        return *this;
    }
    Material& setDiffuse(const glm::vec3& diffuse) {
        this->diffuse = diffuse;
        is_diffuse_map = false;
        return *this;
    }
    Material& setSpecularMap(Texture* specular_map) {
        this->specular_map = specular_map;
        is_specular_map = true;
        return *this;
    }
    Material& setSpecular(const glm::vec3& specular) {
        this->specular = specular;
        is_specular_map = false;
        return *this;
    }
    Material& setShininess(float shininess) {
        this->shininess = shininess;
        return *this;
    }

    const glm::vec3& getAmbient() const { return ambient; }
    const glm::vec3& getDiffuse() const { return diffuse; }
    Texture* getDiffuseMap() const { return diffuse_map; }
    const glm::vec3& getSpecular() const { return specular; }
    Texture* getSpecularMap() const { return specular_map; }
    float getShininess() const { return shininess; }
    bool isDiffuseMap() const { return is_diffuse_map; }
    bool isSpecularMap() const { return is_specular_map; }

protected:
    glm::vec3 ambient;
    bool is_diffuse_map;
    glm::vec3 diffuse;
    Texture* diffuse_map;
    bool is_specular_map;
    glm::vec3 specular;
    Texture* specular_map;
    float shininess;
};

using MaterialSPtr = std::shared_ptr<Material>;

namespace material {

struct Gold : public Material {
    Gold() {
        setAmbient(glm::vec3(0.24725, 0.1995, 0.0745));
        setDiffuse(glm::vec3(0.75164, 0.60648, 0.22648));
        setSpecular(glm::vec3(0.628281, 0.555802, 0.366065));
        setShininess(51.2f);
    }
};

struct Silver : public Material {
    Silver() {
        setAmbient(glm::vec3(0.19225, 0.19225, 0.19225));
        setDiffuse(glm::vec3(0.50754, 0.50754, 0.50754));
        setSpecular(glm::vec3(0.508273, 0.508273, 0.508273));
        setShininess(51.2f);
    }
};

}  // namespace material

}  // namespace game_engine