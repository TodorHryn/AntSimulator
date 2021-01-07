#include "terrain.h"
#include <stdexcept>

Terrain::Terrain(const QSize &size) : size_(size) {
    const int dirtLevel = static_cast<double>(size_.height()) * 2 / 3;

    tiles_.resize(size_.width());

    for (int x = 0; x < size_.width(); ++x) {
        tiles_[x].resize(size_.height());

        for (int y = 0; y < size_.height(); ++y) {
            if (y < dirtLevel)
                tiles_[x][y] = Tiles::SKY;
            else
                tiles_[x][y] = Tiles::DIRT;
        }
    }

    for (int x = 0; x < static_cast<double>(size_.width()) / 10; ++x)
        tiles_[x][dirtLevel] = Tiles::WATER;
}

Tile& Terrain::tile(int x, int y) {
    if (x < 0 || y < 0 || x >= size_.width() || y >= size_.height())
        throw std::out_of_range("Tile position out of bounds");

    return tiles_[x][y];
}

const QSize &Terrain::size() const {
    return size_;
}
