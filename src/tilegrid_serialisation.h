#ifndef VERSUS_TILEGRID_SERIALISATION_H
#define VERSUS_TILEGRID_SERIALISATION_H
#include "tilegrid.h"

TileGrid LoadTileGrid(const char* fileName);
void UnloadTileGrid(TileGrid* tileGrid);
void WriteTileGrid(TileGrid* tileGrid);

#endif
