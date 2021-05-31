#ifndef VERSUS_PLAYER_H
#define VERSUS_PLAYER_H
#include <raylib.h>
#include "tilegrid.h"

typedef struct Player 
{
    Rectangle rect;
    Vector2 velocity;
    bool isGrounded;
} Player;

void UpdatePlayer(Player* player, const TileGrid* surroundings);

#endif
