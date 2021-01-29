#include "renderer/master_renderer.hpp"

#include <utils.hpp>

namespace game_engine {

glm::mat4 MasterRenderer::projection_matrix;

void MasterRenderer::calculateProjectionMatrix(float fov, float znear, float zfar, float display_width, float display_height) {
    projection_matrix = glm::mat4(1.0f);
    projection_matrix =
        glm::perspective(glm::radians(fov), display_width / display_height, znear, zfar);
}

void MasterRenderer::render(const Camera& camera, float time) {
    shader.use();
    shader.setProjectionMatrix(projection_matrix);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    utils::Transform t;
    glm::mat4 transform_mat;
    utils::createTransformMatrix(transform_mat, t);
    shader.use();
    shader.setViewMatrix(camera);
    shader.setTransformationMatrix(transform_mat);
    //basic_shader.setViewMatrix(camera);
    ModelPtr model = std::make_unique<Model>();
    model->load(cube(1.0f));

    glBindVertexArray(model->getVao());
    model->draw();

    /*
    entity_renderer.render(entities, camera);
    terrain_renderer.render(terrains, camera);
    skybox_renderer.render(skybox, camera);
    water_renderer.render(water, camera, time);

    entities.clear();
    terrains.clear();
     */
}

}