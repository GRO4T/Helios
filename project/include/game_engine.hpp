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
        std::srand(std::time(0));
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
        // cubes
        auto& rg = utils::RandomNumberGenerator::getInstance();
        for (int i = 0; i < 40; ++i) {
            ModelPtr model = std::make_unique<Model>();
            model->load(primitive::cube(1.0f));
            MaterialSPtr material = std::make_shared<material::Silver>();
            material
                ->setDiffuseMap(
                    &texture_manager.getTexture("res/wood_metal_container.jpg"))
                .setSpecularMap(&texture_manager.getTexture(
                    "res/wood_metal_container_specular.jpg"));
            MaterializedModelPtr materialized_model =
                std::make_unique<MaterializedModel>(std::move(model), material);
            Transform t;
            const float pos_m = 20.0f;
            t.position =
                glm::vec3(rg.random<-1, 1>() * pos_m, rg.random_0_1() * pos_m,
                          rg.random<-1, 1>() * pos_m);
            entities.push_back(std::move(
                std::make_unique<Entity>(std::move(materialized_model), t)));
        }
        for (auto& e : entities) {
            renderer.registerObject(e.get());
        }

        // plane
        ModelPtr model2 = std::make_unique<Model>();
        model2->load(primitive::plane(20, 20, 4, 4));
        /*
        MaterialSPtr material2 = std::make_shared<material::Silver>(
            &texture_manager.getTexture("res/metal.jpg"));
            */
        MaterialSPtr material2 = std::make_shared<material::Silver>();
        MaterializedModelPtr materialized_model2 =
            std::make_unique<MaterializedModel>(std::move(model2), material2);
        Transform t2;
        t2.rotation.x = -90.0f;
        plane = std::make_unique<Entity>(std::move(materialized_model2), t2);

        renderer.registerObject(plane.get());

        // point_lights
        ModelPtr model3 = std::make_unique<Model>();
        model3->load(primitive::sphere(1.0f, 25));
        Transform t3;
        t3.position.y = 4.0f;
        point_light = std::make_unique<PointLight>(
            std::move(model3), t3,
            PhongLight{
                {0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}},
            PointLight::Attenuation{1.0f, 0.09f, 0.032f});

        renderer.registerObject(point_light.get());

        // dir light
        dir_light = std::make_unique<DirLight>(
            PhongLight{
                {0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}},
            glm::vec3{0, -1, 1});
        renderer.registerObject(dir_light.get());
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
    EntityPtr plane;
    PointLightPtr point_light;
    DirLightPtr dir_light;
};

}  // namespace game_engine