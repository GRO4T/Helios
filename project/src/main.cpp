#include "game_engine.hpp"

using namespace game_engine;

int main() {
    if (!GameEngine::init()) return 1;
    GameEngine engine;
    Assimp::Importer importer;
    engine.run();
    return 0;
}
