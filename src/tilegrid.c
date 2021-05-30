#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <raylib.h>
#include "tilegrid.h"

#define COLS 20
#define ROWS 15
#define TILE_PIXEL_WIDTH 16
#define TILE_COUNT COLS * ROWS

static TileGrid AllocateTileGrid()
{
    TileGrid tileGrid = { 0 };
    tileGrid.cellSize = TILE_PIXEL_WIDTH;
    tileGrid.columns = COLS;
    tileGrid.rows = ROWS;
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
    return c - '0';
}

static int RoundTo(int value, int multiple)
{
    return value - value % multiple;
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
        buffer[i] = (char)tileGrid->tiles[i] + '0';
    }

    buffer[TILE_COUNT] = '\0';
    
    #pragma warning( pop )

    SaveFileText(tileGrid->fileName, buffer);
    free(buffer);
}

Vector2 TileToWorldPoint(const TileGrid* tileGrid, int x, int y)
{
    if (x > tileGrid->columns || x < 0)
    {
        TraceLog(LOG_WARNING, "Coordinate x: %s outside tile grid bounds", x);
        return (Vector2) { 0 };
    }

    if (y > tileGrid->rows || y < 0)
    {
        TraceLog(LOG_WARNING, "Coordinate y: %s outside tile grid bounds", y);
        return (Vector2) { 0 };
    }

    return (Vector2)
    {
        x * tileGrid->cellSize,
        y * tileGrid->cellSize
    };
}

TilePosition WorldToTilePoint(const TileGrid* tileGrid, Vector2 position)
{
    int cellSize = tileGrid->cellSize;
    int x = RoundTo((int)position.x, cellSize) / cellSize;
    int y = RoundTo((int)position.y, cellSize) / cellSize;
    
    return (TilePosition) {
        .x = x,
        .y = y
    };
}

int GetTileAt(const TileGrid* tileGrid, TilePosition position)
{
    int x = position.x;
    int y = position.y;

    if (x > tileGrid->columns || x < 0 || y > tileGrid->rows || y < 0)
    {
        return 0;
    }

    return tileGrid->tiles[x + tileGrid->columns * y];
}
