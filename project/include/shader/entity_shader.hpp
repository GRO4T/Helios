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
        setVec3(name + ".ambient", material.ambient);
        setVec3(name + ".diffuse", material.diffuse);
        setVec3(name + ".specular", material.specular);
        setFloat(name + ".shininess", material.shininess);
        glActiveTexture(material.texture->getTextureUnitShaderID());
        glBindTexture(GL_TEXTURE_2D, material.texture->getTexture());
        setInt(name + ".texture", material.texture->getTextureUnitShaderID());
    }

    void setLight(const std::string& name, const Light& light) const {
        setVec3(name + ".ambient", light.getAmbient());
        setVec3(name + ".diffuse", light.getDiffuse());
        setVec3(name + ".specular", light.getSpecular());
        setVec3(name + ".position", light.getTransform().position);
    }
};

}  // namespace game_engine