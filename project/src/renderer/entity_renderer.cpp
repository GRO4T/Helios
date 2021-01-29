#include "renderer/entity_renderer.hpp"

#include "utils.hpp"

namespace game_engine {

using utils::Transform;

EntityRenderer::EntityRenderer(const glm::mat4& projection_matrix) {
    shader.use();
    shader.setProjectionMatrix(projection_matrix);
    //shader.setInt("texture0", 0);
    //shader.setInt("Texture1", 1);
}

void EntityRenderer::render(std::vector<Entity*>& entities, const Camera& camera) {
    shader.use();
    shader.setViewMatrix(camera);

    for (auto& entity : entities) {
        const auto& model = entity->getMaterializedModel().getModel();
        glm::mat4 transform_matrix;
        utils::createTransformMatrix(transform_matrix, entity->getTransform());
        shader.setTransformationMatrix(transform_matrix);
        prepareInstance(*entity);
        model.draw();
        unbind(model);
        renderChildren(*entity, transform_matrix);
    }
}

void EntityRenderer::renderChildren(Entity& parent, glm::mat4 combined_transform) {
    for (auto& child : parent.getChildren()) {
        Entity& entity = (Entity&)*child;
        glm::mat4 transform_matrix;
        utils::createTransformMatrix(transform_matrix, entity.getTransform());
        shader.setTransformationMatrix(combined_transform * transform_matrix);
        prepareInstance(entity);
        entity.getMaterializedModel().getModel().draw();
        unbind(entity.getMaterializedModel().getModel());
        renderChildren(entity, combined_transform * transform_matrix);
    }
}

void EntityRenderer::unbind(const Model& model) { glBindVertexArray(0); }

void EntityRenderer::prepareInstance(const Entity& entity) {
    const auto& texture = entity.getMaterializedModel().getMaterial().texture;
    glBindVertexArray(entity.getMaterializedModel().getModel().getVao());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTexture());
    glUniform1i(glGetUniformLocation(shader.getProgramID(), texture.getTextureUnitShaderName()),
                texture.getTextureUnitShaderID());
}

}