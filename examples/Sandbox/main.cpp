#include "Helios/Core/GameEngine.hpp"
#include <vector>

using namespace helios;

void createEntities(GameEngine& engine);
void createPlane(GameEngine& engine, const Transform& transform);

int main() {
  if (!GameEngine::init()) return 1;
  GameEngine engine;

  createEntities(engine);

  engine.run();
  return 0;
}

void createEntities(GameEngine& engine) {
  auto& rg = utils::RandomNumberGenerator::getInstance();

  // Backpack model
  {
    Transform transform;
    transform.position.y = 5.0f;
    transform.position.z = 30.0f;
    engine.registerEntity(transform, "res/backpack/backpack.obj");
  }

  // Cubes
  {
    for (int i = 0; i < 40; ++i) {
      MeshPtr mesh = std::make_unique<Mesh>(primitive_mesh::cube(1.0f));
      Transform transform;
      const float pos_m = 20.0f;
      transform.position =
          glm::vec3(rg.random<-1, 1>() * pos_m, rg.random_0_1() * pos_m,
                    rg.random<-1, 1>() * pos_m);
      engine.registerEntity<material::Silver>(
          transform, std::move(mesh), "res/wood_metal_container.jpg",
          "res/wood_metal_container_specular.jpg");
    }
  }

  // Planes
  {
    Transform transform;
    transform.rotation.x = -90.0f;
    createPlane(engine, transform);
    transform.position.y = 20.0f;
    createPlane(engine, transform);
    transform.rotation.x = 0.0f;
    transform.position = glm::vec3(0, 10, -20);
    createPlane(engine, transform);
    transform.position.z = 20.0f;
    transform.rotation.y = 180.0f;
    createPlane(engine, transform);
    transform.rotation.y = 270.0f;
    transform.position = glm::vec3(20, 0, 0);
    createPlane(engine, transform);
    transform.position.x = -20;
    transform.rotation.y = 90.0f;
    createPlane(engine, transform);
  }

  // Point lights
  for (int i = 0; i < 3; ++i) {
    MeshPtr mesh = std::make_unique<Mesh>(primitive_mesh::sphere(1.0f, 25));
    Transform transform;
    const float pos_m = 20.0f;
    transform.position =
        glm::vec3(rg.random<-1, 1>() * pos_m, rg.random_0_1() * pos_m,
                  rg.random<-1, 1>() * pos_m);
    engine.registerPointLight(transform, std::move(mesh));
  }
}

void createPlane(GameEngine& engine, const Transform& transform) {
  MeshPtr mesh =
      std::make_unique<Mesh>(primitive_mesh::plane(20, 20, 4, 4));
  engine.registerEntity<material::Silver>(transform, std::move(mesh));
}
