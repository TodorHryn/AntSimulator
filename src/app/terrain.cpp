#include "terrain.h"
#include "rand.h"
#include <stdexcept>

Terrain::Terrain(const QSize &size) : size_(size) {
    const int dirtLevel = static_cast<double>(size_.height()) * 2 / 3;

    tiles_.resize(size_.width());

    for (int x = 0; x < size_.width(); ++x) {
        tiles_[x].resize(size_.height());

        for (int y = 0; y < size_.height(); ++y) {
            if (y < dirtLevel || x > size_.width() / 2)
                tiles_[x][y] = Tiles::SKY;
            else
                tiles_[x][y] = Tiles::DIRT;
        }
    }

    for (int y = dirtLevel; y > dirtLevel - size_.height() / 3; --y) {
        int wd = static_cast<double>(size_.width()) / 10;

        for (int x = 0; x < wd; ++x) {
            tiles_[x][y] = Tiles::WATER;
        }

        if (y < dirtLevel - 5)
            tiles_[wd][y] = Tiles::DIRT_STABLE;
    }

    waterHeatmap_.resize(size_.width());

    for (int x = 0; x < size_.width(); ++x)
        waterHeatmap_[x].resize(size_.height(), 0);
}

void Terrain::tick() {
    updateWaterHeatmap();

    for (int x = 0; x < size_.width(); ++x)
        for (int y = 0; y < size_.height(); ++y)
            tiles_[x][y].moved = false;

    for (int x = 0; x < size_.width(); ++x) {
        for (int y = size_.height() - 1; y >= 0; --y) {
            if (tiles_[x][y].moved)
                continue;

            if (tiles_[x][y] == Tiles::DIRT) {
                if (!tryMove(x, y, 0, 1))
                    tryMove(x, y, Rand::intInRange(-1, 1), 1);
            }
            else if (tiles_[x][y] == Tiles::WATER) {
                if (!tryMove(x, y, 0, 1)) {
                    int dx = Rand::intInRange(-1, 1);

                    if (!tryMove(x, y, dx, 1)) {
                        if (inBounds(x + 1, y) && inBounds(x - 1, y) && waterHeatmap_[x + 1][y] < waterHeatmap_[x - 1][y] && tiles_[x + 1][y] == Tiles::SKY)
                            tryMove(x, y, 1, 0);
                        else if (inBounds(x - 1, y) && inBounds(x + 1, y) && waterHeatmap_[x - 1][y] < waterHeatmap_[x + 1][y] && tiles_[x - 1][y] == Tiles::SKY)
                            tryMove(x, y, -1, 0);
                        else
                            tryMove(x, y, dx, 0);
                    }
                }
            }
        }
    }
}

bool Terrain::tryMove(int x, int y, int dx, int dy) {
    if (inBounds(x + dx, y + dy) && tiles_[x + dx][y + dy] == Tiles::SKY) {
        tiles_[x][y].moved = true;
        tiles_[x + dx][y + dy] = tiles_[x][y];
        tiles_[x][y] = Tiles::SKY;
        return true;
    }

    return false;
}


Tile& Terrain::tile(int x, int y) {
    if (!inBounds(x, y))
        throw std::out_of_range("Tile position out of bounds");

    return tiles_[x][y];
}

bool Terrain::inBounds(int x, int y) {
    return x >= 0  && y >= 0 && x < size_.width() && y < size_.height();
}

const QSize &Terrain::size() const {
    return size_;
}

const std::vector<std::vector<double> > &Terrain::waterHeatmap() const {
    return waterHeatmap_;
}

void Terrain::updateWaterHeatmap() {
    for (int x = 0; x < size_.width(); ++x) {
        for (int y = 0; y < size_.height(); ++y) {
            waterHeatmap_[x][y] = 0;
        }
    }

    for (int x = 0; x < size_.width(); ++x) {
        for (int y = 0; y < size_.height(); ++y) {
            if (tiles_[x][y] == Tiles::WATER) {
                for (int dx = -WATER_HEATMAP_RAD + 1; dx < WATER_HEATMAP_RAD; ++dx) {
                    for (int dy = -WATER_HEATMAP_RAD + 1; dy < WATER_HEATMAP_RAD; ++dy) {
                        double dist = sqrt(dx * dx + dy * dy);

                        if (dist <= WATER_HEATMAP_RAD && inBounds(x + dx, y + dy)) {
                            waterHeatmap_[x + dx][y + dy] += WATER_HEATMAP_RAD - dist;
                        }
                    }
                }
            }
        }
    }
}
