#pragma once

#include "shader_program.hpp"
#include "utils.hpp"

namespace game_engine {

using namespace utils;

class LightShader : public ShaderProgram {
public:
    LightShader()
        : ShaderProgram("res/shaders/light_shader.vert",
                        "res/shaders/light_shader.frag") {}
    void setLight(const std::string& name, const Light& light) {
        setVec3(name + ".ambient", light.getAmbient());
        setVec3(name + ".diffuse", light.getDiffuse());
        setVec3(name + ".specular", light.getSpecular());
    }
};

}  // namespace game_engine
