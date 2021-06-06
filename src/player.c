#include <math.h>
#include "player.h"
#include "physics.h"
#include "game_constants.h"

#define SPEED 2

#define JUMP_HEIGHT (3 * TILE_SIZE_IN_PIXELS) / TARGET_FRAMERATE.0
#define JUMP_TIME_TO_APEX 0.4
#define GRAVITY ((JUMP_HEIGHT * 2.0) / (pow(JUMP_TIME_TO_APEX, 2)))
#define GRAVITY_PER_FRAME GRAVITY * TARGET_FRAMETIME
#define TAKEOFF_VELOCITY -(GRAVITY * JUMP_TIME_TO_APEX)

#define FALLING_BUT_ALLOW_JUMPING_FRAMES 10
#define FALLING_BUT_QUEUE_JUMP_FRAMES 10

static inline int Sign(float v)
{
    return v < 0.0f ? -1 : 1;
}

static void Jump(Player* player, const TileGrid* tiles)
{
    player->velocity.y = TAKEOFF_VELOCITY;
    player->actor = PhysicsMoveY(*tiles, player->actor, player->velocity.y);
}

static void MoveX(Player* player, const TileGrid* tiles)
{
    float velocity = 0.0f;

    // TODO: Pass in the input.
    if (IsKeyDown(KEY_D))
    {
        velocity += SPEED;
    }
    else if (IsKeyDown(KEY_A))
    {
        velocity -= SPEED;
    }
    else
    {
        velocity = 0.0f;
    }

    player->actor = PhysicsMoveX(*tiles, player->actor, velocity);
}

static void MoveY(Player* player, const TileGrid* tiles)
{
    player->velocity.y += GRAVITY_PER_FRAME;//* TARGET_FRAMETIME;
    player->actor.contacts &= ~CONTACT_BELOW;

    player->actor = PhysicsMoveY(*tiles, player->actor, player->velocity.y);
    
    if (player->actor.contacts & CONTACT_BELOW)
    {
        player->velocity.y = 0.0f;

        // TODO: Pass in input.
        if (IsKeyPressed(KEY_SPACE))
        {
            Jump(player, tiles);
        }
        // Jump Buffering.
        else if (
            IsKeyDown(KEY_SPACE) && 
            player->numFramesJumpHasBeenQueued != 0 &&
            player->numFramesJumpHasBeenQueued <= FALLING_BUT_QUEUE_JUMP_FRAMES)
        {
            Jump(player, tiles);
        }


        player->numFramesFalling = 0;
        player->numFramesJumpHasBeenQueued = 0;
    }
    else
    {
        player->numFramesFalling++;

        if (
            player->velocity.y >= 0.0f &&
            player->numFramesFalling <= FALLING_BUT_ALLOW_JUMPING_FRAMES &&
            IsKeyPressed(KEY_SPACE))
        {
            Jump(player, tiles);
        }

        if (IsKeyDown(KEY_SPACE))
        {
            player->numFramesJumpHasBeenQueued++;
        }
        else
        {
            player->numFramesJumpHasBeenQueued = 0;
        }

        if (IsKeyReleased(KEY_SPACE))
        {
            player->velocity.y *= 0.5f;
        }
    }

    if (player->actor.contacts & CONTACT_ABOVE)
    {
        player->velocity.y = 0.0f;
    }

    
}

void UpdatePlayer(Player* player, const TileGrid* tiles)
{
    MoveX(player, tiles);
    MoveY(player, tiles);
}
