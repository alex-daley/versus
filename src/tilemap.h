#pragma once

typedef int Tile;

typedef struct Tilemap {
    int columns;
    int rows;
    int tileSize;
    Tile* tiles;
} Tilemap;

void WorldToTilePoint(Tilemap map, float x, float y, int* outX, int* outY);
void TileToWorldPoint(Tilemap tile, int x, int y, float* outX, float* outY);
Tile TileAt(Tilemap map, int x, int y);
