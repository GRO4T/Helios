#include "GameEngine.hpp"

using namespace helios;

int main() {
    if (!GameEngine::init()) return 1;
    GameEngine engine;
    Assimp::Importer importer;
    engine.run();
    return 0;
}
