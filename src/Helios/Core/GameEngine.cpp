#include "Helios/Core/GameEngine.hpp"

namespace helios {

bool GameEngine::init() {
  try {
    DisplayManager::init();
  } catch (std::exception e) {
    std::cout << e.what() << std::endl;
    return false;
  }
  DisplayManager::getInstance().createDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  MasterRenderer::calculateProjectionMatrix(FOV, Z_NEAR, Z_FAR, DISPLAY_WIDTH,
                                            DISPLAY_HEIGHT);
  return true;
}

void GameEngine::run() {
  std::srand(uint32_t(std::time(0)));
  createScene();
  while (!display_manager_.windowShouldClose()) {
    double delta_time = display_manager_.getDeltaTime();
    display_manager_.handleEvents();
    updateCamera();
    moveLight();
    renderer.render(camera_, delta_time);
    display_manager_.update();
  }
}

void GameEngine::registerEntity(const Transform& transform,
                                const std::string& model_file_path) {
  ModelPtr model = std::make_unique<Model>(model_file_path);
  EntityPtr entity = std::make_unique<Entity>(std::move(model), transform);
  entities.push_back(std::move(entity));
}

void GameEngine::registerPointLight(const Transform& transform, MeshPtr mesh) {
  point_lights.push_back(std::move(std::make_unique<PointLight>(
      std::move(mesh), transform,
      PhongLight{{0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}},
      PointLight::Attenuation{1.0f, 0.045f, 0.0075f})));
}

void GameEngine::updateCamera() {
  camera_.move();
  camera_.rotate();
}

}  // namespace helios
