#include <math.h>
#include <raylib.h>
#include "game.h"

static int Sign(float v)
{
    return v < 0.0f ? -1 : 1;
}

Game InitGame(TileGrid tileGrid)
{
    Game game = { 0 };
    game.world.tileGrid = tileGrid;
    
    Vector2 startingPosition = TileToWorldPoint(&tileGrid, tileGrid.columns / 2, tileGrid.rows / 2);

    game.world.player = (Player) {
        .x = startingPosition.x,
        .y = startingPosition.y,
        .width = 12,
        .height = 16
    };
    
    return game;
}

void UpdateGame(Game* game)
{
    float velocityX = 0;
    if (IsKeyDown(KEY_A)) velocityX -= 2.0f;
    if (IsKeyDown(KEY_D)) velocityX += 2.0f;

    Player* player = &game->world.player;

    Vector2 desired = { 
        player->x + velocityX, 
        player->y 
    };

    // Player's origin is the top left corner. 
    // If we are moving right, we need to start checking for collisions from the right.

    if (Sign(velocityX) == 1)
    {
        // HACK: Why do we need the -1?
       desired.x += player->width - 1;
    }

    TileGrid* grid = &game->world.tileGrid;
    TilePosition tilePosition = WorldToTilePoint(grid, desired);
    TraceLog(LOG_INFO, "%i %i", tilePosition.x, tilePosition.y);
    if (GetTileAt(grid, tilePosition) == 0)
    {
        player->x += velocityX;
    }
}
