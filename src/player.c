#include "player.h"
#include <math.h>

#define SPEED 2 

static inline int Sign(float v)
{
    return v < 0.0f ? -1 : 1;
}

static void MoveX(Player* player, const TileGrid* tiles)
{
    
    float velocity = 0.0f;
    if (IsKeyDown(KEY_D)) velocity += SPEED;
    else if (IsKeyDown(KEY_A)) velocity -= SPEED;
    else velocity = 0.0f;
    

    Vector2 desired =
    {
        player->rect.x + velocity + (Sign(velocity) == 1 ? player->rect.width : 0.0f),
        player->rect.y + player->rect.height - 0.1f
    };

    TilePosition tilePos = WorldToTilePoint(tiles, desired);
    if (GetTileAt(tiles, tilePos) == 1)
    {
        player->velocity.x = 0.0f;
        Vector2 position = TileToWorldPoint(tiles, (tilePos.x - Sign(velocity)), tilePos.y);
        player->rect.x = position.x;
    }
    else
    {
        player->velocity.x = velocity;
        player->rect.x += player->velocity.x;
    }
}

static void MoveY(Player* player, const TileGrid* tiles)
{
    // TIDY UP THIS ABSOLUTE MESS !!!

    if (player->isGrounded)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            player->isGrounded = false;

            player->velocity.y = -4.0f;
        }

        Vector2 bottomLeft =
        {
            player->rect.x + 0.1f,
            player->rect.y + 0.1f + player->rect.height
        };

        Vector2 bottomRight =
        {
            player->rect.x + player->rect.width - 0.1f,
            player->rect.y + 0.1f + player->rect.height
        };

        TilePosition belowLeft  = WorldToTilePoint(tiles, bottomLeft);
        TilePosition belowRight = WorldToTilePoint(tiles, bottomRight);

        if (GetTileAt(tiles, belowLeft) == 0 && GetTileAt(tiles, belowRight) == 0)
        {
            player->isGrounded = false;
        }
    }
    else
    {
        Vector2 bottomLeft =
        {
            player->rect.x,
            player->rect.y + player->velocity.y + player->rect.height
        };

        Vector2 bottomRight =
        {
            player->rect.x + player->rect.width - 0.1f,
            player->rect.y + player->velocity.y + player->rect.height
        };

        TilePosition belowLeft  = WorldToTilePoint(tiles, bottomLeft);
        TilePosition belowRight = WorldToTilePoint(tiles, bottomRight);

        if ((GetTileAt(tiles, belowLeft) == 1) || (GetTileAt(tiles, belowRight) == 1))
        {
            player->velocity.y = 0.0f;
            Vector2 position = TileToWorldPoint(tiles, belowRight.x, belowRight.y - 1) ;
            player->rect.y = position.y;
            player->isGrounded = true;
        }
        else
        {
            player->rect.y += player->velocity.y;
            player->velocity.y += 0.25f;
        }

        if (player->velocity.y > 0.0f)
        {
            return;
        }

        Vector2 topLeft =
        {
            player->rect.x,
            player->rect.y + player->velocity.y
        };

        Vector2 topRight =
        {
            player->rect.x + player->rect.width - 0.1f,
            player->rect.y + player->velocity.y
        };

        TilePosition aboveLeft  = WorldToTilePoint(tiles, topLeft);
        TilePosition aboveRight = WorldToTilePoint(tiles, topRight);

        if ((GetTileAt(tiles, aboveLeft) == 1) || (GetTileAt(tiles, aboveRight) == 1))
        {
            player->velocity.y = 0.0f;
            Vector2 position = TileToWorldPoint(tiles, aboveLeft.x, aboveLeft.y + 1);
            player->rect.y = position.y;
        }
    }
}

void UpdatePlayer(Player* player, const TileGrid* tiles)
{
    MoveX(player, tiles);
    MoveY(player, tiles);
}
