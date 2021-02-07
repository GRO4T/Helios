#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "camera.hpp"
#include "opengl_all.hpp"
#include "stb_image.h"
#include <ctime>
#include <random>

// class Entity;

namespace game_engine {

namespace utils {

class Loader {
public:
    static Loader &getInstance();
    static GLuint loadMipmapTexture(const char *filename);
    static GLuint loadCubemap(const std::vector<std::string> &faces);

private:
    Loader();
    Loader(const Loader &) = delete;
    Loader &operator=(const Loader &) = delete;
};

struct Transform {
    Transform() { reset(); }
    Transform(const glm::vec3 &pos, const glm::vec3 &rot,
              const glm::vec3 &scale) {
        position = pos;
        rotation = rot;
        this->scale = scale;
    }
    void reset() {
        position = rotation = glm::vec3(0, 0, 0);
        scale = glm::vec3(1, 1, 1);
    }
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

class Image {
public:
    void load(const std::string &path);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getNrChannels() const { return nr_channels; }
    unsigned char *getData() const { return data.get(); }
    float getRGB(int x, int y) const {
        unsigned bytes_per_pixel = nr_channels;
        unsigned char *pixel_offset =
            data.get() + (y * width + x) * bytes_per_pixel;
        unsigned char r = pixel_offset[0];
        unsigned char g = pixel_offset[1];
        unsigned char b = pixel_offset[2];
        return (float)(r * g * b);
    }

private:
    int width;
    int height;
    int nr_channels;
    std::unique_ptr<unsigned char[]> data;
};

void createViewMatrix(glm::mat4 &view, const Camera &camera);
void createTransformMatrix(glm::mat4 &transformation_matrix,
                           const Transform &object_transform);

std::ostream &operator<<(std::ostream &os, const glm::mat4 &mx);
std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec);
std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec);

glm::vec3 lerp(const glm::vec3 &a, const glm::vec3 &b, float ratio);

glm::vec3 rotate_x(const glm::vec3 &v, float angle);
glm::vec3 rotate_y(const glm::vec3 &v, float angle);
glm::vec3 rotate_z(const glm::vec3 &v, float angle);

class RandomNumberGenerator {
public:
    static RandomNumberGenerator& getInstance();

    RandomNumberGenerator(const RandomNumberGenerator&) = delete;
    RandomNumberGenerator& operator=(const RandomNumberGenerator&) = delete;

    float random_0_1();

    template <int a, int b>
    float random() {
        static std::uniform_real_distribution<float> dis(a, b);
        return dis(generator_);
    }

private:
    RandomNumberGenerator();

    std::mt19937 generator_;
    std::uniform_real_distribution<float> dis_0_1;
};

}  // namespace utils

}  // namespace game_engine