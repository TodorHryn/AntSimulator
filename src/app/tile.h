#ifndef TILE_H
#define TILE_H

#include <QColor>

struct Tile {
    QColor color;
    bool isEmpty;
    bool moved = false;
    uint8_t fillLevel = UINT8_MAX;

    bool empty() {
        return isEmpty || (fillLevel == 0);
    }

    bool operator==(const Tile &tile) {
        return color == tile.color && isEmpty == tile.isEmpty;
    }

    bool operator!=(const Tile &tile) {
        return !(*this == tile);
    }
};

#endif // TILE_H
