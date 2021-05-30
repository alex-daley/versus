#include "tilegrid_serialisation.h"
#include <stdlib.h>
#include <assert.h>

#define TILEGRID_COLUMNS 20
#define TILEGRID_ROWS 15
#define TILE_PIXEL_WIDTH 16
#define TILE_COUNT TILEGRID_COLUMNS * TILEGRID_ROWS

static TileGrid AllocateTileGrid()
{
    TileGrid tileGrid = { 0 };
    tileGrid.cellSize = TILE_PIXEL_WIDTH;
    tileGrid.columns = TILEGRID_COLUMNS;
    tileGrid.rows = TILEGRID_ROWS;
    tileGrid.tiles = calloc((size_t)TILE_COUNT, sizeof(int));
    tileGrid.fileName = 0;
    return tileGrid;
}

static bool IsTile(int id)
{
    return id == 0 || id == 1;
}

static int ToInt(char c)
{
    return (int)c - '0';
}

static char ToChar(int i)
{
    return (char)i + '0';
}

TileGrid LoadTileGrid(const char* fileName)
{
    TileGrid grid = AllocateTileGrid();
    grid.fileName = fileName;

    if (!FileExists(fileName))
    {
        TraceLog(LOG_WARNING, "%s not found", fileName);
        return grid;
    }

    char* text = LoadFileText(fileName);
    for (size_t i = 0; i < TILE_COUNT; ++i)
    {
        int tile = ToInt(text[i]);

        if (!IsTile(tile))
        {
            TraceLog(LOG_WARNING, "Unknown tile id: %c at position %i in file %s", text[i], i, fileName);

            UnloadTileGrid(&grid);
            UnloadFileText(text);

            return AllocateTileGrid();
        }

        grid.tiles[i] = tile;
    }

    UnloadFileText(text);

    return grid;
}

void UnloadTileGrid(TileGrid* tileGrid)
{
    free(tileGrid->tiles);
    tileGrid->columns = tileGrid->rows = tileGrid->cellSize = 0;
}

void WriteTileGrid(TileGrid* tileGrid)
{
    if (!tileGrid->fileName)
    {
        TraceLog(LOG_WARNING, "Not saving tile grid because fileName was null");
        return;
    }

    char* buffer = malloc((TILE_COUNT + 1) * sizeof(char));

    assert(buffer);

#pragma warning(push)
#pragma warning(disable : 6386)

    // DANGER ZONE
    for (size_t i = 0; i < TILE_COUNT; ++i)
    {
        buffer[i] = ToChar(tileGrid->tiles[i]);
    }

    buffer[TILE_COUNT] = '\0';

#pragma warning( pop )

    SaveFileText(tileGrid->fileName, buffer);
    free(buffer);
}
