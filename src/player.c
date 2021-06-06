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

static inline int Sign(float v)
{
    return v < 0.0f ? -1 : 1;
}

static void MoveX(Player* player, const TileGrid* tiles)
{
    float velocity = 0.0f;

    // TODO: Remove
    TraceLog(LOG_INFO, "Left %i Right %i above %i below %i", 
        (player->actor.contacts & CONTACT_LEFT ) != 0, 
        (player->actor.contacts & CONTACT_RIGHT) != 0,
        (player->actor.contacts & CONTACT_ABOVE) != 0,
        (player->actor.contacts & CONTACT_BELOW) != 0);

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
            player->velocity.y = TAKEOFF_VELOCITY;
            player->actor = PhysicsMoveY(*tiles, player->actor, player->velocity.y);
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
