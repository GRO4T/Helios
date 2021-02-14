#pragma once

#include <map>
#include <memory>
#include <string>

#include "opengl_all.hpp"
#include "utils.hpp"

namespace game_engine {

class Texture {
public:
    Texture(GLuint texture_id) { id = texture_id; }
    Texture(const std::string& texture_path) { load(texture_path); }

    // copy constructor and assignment operator mess up the texture
    Texture(const Texture& tex) = delete;
    Texture& operator=(const Texture& tex) = delete;

    // because of this destructor textures either have strict ownership or are
    // managed in TextureManager
    virtual ~Texture() { glDeleteTextures(1, &id); }
    GLuint getId() const { return id; }
    void setId(GLuint id) { id = id; }
    void load(const std::string& texture_path) {
        int width, height, nrChannels;
        unsigned char* image =
            stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
        if (image == nullptr)
            throw std::runtime_error("Failed to load texture file");

        // GLuint texture;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        // Set the texture wrapping parameters
        glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT);  // Set texture wrapping to GL_REPEAT (usually
        // basic wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_UNPACK_ALIGNMENT,
                      1);  // this line fixes random seqfaults
        // https://stackoverflow.com/questions/9950546/c-opengl-glteximage2d-access-violation
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        // SOIL_free_image_data(image);
        stbi_image_free(image);
    }

private:
    GLuint id;
};

using TexturePtr = std::unique_ptr<Texture>;
using TextureSPtr = std::shared_ptr<Texture>;

}  // namespace game_engine