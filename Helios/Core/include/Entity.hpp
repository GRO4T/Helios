#pragma once

#include <vector>

#include "Transformable.hpp"

namespace helios {

using utils::Transform;

class Entity : public Transformable {
public:
    Entity() {}
    Entity(ModelPtr model, const Transform& transform)
        : Transformable(transform),
          model(std::move(model)) {}
    Entity(const Entity&) = delete;
    Entity(Entity&& e) = delete;
    virtual ~Entity() {}

    Model& getModel() const { return *model; }

private:
    ModelPtr model;
};

using EntityPtr = std::unique_ptr<Entity>;
using EntitySPtr = std::shared_ptr<Entity>;

}  // namespace helios