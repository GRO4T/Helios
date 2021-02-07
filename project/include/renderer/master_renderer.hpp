#pragma once

#include <entity/entity.hpp>
#include <model/model.hpp>
#include <model/primitive.hpp>
#include <shader/entity_shader.hpp>

#include "camera.hpp"
#include "entity_renderer.hpp"
#include "light_renderer.hpp"
#include "opengl_all.hpp"

namespace game_engine {

class MasterRenderer {
public:
    MasterRenderer()
        : entity_renderer(projection_matrix),
          light_renderer(projection_matrix) {}

    static void calculateProjectionMatrix(float fov, float znear, float zfar,
                                          float display_width,
                                          float display_height);

    void registerObject(Entity* object) { entities.push_back(object); }
    void registerObject(PointLight* object) { point_lights.push_back(object); }
    void registerObject(DirLight* object) { dir_light = object; }

    void render(const Camera& camera, float time);

private:
    static glm::mat4 projection_matrix;

    EntityRenderer entity_renderer;
    LightRenderer light_renderer;

    std::vector<Entity*> entities;
    std::vector<PointLight*> point_lights;
    DirLight* dir_light = nullptr;
};

}  // namespace game_engine