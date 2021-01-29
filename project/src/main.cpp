#include <iostream>

#include "game_engine.hpp"

using namespace game_engine;

int main() {
    if (!GameEngine::init())
        return 1;
    GameEngine engine;
    engine.run();
    return 0;
}