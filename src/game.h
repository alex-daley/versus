#pragma once
#include "content.h"
#include "player.h"

Player LoadPlayer(int minX, int minY);
void UpdatePlayer(Player* player, Content* content);
