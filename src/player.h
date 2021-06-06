#ifndef VERSUS_PLAYER_H
#define VERSUS_PLAYER_H
#include <raylib.h>
#include "tilegrid.h"
#include "physics.h"

typedef struct Player 
{
    Actor actor;
    Vector2 velocity;
} Player;

void UpdatePlayer(Player* player, const TileGrid* surroundings);

#endif
