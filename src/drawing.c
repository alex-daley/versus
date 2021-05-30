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

static void DrawPlayer(const Player* player)
{
    DrawRectangle((int)player->x, (int)player->y, player->width, player->height, RED);
}

void DrawWorld(const World* world)
{
    DrawTileGrid(&world->tileGrid);
    DrawPlayer(&world->player);
}
