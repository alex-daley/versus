#pragma once

static const int playerWidth  = 24;
static const int playerHeight = 24;

typedef enum PlayerState {
    PLAYER_IDLE,
    PLAYER_RUNNING
} PlayerState;

typedef struct Player {
    int minX;
    int minY;
    int maxX;
    int maxY;

    PlayerState state;
    int currentFrame;
    int frameCounter;
} Player;
