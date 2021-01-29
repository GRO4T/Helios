#include "texture/texture.hpp"

namespace game_engine {

const std::map<GLuint, const char*> Texture::texture_unit_shader_name_map{
    {GL_TEXTURE0, "texture0"}, {GL_TEXTURE1, "texture1"}};

const std::map<GLuint, int> Texture::texture_unit_shader_id_map{{GL_TEXTURE0, 0}, {GL_TEXTURE1, 1}};

}  // namespace game_engine
