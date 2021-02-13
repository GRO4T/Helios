#pragma once

#include <model/materialized_mesh.hpp>
#include <vector>

#include "entity/abstract_entity.hpp"
#include "utils.hpp"

namespace game_engine {

using utils::Transform;

class Entity : public AbstractEntity {
public:
    Entity() {}
    Entity(MaterializedMeshPtr materialized_model, const Transform& transform)
        : AbstractEntity(transform),
          materialized_model(std::move(materialized_model)) {}
    Entity(const Entity&) = delete;
    Entity(Entity&& e) = delete;  // we don't use it right now
    /*
    {
        textured_model = e.textured_model;
        e.textured_model.reset();
        transform = e.transform;
    }
     */
    virtual ~Entity() {}

    MaterializedMesh& getMaterializedModel() const override {
        return *materialized_model;
    }

    void addChild(AbstractEntitySharedPtr child) { children.push_back(child); }
    std::vector<AbstractEntitySharedPtr>& getChildren() { return children; }

private:
    Transform transform;
    MaterializedMeshPtr materialized_model;

    std::vector<AbstractEntitySharedPtr> children;
};

using EntityPtr = std::unique_ptr<Entity>;
using EntitySPtr = std::shared_ptr<Entity>;

}  // namespace game_engine