#include "gameengine.h"

GameEngine::GameEngine(const QSize &terrainSize) : terrain_(terrainSize), foodHeatmap_(*this, terrainSize) {

}

void GameEngine::tick() {
    terrain_.tick();
    terrain_.tick();

    for (Ant& ant : ants_)
        ant.tick();

    for (int i = food_.size() - 1; i >= 0; --i)
        if (food_[i].amount() == 0)
            removeFood(i);
}

void GameEngine::addFood(const Food &fd) {
    food_.push_back(fd);
    foodHeatmap_.apply(fd.position().x(), fd.position().y(), 1024);
}

void GameEngine::removeFood(int index) {
    food_.erase(food_.begin() + index);

    foodHeatmap_.clear();

    for (Food &fd : food_)
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
