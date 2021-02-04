#pragma once

#include <renderer/master_renderer.hpp>

#include "display_manager.hpp"
namespace game_engine {

class GameEngine {
public:
    GameEngine()
        : display_manager(DisplayManager::getInstance()),
          texture_manager(TextureManager::getInstance()),
          renderer() {}

    static bool init() {
        bool success = true;
        try {
            DisplayManager::init();
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
            success = false;
        }
        DisplayManager::getInstance().createDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);
        MasterRenderer::calculateProjectionMatrix(FOV, Z_NEAR, Z_FAR, DISPLAY_WIDTH,
                                                  DISPLAY_HEIGHT);
        return success;
    }
    void run() {
        // cube
        ModelPtr model = std::make_unique<Model>();
        model->load(primitive::cube(1.0f));
        MaterialSPtr material = std::make_shared<Material>(
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f),
            32.0f, 1.0f, &texture_manager.getTexture("res/container.jpg"));
        MaterializedModelPtr materialized_model =
            std::make_unique<MaterializedModel>(std::move(model), material);
        Transform t;
        t.position.y = 0.5f;
        EntityPtr cube = std::make_unique<Entity>(std::move(materialized_model), t);

        // plane
        ModelPtr model2 = std::make_unique<Model>();
        model2->load(primitive::plane(20, 20, 4, 4));
        MaterialSPtr material2 = std::make_shared<Material>(
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f),
            32.0f, 1.0f, &texture_manager.getTexture("res/metal.jpg"));
        MaterializedModelPtr materialized_model2 =
            std::make_unique<MaterializedModel>(std::move(model2), material2);
        Transform t2;
        t2.rotation.x = 90.0f;
        EntityPtr plane = std::make_unique<Entity>(std::move(materialized_model2), t2);

        renderer.registerObject(plane.get());
        renderer.registerObject(cube.get());

        //lights
        ModelPtr model3 = std::make_unique<Model>();
        model3->load(primitive::cube(1.0f));
        Transform t3;
        t3.position.y = 0.5f;
        t3.position.z = 2.0f;
        LightPtr light = std::make_unique<Light>(std::move(model3), t3, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));

        renderer.registerObject(light.get());

        while (!display_manager.windowShouldClose()) {
            double delta_time = display_manager.getDeltaTime();
            display_manager.handleEvents();
            updateCamera();
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

    DisplayManager& display_manager;
    TextureManager& texture_manager;

    Camera camera;
    MasterRenderer renderer;
};

}  // namespace game_engine