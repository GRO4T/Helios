#pragma once

#include <Entity.hpp>
#include <model/Mesh.hpp>
#include <model/PrimitiveMesh.hpp>
#include <shader/EntityShader.hpp>

#include "Camera.hpp"
#include "EntityRenderer.hpp"
#include "LightRenderer.hpp"
#include "opengl_all.hpp"

namespace helios {

class MasterRenderer {
public:
    MasterRenderer();

    static void calculateProjectionMatrix(float fov, float znear, float zfar,
                                          float display_width,
                                          float display_height);

    void registerObject(Entity& object) { entities.push_back(&object); }
    void registerObject(PointLight& object) {
        point_lights.push_back(&object);
        physical_lights.push_back(&object);
    }
    void registerObject(DirLight& object) { dir_light = &object; }
    void registerObject(SpotLight& object) {
        spot_lights.push_back(&object);
        physical_lights.push_back(&object);
    }

    void setGlobalLight(Light& light) { global_light = &light; }

    void render(const Camera& camera, double time);

private:
    static glm::mat4 projection_matrix;

    EntityRenderer entity_renderer;
    LightRenderer light_renderer;

    std::vector<Entity*> entities;
    std::vector<PointLight*> point_lights;
    DirLight* dir_light = nullptr;
    std::vector<SpotLight*> spot_lights;
    std::vector<PhysicalLight*> physical_lights;
    Light* global_light = nullptr;
};

}  // namespace game_engine