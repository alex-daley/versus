#ifndef VERSUS_TILEGRID_H
#define VERSUS_TILEGRID_H

typedef struct TileGrid
{
    int columns;
    int rows;
    int cellSize;
    int* tiles;
} TileGrid;

TileGrid LoadTileGrid(int columns, int rows, int cellSize);
void UnloadTileGrid(TileGrid* tileGrid);

#endif
