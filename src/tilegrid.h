#ifndef VERSUS_TILEGRID_H
#define VERSUS_TILEGRID_H

typedef struct TileGrid
{
    int columns;
    int rows;
    int cellSize;
    int* tiles;
    const char* fileName;
} TileGrid;

TileGrid LoadTileGrid(const char* fileName);
void UnloadTileGrid(TileGrid* tileGrid);
void WriteTileGrid(TileGrid* tileGrid);

#endif
