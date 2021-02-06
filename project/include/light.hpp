#pragma once

#include "model/model.hpp"
#include "utils.hpp"

namespace game_engine {

struct PhongLight {
    PhongLight(const glm::vec3 &ambient, const glm::vec3 &diffuse,
               const glm::vec3 &specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {}

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

using utils::Transform;
class Light : public Transformable {
public:
    Light(ModelPtr model, const Transform &t, const PhongLight &phong_light)
        : Transformable(t), model(std::move(model)), phong_light(phong_light) {}

    const Model &getModel() const { return *model; }
    const glm::vec3 &getAmbient() const { return phong_light.ambient; }
    const glm::vec3 &getDiffuse() const { return phong_light.diffuse; }
    const glm::vec3 &getSpecular() const { return phong_light.specular; }
    void setAmbient(const glm::vec3 &value) { phong_light.ambient = value; }
    void setDiffuse(const glm::vec3 &value) { phong_light.diffuse = value; }
    void setSpecular(const glm::vec3 &value) { phong_light.specular = value; }

private:
    ModelPtr model;

    PhongLight phong_light;
};

using LightPtr = std::unique_ptr<Light>;

}  // namespace game_engine
