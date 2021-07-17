#pragma once
#include "content.h"
#include "player.h"

typedef struct GameInput {
    int horizontal;
} GameInput;

Player LoadPlayer(int minX, int minY);
void UpdatePlayer(Player* player, GameInput input, Content* content);
