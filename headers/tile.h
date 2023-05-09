//a rendering tile that is used to allow multiple threads to split up work
#pragma once

struct Tile {
    int xLow, yLow, xHigh, yHigh;
};