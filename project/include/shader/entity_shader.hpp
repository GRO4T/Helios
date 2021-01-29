#pragma once

#include "shader_program.hpp"

namespace game_engine {

class EntityShader : public ShaderProgram {
public:
    EntityShader()
        : ShaderProgram("res/shaders/entity_shader.vert", "res/shaders/entity_shader.frag") {}
};

}  // namespace game_engine