#pragma once

#include <renderer/MasterRenderer.hpp>

#include "DisplayManager.hpp"
#include "Utils.hpp"

namespace helios {

/**
 * Main class of the game engine. Handles rendering and keeps track of the camera,
 * entities and light sources.
 */
class GameEngine {
 public:
  GameEngine()
      : display_manager_(DisplayManager::getInstance()),
        texture_manager_(TextureManager::getInstance()),
        renderer(),
        camera_(glm::vec3(0, 4, -10), 20, 180) {}

  /**
   * Initializes game window.
   *
   * @return true on success, false on failure
   */
  static bool init();

  /**
   * Runs game loop.
   */
  void run();

  /**
   * Registers an entity with 3D model stored in *.obj file.
   *
   * @param transform               Entity's position in the scene.
   * @param model_file_path         Path to the *.obj containing entity's 3D model.
   */
  void registerEntity(const Transform& transform,
                      const std::string& model_file_path);

  /**
   * Registers an entity with primitive mesh, diffuse and specular map.
   *
   * @tparam MaterialType           Material type (silver, gold, etc.).
   * @param transform               Entity's position in the scene.
   * @param mesh                    Entity's mesh.
   * @param diffuse_map_file_path   Path to file with diffuse map.
   * @param specular_map_file_path  Path to file with specular map.
   */
  template <typename MaterialType>
  void registerEntity(const Transform& transform, MeshPtr mesh,
                      const std::string& diffuse_map_file_path,
                      const std::string& specular_map_file_path) {
    MaterialSharedPtr material = std::make_shared<MaterialType>();
    material->diffuse_maps = {
        texture_manager_.getTexture(diffuse_map_file_path)};
    material->specular_maps.push_back(
        texture_manager_.getTexture(specular_map_file_path));
    std::vector<MaterializedMeshSharedPtr> meshes = {
        std::make_unique<MaterializedMesh>(std::move(mesh), material)};
    ModelPtr model = std::make_unique<Model>(meshes);
    EntityPtr entity = std::make_unique<Entity>(std::move(model), transform);
    entities.push_back(std::move(entity));
  }

  /**
   * Registers an entity with primitive mesh without diffuse and specular maps.
   *
   * @tparam MaterialType           Material type (silver, gold, etc.).
   * @param transform               Entity's position in the scene.
   * @param mesh                    Entity's mesh.
   */
  template <typename MaterialType>
  void registerEntity(const Transform& transform, MeshPtr mesh) {
    MaterialSharedPtr material = std::make_shared<MaterialType>();
    std::vector<MaterializedMeshSharedPtr> meshes = {
        std::make_unique<MaterializedMesh>(std::move(mesh), material)};
    ModelPtr model = std::make_unique<Model>(meshes);
    EntityPtr entity = std::make_unique<Entity>(std::move(model), transform);
    entities.push_back(std::move(entity));
  }

  /**
   * Registers a point light.
   *
   * @param transform               Light's position in the scene.
   * @param mesh                    Light's mesh. TODO: Make more descriptive.
   */
  void registerPointLight(const Transform& transform, MeshPtr mesh);

 private:
  static const uint32_t DISPLAY_WIDTH = 1440; //< Application window width in pixels.
  static const uint32_t DISPLAY_HEIGHT = 900; //< Application window height in pixels.
  static constexpr float FOV = 45.0f;         //< Camera's field of view.
  static constexpr float Z_NEAR = 0.1f;       //< TODO
  static constexpr float Z_FAR = 400.0f;      //< TODO

  /**
   * Updates camera position and rotation.
   */
  void updateCamera();

  /**
   * TODO: Remove this.
   */
  void createScene() {
    auto& rg = utils::RandomNumberGenerator::getInstance();
    // moveable point light
    {
      MeshPtr mesh = std::make_unique<Mesh>(primitive_mesh::sphere(1.0f, 25));
      Transform t;
      t.position.y = 4.0f;
      /*
      point_light = std::make_unique<PointLight>(
          std::move(mesh), t,
          PhongLight{
              {0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}},
          PointLight::Attenuation{1.0f, 0.09f, 0.032f});
          */

      point_light = std::make_unique<PointLight>(
          std::move(mesh), t,
          PhongLight{
              {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
          PointLight::Attenuation{1.0f, 0.09f, 0.032f});
      /*
              point_light = std::make_unique<PointLight>(
                  std::move(mesh), t,
                  PhongLight{
                      {0.2f, 0.2f, 0.0f}, {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f,
         0.0f}}, PhysicalLight::Attenuation{1.0f, 0.09f, 0.032f});
                  */

      renderer.registerObject(*point_light);
    }

    // dir light
    {
      dir_light = std::make_unique<DirLight>(
          PhongLight{
              {0.1f, 0.1f, 0.1f}, {0.25f, 0.25f, 0.25f}, {0.5f, 0.5f, 0.5f}},
          glm::vec3{0, -1, 1});
      renderer.registerObject(*dir_light);
    }

    // spot lights
    {
      auto createSpotLight = [&](const Transform& t,
                                 const glm::vec3& direction) {
        MeshPtr model =
            std::make_unique<Mesh>(primitive_mesh::sphere(1.0f, 25));
        spot_lights.push_back(std::move(std::make_unique<SpotLight>(
            std::move(model), t,
            PhongLight{
                {0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}},
            direction, 12.5f, 30.0f,
            PhysicalLight::Attenuation{1.0f, 0.022f, 0.0019f})));
      };
      for (int i = 0; i < 3; ++i) {
        Transform t;
        const float pos_m = 15.0f;
        t.position =
            glm::vec3(rg.random<-1, 1>() * pos_m, rg.random_0_1() * pos_m,
                      rg.random<-1, 1>() * pos_m);
        auto direction = glm::vec3(rg.random<-1, 1>(), rg.random<-1, 1>(),
                                   rg.random<-1, 1>());
        createSpotLight(t, direction);
      }
    }

    // global light
    {
      global_light = std::make_unique<Light>(PhongLight{
          {0.1f, 0.1f, 0.1f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}});
      /*
  global_light = std::make_unique<Light>(PhongLight{
      {0.4f, 0.4f, 0.4f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}});
      */
      renderer.setGlobalLight(*global_light);
    }

    for (auto& e : entities) {
      renderer.registerObject(*e);
    }
    for (auto& point_light : point_lights) {
      renderer.registerObject(*point_light);
    }
    for (auto& s : spot_lights) {
      renderer.registerObject(*s);
    }
  };

  /**
   * TODO: Refactor this.
   */
  void moveLight() {
    if (display_manager_.isKeyPressed(GLFW_KEY_UP)) {
      point_light->move(glm::vec3(1, 0, 0));
    }
    if (display_manager_.isKeyPressed(GLFW_KEY_DOWN)) {
      point_light->move(glm::vec3(-1, 0, 0));
    }
    if (display_manager_.isKeyPressed(GLFW_KEY_RIGHT)) {
      point_light->move(glm::vec3(0, 0, 1));
    }
    if (display_manager_.isKeyPressed(GLFW_KEY_LEFT)) {
      point_light->move(glm::vec3(0, 0, -1));
    }
  }

  DisplayManager& display_manager_;
  TextureManager& texture_manager_;

  Camera camera_;
  MasterRenderer renderer;

  std::vector<EntityPtr> entities;
  PointLightPtr point_light;
  std::vector<PointLightPtr> point_lights;
  DirLightPtr dir_light;
  std::vector<SpotLightPtr> spot_lights;
  LightPtr global_light;
};

}  // namespace helios