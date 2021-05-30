#ifndef VERSUS_WORLD_H
#define VERSUS_WORLD_H
#include "tilegrid.h"

typedef struct Player
{
    float x;
    float y;
    int width;
    int height;
} Player;

typedef struct World
{
    TileGrid tileGrid;
    Player player;
} World;

#endif
