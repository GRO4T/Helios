#include "renderer/master_renderer.hpp"

#include <utils.hpp>

namespace game_engine {

glm::mat4 MasterRenderer::projection_matrix;

void MasterRenderer::calculateProjectionMatrix(float fov, float znear, float zfar,
                                               float display_width, float display_height) {
    projection_matrix = glm::mat4(1.0f);
    projection_matrix =
        glm::perspective(glm::radians(fov), display_width / display_height, znear, zfar);
}

void MasterRenderer::render(const Camera& camera, float time) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    entity_renderer.render(entities, camera, lights);
    light_renderer.render(lights, camera);
}

}  // namespace game_engine