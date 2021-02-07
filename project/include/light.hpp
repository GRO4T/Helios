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
class Light {
public:
    Light(const PhongLight &phong_light) : phong_light(phong_light) {}

    const glm::vec3 &getAmbient() const { return phong_light.ambient; }
    const glm::vec3 &getDiffuse() const { return phong_light.diffuse; }
    const glm::vec3 &getSpecular() const { return phong_light.specular; }
    void setAmbient(const glm::vec3 &value) { phong_light.ambient = value; }
    void setDiffuse(const glm::vec3 &value) { phong_light.diffuse = value; }
    void setSpecular(const glm::vec3 &value) { phong_light.specular = value; }

private:
    PhongLight phong_light;
};

using LightPtr = std::unique_ptr<Light>;

class PointLight : public Light, public Transformable {
public:
    struct Attenuation {
        float constant;
        float linear;
        float quadratic;
    };
    PointLight(ModelPtr model, const Transform &t,
               const PhongLight &phong_light, const Attenuation& attenuation)
        : Light(phong_light), Transformable(t), model(std::move(model)), attenuation(attenuation) {}
    const Model &getModel() const { return *model; }
    float getConstant() const { return attenuation.constant; }
    float getLinear() const { return attenuation.linear; }
    float getQuadratic() const { return attenuation.quadratic; }

private:
    ModelPtr model;
    Attenuation attenuation;
};

using PointLightPtr = std::unique_ptr<PointLight>;

class DirLight : public Light {
public:
    DirLight(const PhongLight &phong_light, const glm::vec3 &direction)
        : Light(phong_light), direction(direction) {}
    const glm::vec3 &getDirection() const { return direction; }

private:
    glm::vec3 direction;
};

using DirLightPtr = std::unique_ptr<DirLight>;

}  // namespace game_engine
