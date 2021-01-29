#pragma once

#include <vector>

#include "entity/entity.hpp"
#include "shader/entity_shader.hpp"

namespace game_engine {

class EntityRenderer {
public:
    EntityRenderer(const glm::mat4& projection_matrix);
    void render(std::vector<Entity*>& entities, const Camera& camera);

private:
    void unbind(const Model& model);
    void prepareInstance(const Entity& entity);
    void prepareInstanceShadows(const Entity& entity);
    void renderChildren(Entity& parent, glm::mat4 combined_transform);
    void renderChildrenShadows(Entity& parent, glm::mat4 combined_transform,
                               glm::mat4 lightSpaceMatrix);

    EntityShader shader;
};

}