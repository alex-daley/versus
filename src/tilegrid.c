#include <stdlib.h>
#include <assert.h>
#include <raylib.h>
#include "tilegrid.h"

#define COLUMNS 20
#define ROWS 15
#define TILE_COUNT COLUMNS * ROWS

TileGrid LoadTileGrid(int cellSize)
{
    TileGrid tileGrid = { 0 };
    tileGrid.cellSize = cellSize;
    tileGrid.columns = COLUMNS;
    tileGrid.rows = ROWS;
    tileGrid.tiles = calloc((size_t)TILE_COUNT, sizeof(int));
    return tileGrid;
}

TileGrid LoadTileGridFromFile(int cellSize, const char* filepath)
{
    TileGrid tileGrid = LoadTileGrid(cellSize);
    char* text = LoadFileText(filepath);

    if (!text)
    {
        TraceLog(LOG_ERROR, "Failed to load TileGrid, falling back to empty grid");
        return tileGrid;
    }

    for (size_t i = 0; i < TILE_COUNT; ++i)
    {
        tileGrid.tiles[i] = text[i] - '0';
    }

    UnloadFileText(text);

    return tileGrid;
}

void UnloadTileGrid(TileGrid* tileGrid)
{
    free(tileGrid->tiles);
    tileGrid->columns = tileGrid->rows = tileGrid->cellSize = 0;
}

void WriteTileGrid(TileGrid* tileGrid, const char* filepath)
{
    char* buffer = malloc((TILE_COUNT + 1) * sizeof(char));

    assert(buffer);
    
    #pragma warning(push)
    #pragma warning(disable : 6386)

    // DANGER ZONE
    for (size_t i = 0; i < TILE_COUNT; ++i)
    {
        buffer[i] = (char)tileGrid->tiles[i] + '0';
    }

    buffer[TILE_COUNT] = '\0';
    
    #pragma warning( pop )

    SaveFileText(filepath, buffer);
    free(buffer);
}
