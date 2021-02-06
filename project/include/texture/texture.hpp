#pragma once

#include <map>
#include <memory>
#include <string>

#include "opengl_all.hpp"
#include "utils.hpp"

namespace game_engine {

class Texture {
public:
    Texture(const std::string& texture_path) {
        texture = utils::Loader::getInstance().loadMipmapTexture(
            texture_path.c_str());
    }
    virtual ~Texture() { glDeleteTextures(1, &texture); }
    GLuint getTexture() const { return texture; }

private:
    GLuint texture;
};

using TexturePtr = std::unique_ptr<Texture>;
using TextureSPtr = std::shared_ptr<Texture>;

}  // namespace game_engine