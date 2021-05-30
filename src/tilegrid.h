#ifndef VERSUS_TILEGRID_H
#define VERSUS_TILEGRID_H
#include <raylib.h>

typedef struct TileGrid
{
    int columns;
    int rows;
    int cellSize;
    int* tiles;
    const char* fileName;
} TileGrid;

typedef struct TilePosition
{
    int x;
    int y;
} TilePosition;

TileGrid LoadTileGrid(const char* fileName);
void UnloadTileGrid(TileGrid* tileGrid);
void WriteTileGrid(TileGrid* tileGrid);

Vector2 TileToWorldPoint(const TileGrid* tileGrid, int x, int y);
TilePosition WorldToTilePoint(const TileGrid* tileGrid, Vector2 position);
int GetTileAt(const TileGrid* tileGrid, TilePosition position);

#endif
