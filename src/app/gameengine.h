#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "terrain.h"
#include "ant.h"
#include "food.h"
#include <vector>

class GameEngine {
    public:
        explicit GameEngine(const QSize &terrainSize);

        void tick();

        Terrain& terrain();
        std::vector<Ant>& ants();
        std::vector<Food>& food();

    private:
        std::vector<Ant> ants_;
        std::vector<Food> food_;
        Terrain terrain_;
};

#endif // GAMEENGINE_H
