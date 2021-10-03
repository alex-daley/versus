#pragma once
#include "animator.h"
#include "content.h"
#include "physics.h"
#include "tilemap.h"

static const int playerWidth = 16;
static const int playerHeight = 24;

typedef enum PlayerIndex {
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4
} PlayerIndex;

typedef enum PlayerState {
    PLAYER_IDLE,
    PLAYER_RUN,
    PLAYER_FALL,
    PLAYER_JUMP,
    PLAYER_JUMPWALL
} PlayerState;

typedef struct Bullet {
    PhysicsObject physics;
    Animator animator;
    double velocityX;
    double velocityY;
} Bullet;

typedef struct Player {
    PlayerIndex index;

    Animator animator;
    Animation* currentAnimation;
    PhysicsObject physics;
    PlayerState state;
    Bullet bullet;

    double velocityX;
    double velocityY;
    double jumpLeewayCounter;
    double jumpBufferCounter;
    double wallStickCounter;
    bool bulletFired;
} Player;

Player LoadPlayer();
void UpdatePlayer(Player* player, Content* content, Tilemap map);
