#pragma once

#include "Helios/Core/Utils.hpp"
#include "Helios/Core/model/Mesh.hpp"
#include "Helios/Core/Transformable.hpp"

namespace helios {

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

class PhysicalLight : public Light, public Transformable {
 public:
  struct Attenuation {
    float constant;
    float linear;
    float quadratic;
  };
  PhysicalLight(const PhongLight &phong_light, MeshPtr mesh, const Transform &t,
                const Attenuation &attenuation)
      : Light(phong_light),
        Transformable(t),
        mesh(std::move(mesh)),
        attenuation(attenuation) {}
  const Mesh &getMesh() const { return *mesh; }
  float getConstant() const { return attenuation.constant; }
  float getLinear() const { return attenuation.linear; }
  float getQuadratic() const { return attenuation.quadratic; }

 protected:
  MeshPtr mesh;
  Attenuation attenuation;
};

class PointLight : public PhysicalLight {
 public:
  PointLight(MeshPtr model, const Transform &t, const PhongLight &phong_light,
             const Attenuation &attenuation)
      : PhysicalLight(phong_light, std::move(model), t, attenuation) {}

 private:
};

using PointLightPtr = std::unique_ptr<PointLight>;

class SpotLight : public PhysicalLight {
 public:
  SpotLight(MeshPtr model, const Transform &t, const PhongLight &phong_light,
            const glm::vec3 &direction, float cut_off, float outer_cut_off,
            const Attenuation &attenuation)
      : PhysicalLight(phong_light, std::move(model), t, attenuation),
        direction(direction),
        cut_off(cut_off),
        outer_cut_off(outer_cut_off) {}
  const glm::vec3 &getDirection() const { return direction; }
  float getCutOff() const { return cut_off; }
  float getOuterCutOff() const { return outer_cut_off; }

 private:
  glm::vec3 direction;
  float cut_off;
  float outer_cut_off;
};

using SpotLightPtr = std::unique_ptr<SpotLight>;

class DirLight : public Light {
 public:
  DirLight(const PhongLight &phong_light, const glm::vec3 &direction)
      : Light(phong_light), direction(direction) {}
  const glm::vec3 &getDirection() const { return direction; }

 private:
  glm::vec3 direction;
};

using DirLightPtr = std::unique_ptr<DirLight>;

}  // namespace helios
