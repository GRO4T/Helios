#include "texture/texture_manager.hpp"

namespace game_engine {

std::map<TextureManager::Filepath, TextureSPtr> TextureManager::texture_map;

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

Texture& TextureManager::getTexture(const std::string& filepath) {
    auto it = texture_map.find(filepath);
    if (it != texture_map.end()) {
        return *it->second;
    } else {
        TextureSPtr texture = std::make_shared<Texture>(filepath);
        texture_map.insert(std::pair(filepath, texture));
        return *texture;
    }
}

void TextureManager::loadTexture(const std::string& filepath) {
    TextureSPtr texture = std::make_shared<Texture>(filepath);
    texture_map.insert(std::pair(filepath, texture));
}

}  // namespace game_engine