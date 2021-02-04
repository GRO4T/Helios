#pragma once

#include "model/model.hpp"
#include "utils.hpp"

namespace game_engine {

struct PhongLight {
    PhongLight(float ambient, float diffuse, float specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {}

    glm::vec3 color = glm::vec3(1, 1, 1);
    float ambient;
    float diffuse;
    float specular;
};

using utils::Transform;
class Light {
public:
    Light(ModelPtr model, const Transform &t, const PhongLight &phong_light)
        : model(std::move(model)), transform(t), phong_light(phong_light) {}

    void setTransform(const Transform &transform) { this->transform = transform; }
    const Transform &getTransform() const { return transform; }
    const Model &getModel() const { return *model; }
    const glm::vec3 &getLightColor() const { return phong_light.color; }
    void setAmbient(float value) { phong_light.ambient = value; }
    float getAmbient() const { return phong_light.ambient; }
    float getDiffuse() const { return phong_light.diffuse; }
    float getSpecular() const { return phong_light.specular; }

private:
    Transform transform;
    ModelPtr model;

    PhongLight phong_light;
};

using LightPtr = std::unique_ptr<Light>;

}  // namespace game_engine
