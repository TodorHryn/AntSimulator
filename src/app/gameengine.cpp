#include "gameengine.h"

GameEngine::GameEngine(const QSize &terrainSize) : terrain_(terrainSize), foodHeatmap_(*this, terrainSize) {

}

void GameEngine::tick() {
    terrain_.tick();
    terrain_.tick();

    for (Ant& ant : ants_)
        ant.tick();
}

void GameEngine::addFood(const Food &fd) {
    food_.push_back(fd);
    foodHeatmap_.apply(fd.position().x(), fd.position().y(), 1024);
}

Terrain &GameEngine::terrain() {
    return terrain_;
}

std::vector<Ant> &GameEngine::ants() {
    return ants_;
}

std::vector<Food> &GameEngine::food() {
    return food_;
}

Heatmap &GameEngine::foodHeatmap() {
    return foodHeatmap_;
}
