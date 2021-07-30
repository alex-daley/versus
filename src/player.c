#include <stdlib.h>
#include <math.h>
#include "player.h"
#include "config.h"

static const double moveSpeed = 2;
static const double gravity = 0.2;
static const double jumpSpeed = -4;
static const double jumpLeewayTime = 0.2;
static const double jumpBufferTime = 0.1;

static void UpdatePlayerAnimator(Player* player, Content* content) {

    switch (player->state) {
        case PLAYER_RUN:
            player->currentAnimation = &content->playerMoveAnimation;
            break;
        case PLAYER_JUMP:
            player->currentAnimation = &content->playerJumpAnimation;
            break;
        default:
            player->currentAnimation = &content->playerIdleAnimation;
            break;
    }

    UpdateAnimator(&player->animator, *player->currentAnimation);
}

static bool IsGrounded(const Player* player) {
    return ((player->physics.contacts & CONTACT_BELOW) != 0);
}

static bool IsTouchingCeiling(const Player* player) {
    return ((player->physics.contacts & CONTACT_ABOVE) != 0);
}

static void Jump(Player* player, Tilemap map) {
    player->physics.moveRemainderY = 0.0;
    player->jumpLeewayCounter = 0.0;
    player->jumpBufferCounter = 0.0;
    
    player->state = PLAYER_JUMP;
    player->velocityY = jumpSpeed;
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

    player->velocityY += gravity;
    player->physics = MoveX(player->physics, map, xInput * moveSpeed);    
    player->physics = MoveY(player->physics, map, player->velocityY);

    if (IsTouchingCeiling(player)) {
        player->velocityY = 0.0;
    }

    if (xInput != 0) {
        player->animator.flipX = xInput == -1;
    }

    if (IsGrounded(player)) {
        player->velocityY = 0.0;
        player->jumpLeewayCounter = GetTime();

        if (IsKeyPressed(KEY_SPACE) || (IsKeyDown(KEY_SPACE) && (GetTime() - player->jumpBufferCounter) < jumpBufferTime)) {
            Jump(player, map);
            player->jumpBufferCounter = 0;
        }
        else {
            if (xInput != 0) {
                player->state = PLAYER_RUN;
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
