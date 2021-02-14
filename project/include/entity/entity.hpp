#pragma once

#include <vector>

#include "entity/abstract_entity.hpp"

namespace game_engine {

using utils::Transform;

class Entity : public AbstractEntity {
public:
    Entity() {}
    Entity(ModelPtr model, const Transform& transform)
        : AbstractEntity(transform),
          model(std::move(model)) {}
    Entity(const Entity&) = delete;
    Entity(Entity&& e) = delete;
    virtual ~Entity() {}

    Model& getModel() const override { return *model; }

    void addChild(AbstractEntitySharedPtr child) { children.push_back(child); }
    std::vector<AbstractEntitySharedPtr>& getChildren() { return children; }

private:
    Transform transform;
    ModelPtr model;

    std::vector<AbstractEntitySharedPtr> children;
};

using EntityPtr = std::unique_ptr<Entity>;
using EntitySPtr = std::shared_ptr<Entity>;

}  // namespace game_engine