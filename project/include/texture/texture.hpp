#pragma once

#include <map>
#include <memory>
#include <string>

#include "opengl_all.hpp"
#include "utils.hpp"

namespace game_engine {

class Texture {
public:
    Texture(GLuint texture_unit, const std::string& texture_path, GLuint texture_unit_shader_id = GL_TEXTURE0)
        : texture_unit(texture_unit), texture_unit_shader_id(texture_unit_shader_id) {
        texture =
            utils::Loader::getInstance().loadMipmapTexture(texture_unit, texture_path.c_str());
    }
    Texture(GLuint texture_unit, const std::vector<std::string>& texture_paths,
            GLuint texture_unit_shader_id = GL_TEXTURE0)
        : texture_unit(texture_unit), texture_unit_shader_id(texture_unit_shader_id) {
        texture = utils::Loader::getInstance().loadCubemap(texture_paths);
    }
    virtual ~Texture() { glDeleteTextures(1, &texture); }
    GLuint getTexture() const { return texture; }
    GLuint getTextureUnit() const { return texture_unit; }
    GLuint getTextureUnitShaderID() const { return texture_unit_shader_id; }

private:
    GLuint texture;
    GLuint texture_unit;
    GLuint texture_unit_shader_id;
};

using TexturePtr = std::unique_ptr<Texture>;
using TextureSPtr = std::shared_ptr<Texture>;

}  // namespace game_engine