#pragma once

#include "Helios/Core/Light.hpp"
#include "Helios/Core/shader/ShaderProgram.hpp"
#include "Helios/Core/Utils.hpp"

namespace helios {

using namespace utils;

class EntityShader : public ShaderProgram {
 public:
  EntityShader()
      : ShaderProgram("res/shaders/entity_shader.vert",
                      "res/shaders/entity_shader.frag") {}

  void setMaterial(const Material& material) const {
    const std::string name = "material";
    int i = 0, diffuse_id = 0, specular_id = 0;
    if (material.diffuse_maps.size() > 0) {
      setBool(name + ".is_diffuse_map", true);
      for (const auto& dm : material.diffuse_maps) {
        setInt(name + ".diffuse_map" + std::to_string(diffuse_id++), i);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, dm->getTextureId());
        ++i;
      }
    } else {
      setBool(name + ".is_diffuse_map", false);
      setVec3(name + ".diffuse", material.diffuse);
    }
    setVec3(name + ".ambient", material.ambient);
    if (material.specular_maps.size() > 0) {
      setBool(name + ".is_specular_map", true);
      for (const auto& sm : material.specular_maps) {
        setInt(name + ".specular_map" + std::to_string(specular_id++), i);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, sm->getTextureId());
        ++i;
      }
    } else {
      setBool(name + ".is_specular_map", false);
      setVec3(name + ".specular", material.specular);
    }
    setFloat(name + ".shininess", material.shininess);
  }

  void setPointLight(const PointLight& light, int index) const {
    const std::string point_light =
        "point_lights[" + std::to_string(index) + "]";
    setVec3(point_light + ".ambient", light.getAmbient());
    setVec3(point_light + ".diffuse", light.getDiffuse());
    setVec3(point_light + ".specular", light.getSpecular());
    setVec3(point_light + ".position", light.getTransform().position);
    setFloat(point_light + ".constant", light.getConstant());
    setFloat(point_light + ".linear", light.getLinear());
    setFloat(point_light + ".quadratic", light.getQuadratic());
    setBool(point_light + ".enabled", true);
  }

  void setPointLights(const std::vector<PointLight*> lights) const {
    for (int i = 0; const auto& light : lights) {
      setPointLight(*light, i++);
    }
  }

  void resetPointLights(const std::vector<PointLight*> lights) const {
    for (int i = 0; const auto& light : lights) {
      const std::string point_light =
          "point_lights[" + std::to_string(i++) + "]";
      setBool(point_light + ".enabled", false);
    }
  }

  void setDirLight(const DirLight& light) const {
    const std::string dir_light = "dir_light";
    setVec3(dir_light + ".ambient", light.getAmbient());
    setVec3(dir_light + ".diffuse", light.getDiffuse());
    setVec3(dir_light + ".specular", light.getSpecular());
    setVec3(dir_light + ".direction", light.getDirection());
  }

  void setSpotLight(const SpotLight& light, int index) const {
    const std::string spot_light = "spot_lights[" + std::to_string(index) + "]";
    setVec3(spot_light + ".ambient", light.getAmbient());
    setVec3(spot_light + ".diffuse", light.getDiffuse());
    setVec3(spot_light + ".specular", light.getSpecular());
    setVec3(spot_light + ".position", light.getTransform().position);
    setVec3(spot_light + ".direction", light.getDirection());
    setFloat(spot_light + ".cut_off",
             std::cos(glm::radians(light.getCutOff())));
    setFloat(spot_light + ".outer_cut_off",
             std::cos(glm::radians(light.getOuterCutOff())));
    setFloat(spot_light + ".constant", light.getConstant());
    setFloat(spot_light + ".linear", light.getLinear());
    setFloat(spot_light + ".quadratic", light.getQuadratic());
    setBool(spot_light + ".enabled", true);
  }

  void setSpotLights(const std::vector<SpotLight*>& lights) const {
    for (int i = 0; const auto& light : lights) {
      setSpotLight(*light, i++);
    }
  }

  void resetSpotLights(const std::vector<SpotLight*>& lights) const {
    for (int i = 0; const auto& light : lights) {
      const std::string spot_light = "spot_lights[" + std::to_string(i++) + "]";
      setBool(spot_light + ".enabled", false);
    }
  }

  void setGlobalLight(const std::string& name, const Light& light) const {
    setVec3(name + ".ambient", light.getAmbient());
    setVec3(name + ".diffuse", light.getDiffuse());
    setVec3(name + ".specular", light.getSpecular());
  }
};

}  // namespace helios
