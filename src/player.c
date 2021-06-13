#include <math.h>
#include "player.h"
#include "physics.h"
#include "game_constants.h"

#define MAX_SPEED          (96.0f / powf(1.0f, 1.0f)) * TARGET_FRAMETIME
#define ACCELERATION       MAX_SPEED
#define AIR_MOVE_FACTOR    0.2f

#define JUMP_TILES         3.0f
#define JUMP_TIME          0.4f
#define JUMP_HEIGHT        ((JUMP_TILES * TILE_SIZE_IN_PIXELS) / TARGET_FRAMERATE.f)
#define GRAVITY            ((JUMP_HEIGHT * 2.0f) / (powf(JUMP_TIME, 2.0f)))
#define GRAVITY_STEP       (GRAVITY * TARGET_FRAMETIME)
#define TAKEOFF            (-(GRAVITY * JUMP_TIME))
#define TERMINAL_VELOCITY  (-1.0f * TAKEOFF)

// FIXME: What if we're running un-expected framerates?
#define LEEWAY_FRAMES      8

static inline int Sign(float v)
{
    return v < 0.0f ? -1 : 1;
}

static void Jump(Player* player, const TileGrid* tiles)
{
    player->velocity.y = TAKEOFF;
    player->actor = PhysicsMoveY(tiles, player->actor, player->velocity.y);
}

static void MoveX(Player* player, const TileGrid* tiles)
{
    int direction = 0;

    if (IsKeyDown(KEY_D))
    {
        direction += 1;
    }
    else if (IsKeyDown(KEY_A))
    {
        direction -= 1;
    }

    if (direction == 0)
    {
        player->velocity.x = 0.0f;
    }
    
    TraceLog(LOG_INFO, "%f", player->velocity.x);

    if (player->actor.contacts & CONTACT_BELOW)
    {
        player->velocity.x += ACCELERATION * direction;
    }
    else
    {
        player->velocity.x += ACCELERATION * AIR_MOVE_FACTOR * direction;
    }

    if (fabs(player->velocity.x) >= MAX_SPEED)
    {
        player->velocity.x = MAX_SPEED * direction;
    }

    player->actor = PhysicsMoveX(tiles, player->actor, player->velocity.x);

    if ((player->actor.contacts & (CONTACT_LEFT | CONTACT_RIGHT)))
    {
        player->velocity.x = 0.0f;
    }
}

static void MoveY(Player* player, const TileGrid* tiles)
{
    player->velocity.y += (float)GRAVITY_STEP;

    if (player->velocity.y > TERMINAL_VELOCITY)
    {
        player->velocity.y = TERMINAL_VELOCITY;
    }

    player->actor.contacts &= ~CONTACT_BELOW;
    player->actor = PhysicsMoveY(tiles, player->actor, player->velocity.y);

    if (player->actor.contacts & CONTACT_ABOVE)
    {
        player->velocity.y = 0.0f;
    }

    if (player->actor.contacts & CONTACT_BELOW)
    {
        if (IsKeyPressed(KEY_SPACE) ||
            IsKeyDown(KEY_SPACE) &&
            player->jumpQueueFrames != 0 &&
            player->jumpQueueFrames <= LEEWAY_FRAMES)
        {
            Jump(player, tiles);
        }
        else
        {
            player->velocity.y = 0.0f;
        }

        player->jumpQueueFrames = 0;
        player->fallFrames = 0;
    }
    else
    {
        player->fallFrames++;

        player->jumpQueueFrames = IsKeyDown(KEY_SPACE)
            ? player->jumpQueueFrames + 1
            : 0;

        if (IsKeyPressed(KEY_SPACE) &&
            player->velocity.y >= 0.0f &&
            player->fallFrames <= LEEWAY_FRAMES)
        {
            Jump(player, tiles);
        }
        else if (IsKeyReleased(KEY_SPACE))
        {
            player->velocity.y *= 0.5f;
        }
    }
}

void UpdatePlayer(Player* player, const TileGrid* tiles)
{
    MoveX(player, tiles);
    MoveY(player, tiles);
}
