#pragma once

#include <map>
#include <memory>
#include <string>

#include "opengl_all.hpp"
#include "utils.hpp"

namespace game_engine {

class Texture {
public:
    enum class Type {
        DIFFUSE,
        SPECULAR
    };

    Texture(const std::string &texture_path) {
        load(texture_path);
    }
    virtual ~Texture() { glDeleteTextures(1, &texture); }
    GLuint getId() const { return texture; }
    void setId(GLuint id) { texture = id; }
    void load(const std::string&texture_path) {
        int width, height, nrChannels;
        unsigned char *image =
            stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
        if (image == nullptr)
            throw std::runtime_error("Failed to load texture file");

        //GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

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
    GLuint texture;
};

using TexturePtr = std::unique_ptr<Texture>;
using TextureSPtr = std::shared_ptr<Texture>;

}  // namespace game_engine