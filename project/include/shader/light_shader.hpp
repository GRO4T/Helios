#pragma once

#include "shader_program.hpp"
#include "utils.hpp"

namespace game_engine {

using namespace utils;

class LightShader : public ShaderProgram {
public:
    LightShader()
        : ShaderProgram("res/shaders/light_shader.vert", "res/shaders/light_shader.frag") {}
};

}  // namespace game_engine
