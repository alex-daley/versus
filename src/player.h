#pragma once

static const int playerWidth  = 16;
static const int playerHeight = 24;

typedef struct Player {
    int minX;
    int minY;
    int maxX;
    int maxY;
} Player;
