#ifndef TERRAIN_H
#define TERRAIN_H

#include "tiles.h"
#include <QSize>
#include <vector>

class Terrain {
    public:
        explicit Terrain(const QSize &size);
        Terrain(const Terrain&) = delete;
        Terrain& operator= (const Terrain&) = delete;

        void tick();

        Tile& tile(int x, int y);
        bool inBounds(int x, int y);

        const QSize& size() const;

    private:
        bool tryMove(int x, int y, int dx, int dy);
        bool tryMoveLiquid(int x, int y, int dx, int dy);
        bool tryMoveSolid(int x, int y, int dx, int dy);

        QSize size_;
        std::vector<std::vector<Tile>> tiles_;
};

#endif // TERRAIN_H
