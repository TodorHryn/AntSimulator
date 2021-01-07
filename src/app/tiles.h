#ifndef TILES_H
#define TILES_H

#include "tile.h"
#include <memory>

namespace Tiles {
    Tile SKY = {QColor::fromRgb(135, 206, 235), true};
    Tile DIRT = {QColor::fromRgb(155, 118, 82), false};
    Tile WATER = {QColor::fromRgb(42, 157, 244), false};
};

#endif // TILES_H
