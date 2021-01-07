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
        const std::vector<std::vector<double>>& waterHeatmap() const;

    private:
        const int WATER_HEATMAP_RAD = 5;

        void updateWaterHeatmap();
        bool tryMove(int x, int y, int dx, int dy, uint8_t maxAmount = UINT8_MAX);

        QSize size_;
        std::vector<std::vector<Tile>> tiles_;
        std::vector<std::vector<double>> waterHeatmap_;
};

#endif // TERRAIN_H
