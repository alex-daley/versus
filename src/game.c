#include <math.h>
#include <raylib.h>
#include "game.h"
#include "player.h"

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
    Actor actor = player->actor;

    Rectangle rect =
    {
        actor.minX,
        actor.minY,
        actor.maxX - actor.minX,
        actor.maxY - actor.minY
    };

    DrawRectangleRec(rect, RED);
}

Game InitGame(Content* content)
{
    Game game = { 0 };
    game.content = content;

    TileGrid grid = content->tileGrid;
    Vector2 centre = TileToWorldPoint(&grid, grid.columns / 2, grid.rows / 2);
    game.player = (Player)
    {
        .actor.minX = centre.x,
        .actor.minY = centre.y,
        .actor.maxX = centre.x + 16,
        .actor.maxY = centre.y + 16,
        .actor.contacts = 0,
        .velocity = (Vector2) { 0 },
    };

    return game;
}

void UpdateGame(Game* game)
{
    Player* player = &game->player;
    TileGrid* grid = &game->content->tileGrid;
    UpdatePlayer(player, grid);
}

void DrawGame(const Game* game) 
{
    DrawTileGrid(&game->content->tileGrid);
    DrawPlayer(&game->player);
}
