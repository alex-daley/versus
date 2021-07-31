#pragma
#include "animator.h"
#include "content.h"
#include "physics.h"
#include "tilemap.h"

static const int playerWidth = 16;
static const int playerHeight = 24;

typedef enum PlayerState {
    PLAYER_IDLE,
    PLAYER_RUN,
    PLAYER_JUMP
} PlayerState;

typedef struct Player {
    Animator animator;
    Animation* currentAnimation;
    PhysicsObject physics;
    PlayerState state;

    double velocityY;
    double jumpLeewayCounter;
    double jumpBufferCounter;
} Player;

Player LoadPlayer();
void UpdatePlayer(Player* player, Content* content, Tilemap map);
