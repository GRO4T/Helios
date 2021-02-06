#pragma once
/*
#include "cubemap.hpp"
#include "entity/entity.hpp"
#include "entity_renderer.hpp"
#include "lighting/lighting.hpp"
#include "shader/entity_shader.hpp"
#include "shader/skybox_shader.hpp"
#include "shader/terrain_shader.hpp"
 */
//#include "skybox_renderer.hpp"
//#include "terrain.hpp"
//#include "terrain_renderer.hpp"
//#include "water_renderer.hpp"

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
    /*
    terrain_renderer(projection_matrix),
    skybox_renderer(projection_matrix),
    water_renderer(projection_matrix) {}
    */

    static void calculateProjectionMatrix(float fov, float znear, float zfar,
                                          float display_width,
                                          float display_height);

    // void registerObject(TerrainSharedPtr terrain) {
    // terrains.push_back(terrain); }
    void registerObject(Entity* object) { entities.push_back(object); }
    void registerObject(Light* object) { lights.push_back(object); }
    /*
    void registerForShadows(EntitySPtr entity) {
    entity_renderer.registerForShadows(entity); } void
    registerObject(CubemapSharedPtr cubemap) { this->skybox = cubemap; } void
    registerObject(WaterSharedPtr water_) { this->water = water_; }
     */

    void render(const Camera& camera, float time);

    // EntityRenderer getEntityRenderer() { return entity_renderer; }

private:
    static glm::mat4 projection_matrix;

    EntityRenderer entity_renderer;
    LightRenderer light_renderer;

    std::vector<Entity*> entities;
    std::vector<Light*> lights;

    /*
    std::vector<TerrainSharedPtr> terrains;
    CubemapSharedPtr skybox;
    WaterSharedPtr water;

    TerrainRenderer terrain_renderer;
    SkyboxRenderer skybox_renderer;
    WaterRenderer water_renderer;
     */
};

}  // namespace game_engine