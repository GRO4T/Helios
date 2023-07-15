#include "Utils.hpp"

#include <algorithm>
#include <stdexcept>

#include "opengl_all.hpp"
#include "stb_image.h"

namespace helios {

namespace utils {

void createViewMatrix(glm::mat4 &view, const Camera &camera) {
    view = glm::mat4(1.0f);
    view = glm::rotate(view, (float)glm::radians(camera.getPitch()),
                       glm::vec3(1, 0, 0));
    view = glm::rotate(view, (float)glm::radians(camera.getYaw()),
                       glm::vec3(0, 1, 0));
    view = glm::translate(view, -camera.getPosition());
}

void createTransformMatrix(glm::mat4 &transformation_matrix,
                           const Transform &object_transform) {
    transformation_matrix = glm::mat4(1.0f);
    const glm::vec3 &pos = object_transform.position;
    transformation_matrix = glm::translate(transformation_matrix, pos);
    const glm::vec3 &rot = object_transform.rotation;
    transformation_matrix = glm::rotate(
        transformation_matrix, (float)glm::radians(rot.x), glm::vec3(1, 0, 0));
    transformation_matrix = glm::rotate(
        transformation_matrix, (float)glm::radians(rot.y), glm::vec3(0, 1, 0));
    transformation_matrix = glm::rotate(
        transformation_matrix, (float)glm::radians(rot.z), glm::vec3(0, 0, 1));
    const glm::vec3 &scale = object_transform.scale;
    transformation_matrix = glm::scale(transformation_matrix, scale);
}

std::ostream &operator<<(std::ostream &os, const glm::mat4 &mx) {
    for (int Row = 0; Row < 4; ++Row) {
        for (int Col = 0; Col < 4; ++Col) os << mx[Row][Col] << ' ';
        os << std::endl;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec) {
    os << vec.r << " " << vec.g << " " << vec.b << " " << vec.a;
    return os;
}

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec) {
    os << vec.x << " " << vec.y << " " << vec.z;
    return os;
}

void Image::load(const std::string &path) {
    unsigned char *image =
        stbi_load(path.c_str(), &width, &height, &nr_channels, 0);
    if (image == nullptr)
        throw std::runtime_error("Failed to load texture file");
    std::unique_ptr<unsigned char[]> tmp(image);
    data = std::move(tmp);
}

glm::vec3 lerp(const glm::vec3 &a, const glm::vec3 &b, float ratio) {
    ratio = std::max(std::min(ratio, 1.0f), 0.0f);
    float rat_a = 1 - ratio;
    return glm::vec3(a.x * rat_a + b.x * ratio, a.y * rat_a + b.y * ratio,
                     a.z * rat_a + b.z * ratio);
}

glm::vec3 rotate_x(const glm::vec3 &v, float angle) {
    float sin = std::sin(glm::radians(angle));
    float cos = std::cos(glm::radians(angle));
    float ty = v.y;
    float tz = v.z;
    return glm::vec3(v.x, (cos * ty) - (sin * tz), (cos * tz) + (sin * ty));
}

glm::vec3 rotate_y(const glm::vec3 &v, float angle) {
    float sin = std::sin(glm::radians(angle));
    float cos = std::cos(glm::radians(angle));
    float tx = v.x;
    float tz = v.z;
    return glm::vec3((cos * tx) + (sin * tz), v.y, (cos * tz) - (sin * tx));
}

glm::vec3 rotate_z(const glm::vec3 &v, float angle) {
    float sin = std::sin(glm::radians(angle));
    float cos = std::cos(glm::radians(angle));
    float tx = v.x;
    float ty = v.y;
    return glm::vec3((cos * tx) - (sin * ty), (cos * ty) + (sin * tx), v.z);
}

RandomNumberGenerator::RandomNumberGenerator()
    : generator_(std::random_device{}()), dis_0_1(0.0, 1.0) {}

RandomNumberGenerator& RandomNumberGenerator::getInstance() {
    static RandomNumberGenerator instance;
    return instance;
}

float RandomNumberGenerator::random_0_1() { return dis_0_1(generator_); }

}  // namespace utils

}  // namespace game_engine
