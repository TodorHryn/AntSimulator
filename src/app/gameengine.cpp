#include "gameengine.h"

GameEngine::GameEngine(const QSize &terrainSize) :
    terrain_(terrainSize),
    foodHeatmap_(*this, terrainSize),
    lightHeatmap_(*this, terrainSize)
{

}

void GameEngine::tick() {
    terrain_.tick();
    terrain_.tick();

    for (Ant& ant : ants_)
        ant.tick();

    for (int i = food_.size() - 1; i >= 0; --i)
        if (food_[i].amount() == 0)
            removeFood(i);

    for (int x = 0; x < terrain_.size().width(); ++x) {
        bool visible = true;

        for (int y = 0; y < terrain_.size().height(); ++y) {
            if (!terrain_.tile(x, y).empty())
                visible = false;

            if (visible)
                lightHeatmap_.apply(x, y, 8);
            else
                lightHeatmap_.apply(x, y, 0);
        }
    }
}

void GameEngine::addFood(const Food &fd) {
    food_.push_back(fd);
    foodHeatmap_.apply(fd.position().x(), fd.position().y(), 10);
}

void GameEngine::removeFood(int index) {
    food_.erase(food_.begin() + index);

    foodHeatmap_.clear();

    for (Food &fd : food_)
        foodHeatmap_.apply(fd.position().x(), fd.position().y(), 10);
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

Heatmap &GameEngine::lightHeatmap() {
    return lightHeatmap_;
}
