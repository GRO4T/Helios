#pragma once

#include <renderer/master_renderer.hpp>

#include "display_manager.hpp"
namespace game_engine {

class GameEngine {
public:
    GameEngine(): display_manager(DisplayManager::getInstance()), renderer() {

    }

    static bool init() {
        bool success = true;
        try {
            DisplayManager::init();
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
            success = false;
        }
        DisplayManager::getInstance().createDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);
        MasterRenderer::calculateProjectionMatrix(FOV, Z_NEAR, Z_FAR, DISPLAY_WIDTH, DISPLAY_HEIGHT);
        return success;
    }
    void run() {
        /*
         * Needs refactoring
         */
        glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);


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

    Camera camera;
    MasterRenderer renderer;

    /*
     * Needs refactoring
     */
};

}