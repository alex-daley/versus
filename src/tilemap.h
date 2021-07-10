#pragma once

typedef int Tile;

typedef struct Tilemap {
    int columns;
    int rows;
    int tileSize;
    Tile* tiles;
} Tilemap;
