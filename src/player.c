#include <stdlib.h>
#include <math.h>
#include "player.h"
#include "config.h"
#include "game_input.h"

static const double moveSpeed = 0.2;
static const double maxMoveSpeed = 2;

static const double gravity = 0.25;
static const double halfGravityJumpVelocity = 0.2;
static const double terminalVelocity = 4;
static const double jumpSpeed = -5;
static const double jumpLeewayTime = 0.15;
static const double jumpBufferTime = 0.05;
static const double wallStickTime = 0.25;

static int Sign(double velocity) {
    return velocity < 0.0 ? -1 : 1;
}

static Animation* DeduceAnimation(const Player* player, Content* content) {
    switch (player->state) {
        case PLAYER_RUN : return &content->playerMoveAnimation;
        case PLAYER_JUMP: return &content->playerJumpAnimation;
        case PLAYER_FALL: return &content->playerFallAnimation;
        default:          return &content->playerIdleAnimation;
    }
}

static void UpdatePlayerAnimator(Player* player, Content* content) {
    player->currentAnimation = DeduceAnimation(player, content);
    UpdateAnimator(&player->animator, *player->currentAnimation);
}

static void SetState(Player* player, PlayerState nextState) {
    if (player->state != nextState) {
        player->state = nextState;
        player->animator.currentFrame = 0;
    }
}

static void ApplyGraivty(Player* player, InputState input) {
    // Apply half gravity if we're near the apex of a jump and still holding down the jump button :)
    if (input.jump == JUMP_BUTTON_DOWN && (fabs(player->velocityY) < halfGravityJumpVelocity)) {
        player->velocityY += gravity * 0.5;
    }
    else {
        player->velocityY += gravity;
    }

    if (player->velocityY > terminalVelocity) {
        player->velocityY = terminalVelocity;
    }
}

static bool HasFlag(const Player* player, Contact flag) {
    return ((player->physics.contacts & flag) != 0);
}

static bool IsGrounded(const Player* player) {
    return HasFlag(player, CONTACT_BELOW);
}

static bool IsTouchingCeiling(const Player* player) {
    return HasFlag(player, CONTACT_ABOVE);
}

static bool IsTouchingWall(const Player* player) {
    return HasFlag(player, CONTACT_LEFT) || HasFlag(player, CONTACT_RIGHT);
}

static void ZeroVelocityX(Player* player) {
    player->velocityX = 0.0;
    player->physics.moveRemainderX = 0.0;
}

static void ZeroVelocityY(Player* player) {
    player->velocityY = 0.0;
    player->physics.moveRemainderY = 0.0;
}

static bool HasJumpInput(InputState input, double time, double bufferCounter) {
    if (input.jump == JUMP_BUTTON_PRESSED) {
        return true;
    }
    
    bool withinBufferTime = (time - bufferCounter) < jumpBufferTime;
    return input.jump == JUMP_BUTTON_DOWN && withinBufferTime;
}

static void Jump(Player* player) {
    SetState(player, PLAYER_JUMP);
    ZeroVelocityY(player);
    player->jumpLeewayCounter = 0.0;
    player->jumpBufferCounter = 0.0;
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
    const InputState input = GetInput(player->index);
    const Contact prevContact = player->physics.contacts;
    const double time = GetTime();

    UpdatePlayerAnimator(player, content);

    ApplyGraivty(player, input);

    // TODO: Tidy up logic.
    if (input.x == 0 && player->state != PLAYER_JUMPWALL) {
        player->velocityX = 0.0;
        ZeroVelocityX(player);
    }
    else {
        player->animator.flipX = input.x == -1;

        if(player->state != PLAYER_JUMPWALL || player->velocityY > 0.0) {
            if (Sign(player->velocityX) != input.x && IsGrounded(player)) {
                ZeroVelocityX(player);
            }

            player->animator.flipX = input.x == -1;

            if (time - player->wallStickCounter > wallStickTime) {
                player->velocityX += moveSpeed * input.x;
            }
            else {
                TraceLog(LOG_INFO, "wall stick");
            }
            if (fabs(player->velocityX) > maxMoveSpeed) {
                player->velocityX = maxMoveSpeed * input.x;
            }
        }
    }

    player->physics = MoveX(player->physics, map, player->velocityX);
    player->physics = MoveY(player->physics, map, player->velocityY);

    if (IsGrounded(player)) {
        player->jumpLeewayCounter = time;
        player->velocityY = 0.0;

        if (input.x == 0) {
            SetState(player, PLAYER_IDLE);
        }
        else {
            SetState(player, PLAYER_RUN);
        }

        if (HasJumpInput(input, time, player->jumpBufferCounter)) {
            Jump(player);
        }
    }
    else { // !Grounded
        
        if (player->velocityY > 0.0) {
            SetState(player, PLAYER_FALL);
        }

        if (IsTouchingCeiling(player)) {
            player->velocityY = 0.0;
        }

        if (IsTouchingWall(player)) {

        }

        if (IsTouchingWall(player) && (prevContact & CONTACT_LEFT) == 0) {
            TraceLog(LOG_INFO, "Info");
            player->wallStickCounter = time;
        }

        if (IsTouchingWall(player) && HasJumpInput(input, time, player->jumpBufferCounter)) {
            Jump(player);
            SetState(player, PLAYER_JUMPWALL);
            int direction = HasFlag(player, CONTACT_LEFT) ? 1 : -1;
            player->velocityX = direction * maxMoveSpeed;
        }

        if (input.jump == JUMP_BUTTON_PRESSED) {
            player->jumpBufferCounter = time;
            if (time - player->jumpLeewayCounter < jumpLeewayTime) {
                Jump(player); // "Coyote Time"
            }
        }
        else if (input.jump == JUMP_BUTTON_RELEASED) {
            player->velocityY *= 0.5f;
        }
    }
}
