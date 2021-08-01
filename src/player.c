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

void UpdatePlayer(Player* player, Content* content, Tilemap map) {
    UpdatePlayerAnimator(player, content);

    // TODO: REFACTOR!

    int xInput = 0;
    if (IsKeyDown(KEY_D)) xInput += 1;
    if (IsKeyDown(KEY_A)) xInput -= 1;


    if (player->state != PLAYER_JUMPWALL || player->velocityY > 0.0) {

        if (IsGrounded(player)) {
            player->velocityX += xInput * moveSpeed;
            if (xInput == 0) {
                player->velocityX = 0.0;
            }

        }
        else {
            player->velocityX += xInput * moveSpeed * 0.2;
        }

        if (abs(player->velocityX) >= moveSpeed) {
            if (xInput != 0) {
                player->velocityX = moveSpeed * xInput;
            }
        }
    }

    
    player->velocityY += gravity;
    player->physics = MoveX(player->physics, map, player->velocityX);
    player->physics = MoveY(player->physics, map, player->velocityY);

    if (IsTouchingCeiling(player)) {
        player->velocityY = 0.0;
    }

    if (player->velocityX != 0) {
        player->animator.flipX = player->velocityX < 0;
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
    else {
        if (IsKeyPressed(KEY_SPACE)) {
            if ((player->physics.contacts & (CONTACT_RIGHT))) {
                player->velocityX = -moveSpeed;
                Jump(player, map);
                player->state = PLAYER_JUMPWALL;
            }
            else if ((player->physics.contacts & (CONTACT_LEFT))) {
                player->velocityX = moveSpeed;
                Jump(player, map);
                player->state = PLAYER_JUMPWALL;
            }
            else if (((GetTime() - player->jumpLeewayCounter) < jumpLeewayTime)) {
                Jump(player, map);
            }
            else {
                player->jumpBufferCounter = GetTime();
            }
        }
        else if (IsKeyDown(KEY_SPACE) && (GetTime() - player->jumpBufferCounter) < jumpBufferTime) {
            if ((player->physics.contacts & (CONTACT_RIGHT))) {
                player->velocityX = -moveSpeed;
                Jump(player, map);
                player->state = PLAYER_JUMPWALL;
            }
            else if ((player->physics.contacts & (CONTACT_LEFT))) {
                player->velocityX = moveSpeed;
                Jump(player, map);
                player->state = PLAYER_JUMPWALL;
            }
        }
        
        if (IsKeyReleased(KEY_SPACE) && player->state == PLAYER_JUMP) {
            player->velocityY *= 0.5;
        }
    }
}
