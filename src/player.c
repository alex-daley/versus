#include <stdlib.h>
#include <math.h>
#include "player.h"
#include "config.h"

static const float maxSpeed = 96.0f;
static const double timeToApex = 0.3;
static const double jumpLeewayTime = 0.2;
static const double jumpBufferTime = 0.1;


static double Gravity() {
    static const double tiles = 2;
    
    double height = tiles * (double)tileSize;
    double gravity = ((height * 2.0) / (pow(timeToApex, 2.0)));

    return gravity;
}

static double TakeoffVelocity() {
    return (-(Gravity() * timeToApex));
}

static void UpdatePlayerAnimator(Player* player, const Content* content) {

    switch (player->state) {
        case PLAYER_RUNNING:
            player->currentAnimation = &content->playerMoveAnimation;
            break;
        case PLAYER_JUMPING:
            player->currentAnimation = &content->playerJumpAnimation;
            break;
        default:
            player->currentAnimation = &content->playerIdleAnimation;
            break;
    }

    UpdateAnimator(&player->animator, *player->currentAnimation);
}

static void Jump(Player* player, Tilemap map) {
    player->physics.moveRemainderY = 0;
    player->velocityY = TakeoffVelocity();
    player->physics = MoveY(player->physics, map, player->velocityY * fixedDeltaTime);
    player->jumpLeewayCounter = 0;
}

Player LoadPlayer() {
    int x = logicalWidth / 2;
    int y = logicalHeight / 2;
    
    Player player = { 0 };

    player.physics.minX = x;
    player.physics.minY = y;
    player.physics.maxX = x + playerWidth;
    player.physics.maxY = y + playerHeight;

    return player;
}

void UpdatePlayer(Player* player, const Content* content, Tilemap map) {
    UpdatePlayerAnimator(player, content);

    int xInput = 0;
    if (IsKeyDown(KEY_D)) xInput += 1;
    if (IsKeyDown(KEY_A)) xInput -= 1;

    player->velocityY += Gravity() * fixedDeltaTime;
    player->physics = MoveX(player->physics, map, xInput * maxSpeed * fixedDeltaTime);
    player->physics = MoveY(player->physics, map, player->velocityY * fixedDeltaTime);
    
    if (xInput != 0) {
        player->animator.flipX = xInput == -1;
    }

    if (player->physics.isGrounded) {
        player->velocityY = 0.0;
        player->jumpLeewayCounter = GetTime();

        if (IsKeyPressed(KEY_SPACE) || (IsKeyDown(KEY_SPACE) && (GetTime() - player->jumpBufferCounter) < jumpBufferTime)) {
            player->state = PLAYER_JUMPING;
            Jump(player, map);
            player->jumpBufferCounter = 0;
        }
        else {
            if (xInput != 0) {
                player->state = PLAYER_RUNNING;
            }
            else {
                player->state = PLAYER_IDLE;
            }
        }
    }
    else if (IsKeyPressed(KEY_SPACE) && ((GetTime() - player->jumpLeewayCounter) < jumpLeewayTime)) {
        Jump(player, map);
    } 
    else if (IsKeyPressed(KEY_SPACE)) {
        player->jumpBufferCounter = GetTime();
    }
}
