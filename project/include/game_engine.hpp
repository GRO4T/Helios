#pragma once

#include <renderer/master_renderer.hpp>

#include "display_manager.hpp"
#include "utils.hpp"

namespace game_engine {

class GameEngine {
public:
    GameEngine()
        : display_manager(DisplayManager::getInstance()),
          texture_manager(TextureManager::getInstance()),
          renderer(),
          camera(glm::vec3(0, 4, -10), 20, 180) {}

    static bool init() {
        bool success = true;
        try {
            DisplayManager::init();
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
            success = false;
        }
        DisplayManager::getInstance().createDisplay(DISPLAY_WIDTH,
                                                    DISPLAY_HEIGHT);
        MasterRenderer::calculateProjectionMatrix(
            FOV, Z_NEAR, Z_FAR, DISPLAY_WIDTH, DISPLAY_HEIGHT);
        return success;
    }
    void run() {
        std::srand(uint32_t(std::time(0)));
        createScene();
        while (!display_manager.windowShouldClose()) {
            double delta_time = display_manager.getDeltaTime();
            display_manager.handleEvents();
            updateCamera();
            moveLight();
            renderer.render(camera, delta_time);
            display_manager.update();
        }
    }

private:
    static const uint32_t DISPLAY_WIDTH = 1440;
    static const uint32_t DISPLAY_HEIGHT = 900;
    static constexpr float FOV = 45.0f;
    static constexpr float Z_NEAR = 0.1f;
    static constexpr float Z_FAR = 400.0f;

    void updateCamera() {
        camera.move();
        camera.rotate();
    }

    void createScene() {
        // complex model
        {
            ModelPtr model = std::make_unique<Model>("res/backpack/backpack.obj");
            Transform t;
            t.position.y = 5.0f;
            t.position.z = 30.0f;
            entities.push_back(
                std::move(std::make_unique<Entity>(std::move(model), t)));
        }

        // cubes
        auto& rg = utils::RandomNumberGenerator::getInstance();
        for (int i = 0; i < 40; ++i) {
            MeshPtr mesh = std::make_unique<Mesh>(primitive_mesh::cube(1.0f));
            MaterialSPtr material = std::make_shared<material::Silver>();
            material->diffuse_maps = {
                texture_manager.getTexture("res/wood_metal_container.jpg")};
            material->specular_maps.push_back(texture_manager.getTexture(
                "res/wood_metal_container_specular.jpg"));
            std::vector<MaterializedMeshSPtr> meshes = {
                std::make_unique<MaterializedMesh>(std::move(mesh), material)};
            ModelPtr model = std::make_unique<Model>(meshes);
            Transform t;
            const float pos_m = 20.0f;
            t.position =
                glm::vec3(rg.random<-1, 1>() * pos_m, rg.random_0_1() * pos_m,
                          rg.random<-1, 1>() * pos_m);
            entities.push_back(std::move(
                std::make_unique<Entity>(std::move(model), t)));
        }
        // planes
        {
            auto create_plane = [&](const Transform& t) {
                MeshPtr mesh =
                    std::make_unique<Mesh>(primitive_mesh::plane(20, 20, 4, 4));
                MaterialSPtr material = std::make_shared<material::Silver>();
                std::vector<MaterializedMeshSPtr> meshes = {
                    std::make_unique<MaterializedMesh>(std::move(mesh),
                                                       material)};
                ModelPtr model = std::make_unique<Model>(meshes);
                entities.push_back(
                    std::move(std::make_unique<Entity>(std::move(model), t)));
            };
            Transform t;
            t.rotation.x = -90.0f;
            create_plane(t);
            t.position.y = 20.0f;
            create_plane(t);
            t.rotation.x = 0.0f;
            t.position = glm::vec3(0, 10, -20);
            create_plane(t);
            t.position.z = 20.0f;
            t.rotation.y = 180.0f;
            create_plane(t);
            t.rotation.y = 270.0f;
            t.position = glm::vec3(20, 0, 0);
            create_plane(t);
            t.position.x = -20;
            t.rotation.y = 90.0f;
            create_plane(t);
        }
        // point_lights
        for (int i = 0; i < 3; ++i) {
            MeshPtr mesh =
                std::make_unique<Mesh>(primitive_mesh::sphere(1.0f, 25));
            Transform t;
            const float pos_m = 20.0f;
            t.position =
                glm::vec3(rg.random<-1, 1>() * pos_m, rg.random_0_1() * pos_m,
                          rg.random<-1, 1>() * pos_m);
            point_lights.push_back(std::move(std::make_unique<PointLight>(
                std::move(mesh), t,
                PhongLight{
                    {0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}},
                PointLight::Attenuation{1.0f, 0.045f, 0.0075f})));
        }

        // moveable point light
        {
            MeshPtr mesh =
                std::make_unique<Mesh>(primitive_mesh::sphere(1.0f, 25));
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
                {0.2f, 0.2f, 0.0f}, {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}},
            PhysicalLight::Attenuation{1.0f, 0.09f, 0.032f});
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
                    PhongLight{{0.2f, 0.2f, 0.2f},
                               {0.5f, 0.5f, 0.5f},
                               {1.0f, 1.0f, 1.0f}},
                    direction, 12.5f, 30.0f,
                    PhysicalLight::Attenuation{1.0f, 0.022f, 0.0019f})));
            };
            for (int i = 0; i < 3; ++i) {
                Transform t;
                const float pos_m = 15.0f;
                t.position = glm::vec3(rg.random<-1, 1>() * pos_m,
                                       rg.random_0_1() * pos_m,
                                       rg.random<-1, 1>() * pos_m);
                auto direction = glm::vec3(
                    rg.random<-1, 1>(), rg.random<-1, 1>(), rg.random<-1, 1>());
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

    void moveLight() {
        if (display_manager.isKeyPressed(GLFW_KEY_UP)) {
            point_light->move(glm::vec3(1, 0, 0));
        }
        if (display_manager.isKeyPressed(GLFW_KEY_DOWN)) {
            point_light->move(glm::vec3(-1, 0, 0));
        }
        if (display_manager.isKeyPressed(GLFW_KEY_RIGHT)) {
            point_light->move(glm::vec3(0, 0, 1));
        }
        if (display_manager.isKeyPressed(GLFW_KEY_LEFT)) {
            point_light->move(glm::vec3(0, 0, -1));
        }
    }

    DisplayManager& display_manager;
    TextureManager& texture_manager;

    Camera camera;
    MasterRenderer renderer;

    std::vector<EntityPtr> entities;
    PointLightPtr point_light;
    std::vector<PointLightPtr> point_lights;
    DirLightPtr dir_light;
    std::vector<SpotLightPtr> spot_lights;
    LightPtr global_light;
};

}  // namespace game_engine