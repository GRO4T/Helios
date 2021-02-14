#include "renderer/entity_renderer.hpp"

#include "utils.hpp"

namespace game_engine {

using utils::Transform;

EntityRenderer::EntityRenderer(const glm::mat4& projection_matrix) {
    shader.use();
    shader.setProjectionMatrix(projection_matrix);
}

void EntityRenderer::render(std::vector<Entity*>& entities,
                            const Camera& camera,
                            std::vector<PointLight*>& point_lights,
                            DirLight* dir_light,
                            std::vector<SpotLight*>& spot_lights,
                            Light* global_light) {
    shader.use();
    shader.setViewMatrix(camera);

    shader.setVec3("camera_position", camera.getPosition());
    if (dir_light != nullptr) shader.setDirLight(*dir_light);
    shader.setPointLights(point_lights);
    shader.setSpotLights(spot_lights);
    if (global_light != nullptr)
        shader.setGlobalLight("global_light", *global_light);

    for (auto& entity : entities) {
        glm::mat4 transform_matrix;
        utils::createTransformMatrix(transform_matrix, entity->getTransform());
        shader.setTransformationMatrix(transform_matrix);

        for (const auto& materialized_mesh : entity->getModel().meshes) {
            glBindVertexArray(materialized_mesh->getMesh().getVao());
            shader.setMaterial("material", materialized_mesh->getMaterial());
            materialized_mesh->getMesh().draw();
            unbind();
        }
        renderChildren(*entity, transform_matrix);
    }

    shader.resetPointLights(point_lights);
    shader.resetSpotLights(spot_lights);
}

void EntityRenderer::renderChildren(Entity& parent,
                                    glm::mat4 combined_transform) {
    for (auto& child : parent.getChildren()) {
        Entity& entity = (Entity&)*child;
        glm::mat4 transform_matrix;
        utils::createTransformMatrix(transform_matrix, entity.getTransform());
        shader.setTransformationMatrix(combined_transform * transform_matrix);

        for (const auto& materialized_mesh : entity.getModel().meshes) {
            glBindVertexArray(materialized_mesh->getMesh().getVao());
            shader.setMaterial("material", materialized_mesh->getMaterial());
            materialized_mesh->getMesh().draw();
            unbind();
        }
        renderChildren(entity, combined_transform * transform_matrix);
    }
}

void EntityRenderer::unbind() { glBindVertexArray(0); }

}  // namespace game_engine