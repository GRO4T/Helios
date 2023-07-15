#include "renderer/MasterRenderer.hpp"

#include <Utils.hpp>

namespace game_engine {

glm::mat4 MasterRenderer::projection_matrix;

MasterRenderer::MasterRenderer()
    : entity_renderer(projection_matrix), light_renderer(projection_matrix) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
}

void MasterRenderer::calculateProjectionMatrix(float fov, float znear,
                                               float zfar, float display_width,
                                               float display_height) {
    projection_matrix = glm::mat4(1.0f);
    projection_matrix = glm::perspective(
        glm::radians(fov), display_width / display_height, znear, zfar);
}

void MasterRenderer::render(const Camera& camera, double time) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    entity_renderer.render(entities, camera, point_lights, *dir_light,
                           spot_lights, *global_light);
    light_renderer.render(physical_lights, camera);
}

}  // namespace game_engine