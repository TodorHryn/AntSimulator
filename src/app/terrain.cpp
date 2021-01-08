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

        if (y < dirtLevel - 8)
            tiles_[wd][y] = Tiles::DIRT_STABLE;
    }
}

void Terrain::tick() {
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
                    tryMove(x, y, 1, 0);
                    tryMove(x, y, -1, 0);
                }
            }
        }
    }
}

bool Terrain::tryMove(int x, int y, int dx, int dy) {
    if (inBounds(x + dx, y + dy)) {
        if (tiles_[x][y] == Tiles::WATER)
            tryMoveLiquid(x, y, dx, dy);
        else if (tiles_[x][y] == Tiles::DIRT)
            tryMoveSolid(x, y, dx, dy);
    }

    return false;
}

bool Terrain::tryMoveLiquid(int x, int y, int dx, int dy) {
    if (tiles_[x][y] != Tiles::WATER)
        throw std::invalid_argument("tryMoveLiquid can only be called on liquids");

    if (tiles_[x + dx][y + dy] == Tiles::SKY) {
        tiles_[x + dx][y + dy] = Tiles::WATER;
        tiles_[x + dx][y + dy].fillLevel = 0;
    }

    if (tiles_[x + dx][y + dy] == Tiles::WATER) {
        uint8_t toTransfer = 0;

        if (dy == 0) {
            if (tiles_[x][y].fillLevel > tiles_[x + dx][y + dy].fillLevel)
                toTransfer = (tiles_[x][y].fillLevel - tiles_[x + dx][y + dy].fillLevel) / 2;
        }
        else
            toTransfer = std::min(static_cast<uint8_t>(UINT8_MAX - tiles_[x + dx][y + dy].fillLevel), tiles_[x][y].fillLevel);

        tiles_[x + dx][y + dy].fillLevel += toTransfer;
        tiles_[x][y].fillLevel -= toTransfer;

        return tiles_[x][y].fillLevel == 0;
    }

    return false;
}

bool Terrain::tryMoveSolid(int x, int y, int dx, int dy) {
    if (tiles_[x][y] != Tiles::DIRT)
        throw std::invalid_argument("tryMoveSolid can only be called on solid tiles");

    if (tiles_[x + dx][y + dy] == Tiles::SKY) {
        tiles_[x][y].moved = true;
        tiles_[x + dx][y + dy] = tiles_[x][y];
        tiles_[x][y] = Tiles::SKY;
        return true;
    }
    else if (tiles_[x + dx][y + dy] == Tiles::WATER) {
        Tile t = tiles_[x + dx][y + dy];

        tiles_[x][y].moved = true;
        tiles_[x + dx][y + dy] = tiles_[x][y];
        tiles_[x][y] = t;
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
