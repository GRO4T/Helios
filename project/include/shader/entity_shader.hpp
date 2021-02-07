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

    void setPointLight(const std::string& name, const PointLight& light) const {
        setVec3(name + ".ambient", light.getAmbient());
        setVec3(name + ".diffuse", light.getDiffuse());
        setVec3(name + ".specular", light.getSpecular());
        setVec3(name + ".position", light.getTransform().position);
        setFloat(name + ".constant", light.getConstant());
        setFloat(name + ".linear", light.getLinear());
        setFloat(name + ".quadratic", light.getQuadratic());
    }

    void setDirLight(const std::string& name, const DirLight& light) const {
        setVec3(name + ".ambient", light.getAmbient());
        setVec3(name + ".diffuse", light.getDiffuse());
        setVec3(name + ".specular", light.getSpecular());
        setVec3(name + ".direction", light.getDirection());
    }

    void setSpotLight(const std::string& name, const SpotLight& light) const {
        setVec3(name + ".ambient", light.getAmbient());
        setVec3(name + ".diffuse", light.getDiffuse());
        setVec3(name + ".specular", light.getSpecular());
        setVec3(name + ".position", light.getTransform().position);
        setVec3(name + ".direction", light.getDirection());
        setFloat(name + ".cut_off", std::cos(glm::radians(light.getCutOff())));
        setFloat(name + ".outer_cut_off",
                 std::cos(glm::radians(light.getOuterCutOff())));
    }

    void setGlobalLight(const std::string& name, const Light& light) const {
        setVec3(name + ".ambient", light.getAmbient());
        setVec3(name + ".diffuse", light.getDiffuse());
        setVec3(name + ".specular", light.getSpecular());
    }
};

}  // namespace game_engine