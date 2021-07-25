#pragma
#include "animator.h"
#include "content.h"
#include "physics.h"
#include "tilemap.h"

static const int playerWidth = 16;
static const int playerHeight = 24;

typedef enum PlayerState {
    PLAYER_IDLE,
    PLAYER_RUNNING
} PlayerState;

typedef struct Player {
    Animator animator;
    Animation* currentAnimation;
    PhysicsObject physics;
    PlayerState state;

    float velocityY;
} Player;

Player LoadPlayer();
void UpdatePlayer(Player* player, const Content* content, Tilemap map);
