#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "terrain.h"
#include "ant.h"
#include "food.h"
#include "heatmap.h"
#include <vector>

class GameEngine {
    public:
        explicit GameEngine(const QSize &terrainSize);

        void tick();
        void addFood(const Food &fd);
        void removeFood(int index);

        Terrain& terrain();
        std::vector<Ant>& ants();
        std::vector<Food>& food();
        Heatmap& foodHeatmap();

    private:
        std::vector<Ant> ants_;
        std::vector<Food> food_;
        Heatmap foodHeatmap_;
        Terrain terrain_;
};

#endif // GAMEENGINE_H
