#include <raylib.h>
#include "drawing.h"

static void DrawTileGrid(const TileGrid* tileGrid)
{
    for (int y = 0; y < tileGrid->rows; y++)
    {
        for (int x = 0; x < tileGrid->columns; x++)
        {
            if (tileGrid->tiles[x + tileGrid->columns * y] == 1)
            {
                DrawRectangle(
                    x * tileGrid->cellSize, 
                    y * tileGrid->cellSize, 
                    tileGrid->cellSize, 
                    tileGrid->cellSize, 
                    WHITE);
            }
        }
    }
}

void DrawWorld(const World* world)
{
    DrawTileGrid(&world->tileGrid);
}
