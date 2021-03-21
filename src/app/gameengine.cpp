#include "gameengine.h"

GameEngine::GameEngine(const QSize &terrainSize) : terrain_(terrainSize) {

}

void GameEngine::tick() {
    terrain_.tick();
    terrain_.tick();

    for (Ant& ant : ants_)
        ant.tick();
}

Terrain &GameEngine::terrain() {
    return terrain_;
}

std::vector<Ant> &GameEngine::ants() {
    return ants_;
}
