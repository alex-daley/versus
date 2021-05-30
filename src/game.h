#ifndef VERSUS_GAME_H
#define VERSUS_GAME_H
#include "world.h"

typedef struct Game
{
    World world;
} Game;

Game InitGame(TileGrid tileGrid);
void UpdateGame(Game* game);

#endif
