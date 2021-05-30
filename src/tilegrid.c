#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <raylib.h>
#include "tilegrid.h"

static int RoundTo(int value, int multiple)
{
    return value - value % multiple;
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
