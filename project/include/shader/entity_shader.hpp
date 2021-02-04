#pragma once

#include "shader_program.hpp"
#include "utils.hpp"

namespace game_engine {

using namespace utils;

class EntityShader : public ShaderProgram {
public:
    EntityShader()
        : ShaderProgram("res/shaders/entity_shader.vert", "res/shaders/entity_shader.frag") {}

    void setMaterial(const std::string& name, const Material& material) const {
        setVec3(name + ".ambient", material.ambient);
        setVec3(name + ".diffuse", material.diffuse);
        setVec3(name + ".specular", material.specular);
        setFloat(name + ".shininess", material.shininess);
        setFloat(name + ".alpha", material.alpha);
        std::cout << material.base_color << std::endl;
        setVec4(name + ".base_color", material.base_color);
        glActiveTexture(material.texture->getTextureUnitShaderID());
        glBindTexture(GL_TEXTURE_2D, material.texture->getTexture());
        setInt(name + ".texture", material.texture->getTextureUnitShaderID());
    }
};

}  // namespace game_engine