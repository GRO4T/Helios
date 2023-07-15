#include "renderer/EntityRenderer.hpp"

#include "Utils.hpp"

namespace helios {

using utils::Transform;

EntityRenderer::EntityRenderer(const glm::mat4& projection_matrix)
    : outline_shader("res/shaders/outline_shader.vert",
                     "res/shaders/outline_shader.frag") {
    entity_shader.use();
    entity_shader.setProjectionMatrix(projection_matrix);
    outline_shader.use();
    outline_shader.setProjectionMatrix(projection_matrix);
}

void EntityRenderer::render(const std::vector<Entity*>& entities,
                            const Camera& camera,
                            const std::vector<PointLight*>& point_lights,
                            const DirLight& dir_light,
                            const std::vector<SpotLight*>& spot_lights,
                            const Light& global_light) const {

    entity_shader.use();
    entity_shader.setViewMatrix(camera);
    entity_shader.setVec3("camera_position", camera.getPosition());
    setLights(point_lights, dir_light, spot_lights, global_light);

    // tmp
    std::vector<Entity*> normal_entities(entities.begin() + 1,
                                         entities.end());
    std::vector<Entity*> outlined_entities(entities.begin(),
                                           entities.begin() + 1);
    glStencilMask(0x00);
    drawEntities(entities);
    drawOutlinedEntities(outlined_entities, camera);

    entity_shader.resetPointLights(point_lights);
    entity_shader.resetSpotLights(spot_lights);
}

void EntityRenderer::unbind() const { glBindVertexArray(0); }

void EntityRenderer::setLights(const std::vector<PointLight*>& point_lights,
                               const DirLight& dir_light,
                               const std::vector<SpotLight*>& spot_lights,
                               const Light& global_light) const {
    if (&dir_light != nullptr) entity_shader.setDirLight(dir_light);
    entity_shader.setPointLights(point_lights);
    entity_shader.setSpotLights(spot_lights);
    if (&global_light != nullptr)
        entity_shader.setGlobalLight("global_light", global_light);
}
void EntityRenderer::drawEntities(const std::vector<Entity*>& entities) const {
    for (auto& entity : entities) {
        glm::mat4 transform_matrix;
        utils::createTransformMatrix(transform_matrix, entity->getTransform());
        entity_shader.setTransformationMatrix(transform_matrix);

        for (const auto& materialized_mesh : entity->getModel().meshes) {
            glBindVertexArray(materialized_mesh->getMesh().getVao());
            entity_shader.setMaterial(materialized_mesh->getMaterial());
            materialized_mesh->getMesh().draw();
            unbind();
        }
    }
}
void EntityRenderer::drawOutlinedEntities(const std::vector<Entity*>& entities,
                                  const Camera& camera) const {
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    drawEntities(entities);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    outline_shader.use();
    outline_shader.setViewMatrix(camera);
    outline_shader.setVec3("camera_position", camera.getPosition());
    drawOutline(entities, 0.02f);
    glStencilMask(0xFF);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);
}

void EntityRenderer::drawOutline(const std::vector<Entity*>& entities,
                                  float scale_up) const {
    for (auto& entity : entities) {
        glm::mat4 transform_matrix;
        Transform scaled_up_transform(entity->getTransform());
        scaled_up_transform.scale += scale_up;
        utils::createTransformMatrix(transform_matrix, scaled_up_transform);
        outline_shader.setTransformationMatrix(transform_matrix);

        for (const auto& materialized_mesh : entity->getModel().meshes) {
            glBindVertexArray(materialized_mesh->getMesh().getVao());
            materialized_mesh->getMesh().draw();
            unbind();
        }
    }
}

}  // namespace helios