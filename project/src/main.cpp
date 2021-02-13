#include <iostream>

#include "game_engine.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace game_engine;

int main() {
    if (!GameEngine::init()) return 1;
    GameEngine engine;
    Assimp::Importer importer;
    engine.run();
    return 0;
}