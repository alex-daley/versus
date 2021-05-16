#include <stdlib.h>
#include "tilegrid.h"

TileGrid LoadTileGrid(int columns, int rows, int cellSize)
{
    TileGrid tileGrid = { 0 };
    tileGrid.cellSize = cellSize;
    tileGrid.columns = columns;
    tileGrid.rows = rows;
    tileGrid.tiles = calloc(columns * rows, sizeof(int));
    return tileGrid;
}

void UnloadTileGrid(TileGrid* tileGrid)
{
    free(tileGrid->tiles);
    tileGrid->columns = tileGrid->rows = tileGrid->cellSize = 0;
}
