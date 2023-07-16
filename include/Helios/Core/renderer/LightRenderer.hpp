#pragma once

#include "Helios/Core/Light.hpp"
#include "Helios/Core/shader/LightShader.hpp"
#include "opengl_includes.hpp"

namespace helios {

class LightRenderer {
 public:
  LightRenderer(const glm::mat4& projection_matrix) {
    shader.use();
    shader.setProjectionMatrix(projection_matrix);
  }

  void render(std::vector<PhysicalLight*>& lights, const Camera& camera) {
    glClear(GL_STENCIL_BUFFER_BIT);
    shader.use();
    shader.setViewMatrix(camera);

    for (auto& light : lights) {
      const auto& mesh = light->getMesh();
      glm::mat4 transform_matrix;
      utils::createTransformMatrix(transform_matrix, light->getTransform());
      shader.setTransformationMatrix(transform_matrix);
      prepareInstance(*light);
      mesh.draw();
      unbind(mesh);
    }
  }

 private:
  void unbind(const Mesh& model) { glBindVertexArray(0); }
  void prepareInstance(const PhysicalLight& light) {
    glBindVertexArray(light.getMesh().getVao());
    shader.setLight(light);
  }

  LightShader shader;
};

}  // namespace helios