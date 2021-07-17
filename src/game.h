#pragma once
#include "content.h"
#include "player.h"
#include "tilemap.h"

typedef struct GameInput {
    int horizontal;
} GameInput;

typedef struct GameTime {
    double dt;
} GameTime;

Player LoadPlayer(int minX, int minY);

// TODO: Tidy up.
void UpdatePlayer(Player* player, GameInput input, GameTime time, Tilemap map, Content* content);
