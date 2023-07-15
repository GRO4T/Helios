#pragma once

#include <vector>

#include "Entity.hpp"
#include "shader/EntityShader.hpp"

namespace helios {

class EntityRenderer {
public:
    EntityRenderer(const glm::mat4& projection_matrix);
    void render(const std::vector<Entity*>& entities, const Camera& camera,
                const std::vector<PointLight*>& point_lights,
                const DirLight& dir_light,
                const std::vector<SpotLight*>& spot_lights,
                const Light& global_light) const;

private:
    void unbind() const;
    void setLights(const std::vector<PointLight*>& point_lights,
                   const DirLight& dir_light,
                   const std::vector<SpotLight*>& spot_lights,
                   const Light& global_light) const;
    void drawEntities(const std::vector<Entity*>& entities) const;
    void drawOutline(const std::vector<Entity*>& entities, float scale_up) const;
    void drawOutlinedEntities(const std::vector<Entity*>& entities, const Camera& camera) const;

    EntityShader entity_shader;
    ShaderProgram outline_shader;
};

}  // namespace helios