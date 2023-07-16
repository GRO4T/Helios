#pragma once

#include <map>
#include <memory>
#include <string>

#include "Helios/Core/Utils.hpp"
#include "opengl_includes.hpp"

namespace helios {

class Texture {
 public:
  Texture(GLuint texture_id) { this->texture_id = texture_id; }
  Texture(const std::string& texture_path) { load(texture_path); }

  // copy constructor and assignment operator mess up the texture
  Texture(const Texture& tex) = delete;
  Texture& operator=(const Texture& tex) = delete;

  // because of this destructor textures either have strict ownership or are
  // managed in TextureManager
  virtual ~Texture() { glDeleteTextures(1, &texture_id); }
  GLuint getTextureId() const { return texture_id; }
  void setTextureId(GLuint id) { id = id; }
  void load(const std::string& texture_path) {
    int width, height, nr_channels;
    GLenum format;

    unsigned char* data =
        stbi_load(texture_path.c_str(), &width, &height, &nr_channels, 0);
    if (data == nullptr) {
      stbi_image_free(data);
      throw std::runtime_error("Failed to load texture file");
    }

    if (nr_channels == 1)
      format = GL_RED;
    else if (nr_channels == 3)
      format = GL_RGB;
    else if (nr_channels == 4)
      format = GL_RGBA;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*
    glPixelStorei(GL_UNPACK_ALIGNMENT,
                  1);  // this line fixes random seqfaults
    //
    https://stackoverflow.com/questions/9950546/c-opengl-glteximage2d-access-violation
     */
    stbi_image_free(data);
  }

 private:
  GLuint texture_id;
};

using TexturePtr = std::unique_ptr<Texture>;
using TextureSPtr = std::shared_ptr<Texture>;

}  // namespace helios
