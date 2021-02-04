#pragma once

#include "model/model.hpp"
#include "utils.hpp"

namespace game_engine {

using utils::Transform;
class Light {
public:
    Light(ModelPtr model, const Transform &t, const glm::vec3 &object_color,
          const glm::vec3 &light_color)
        : model(std::move(model)),
          transform(t),
          object_color(object_color),
          light_color(light_color) {}

    void setTransform(const Transform &transform) { this->transform = transform; }
    const Transform &getTransform() const { return transform; }
    const Model &getModel() const { return *model; }
    const glm::vec3 &getObjectColor() const { return object_color; }
    const glm::vec3 &getLightColor() const { return light_color; }

private:
    Transform transform;
    ModelPtr model;

    glm::vec3 object_color;
    glm::vec3 light_color;
};

using LightPtr = std::unique_ptr<Light>;

}  // namespace game_engine
