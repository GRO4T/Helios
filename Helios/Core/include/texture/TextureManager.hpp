#pragma once

#include <map>

#include "Texture.hpp"

namespace game_engine {

class TextureManager {
    using Filepath = std::string;

public:
    static TextureManager& getInstance();
    static TextureSPtr getTexture(const std::string& filepath);

private:
    TextureManager() {}
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    static std::map<Filepath, TextureSPtr> texture_map;
};

}  // namespace game_engine