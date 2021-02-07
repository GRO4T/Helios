#pragma once

#include <light.hpp>

#include "shader_program.hpp"
#include "utils.hpp"

namespace game_engine {

using namespace utils;

class EntityShader : public ShaderProgram {
public:
    EntityShader()
        : ShaderProgram("res/shaders/entity_shader.vert",
                        "res/shaders/entity_shader.frag") {}

    void setMaterial(const std::string& name, const Material& material) const {
        setBool(name + ".is_diffuse_map", material.isDiffuseMap());
        if (material.isDiffuseMap()) {
            setInt(name + ".diffuse_map", 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,
                          material.getDiffuseMap()->getTexture());
        } else {
            setVec3(name + ".diffuse", material.getDiffuse());
        }
        setVec3(name + ".ambient", material.getAmbient());
        setBool(name + ".is_specular_map", material.isSpecularMap());
        if (material.isSpecularMap()) {
            setInt(name + ".specular_map", 1);
            glActiveTexture(GL_TEXTURE0 + 1);
            glBindTexture(GL_TEXTURE_2D,
                          material.getSpecularMap()->getTexture());
        } else {
            setVec3(name + ".specular", material.getSpecular());
        }
        setFloat(name + ".shininess", material.getShininess());
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

    void setPointLights(const std::vector<PointLight*> lights) {
        for (int i = 0; const auto& light : lights) {
            setPointLight(*light, i++);
        }
    }

    void resetPointLights(const std::vector<PointLight*> lights) {
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
        const std::string spot_light =
            "spot_lights[" + std::to_string(index) + "]";
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

    void setSpotLights(const std::vector<SpotLight*>& lights) {
        for (int i = 0; const auto& light : lights) {
            setSpotLight(*light, i++);
        }
    }

    void resetSpotLights(const std::vector<SpotLight*>& lights) {
        for (int i = 0; const auto& light : lights) {
            const std::string spot_light =
                "spot_lights[" + std::to_string(i++) + "]";
            setBool(spot_light + ".enabled", false);
        }
    }

    void setGlobalLight(const std::string& name, const Light& light) const {
        setVec3(name + ".ambient", light.getAmbient());
        setVec3(name + ".diffuse", light.getDiffuse());
        setVec3(name + ".specular", light.getSpecular());
    }
};

}  // namespace game_engine