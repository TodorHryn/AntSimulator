#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "terrain.h"
#include "ant.h"
#include <vector>

class GameEngine {
    public:
        explicit GameEngine(const QSize &terrainSize);

        void tick();

        Terrain& terrain();
        std::vector<Ant>& ants();

    private:
        std::vector<Ant> ants_;
        Terrain terrain_;
};

#endif // GAMEENGINE_H
