#pragma once

#include "ShaderProgram.hpp"
#include "Utils.hpp"

namespace helios {

using namespace utils;

class LightShader : public ShaderProgram {
public:
    LightShader()
        : ShaderProgram("res/shaders/light_shader.vert",
                        "res/shaders/light_shader.frag") {}
    void setLight(const Light& light) {
        const std::string name = "light";
        setVec3(name + ".ambient", light.getAmbient());
        setVec3(name + ".diffuse", light.getDiffuse());
        setVec3(name + ".specular", light.getSpecular());
    }
};

}  // namespace helios
