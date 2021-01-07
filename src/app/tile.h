#ifndef TILE_H
#define TILE_H

#include <QColor>

struct Tile {
    QColor color;
    bool isEmpty;
    bool moved = false;

    bool operator==(const Tile &tile) {
        return color == tile.color && isEmpty == tile.isEmpty;
    }
};

#endif // TILE_H
