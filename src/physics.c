#include "physics.h"
#include <raylib.h>
#include <math.h>

static inline int Sign(int v)
{
    return v < 0 ? -1 : 1;
}

Actor PhysicsMoveX(const TileGrid* tiles, Actor actor, float amount)
{
    int move = (int)roundf(amount);
    int sign = move == 0.0f ? 0 : Sign(move);

    Vector2 desired = 
    {
        .x = (float)((sign == 1 ? actor.maxX : actor.minX) + move),
        .y = (float)(actor.minY + 1)
    };

    // Get the tile(s) at our desired position.
    TilePosition minY = WorldToTilePoint(tiles, desired);
    desired.y = (float)(actor.maxY - 1);
    TilePosition maxY = WorldToTilePoint(tiles, desired);

    // Have we hit something?
    if (GetTileAt(tiles, minY) + GetTileAt(tiles, maxY) != 0)
    {   
        // Which tile have we hit?
        TilePosition tile = GetTileAt(tiles, minY) != 0 ? minY : maxY;

        // Snap to the tile adjacent to it.
        Vector2 snapPoint = TileToWorldPoint(tiles, (tile.x - sign), tile.y);

        int width = actor.maxX - actor.minX;
        actor.minX = (int)roundf(snapPoint.x);
        actor.maxX = actor.minX + width;

        // Update contact flags
        actor.contacts |= sign == 1 ? CONTACT_RIGHT : CONTACT_LEFT;

        return actor;
    }

    // Nothing here, we can move unconstrained.
    actor.minX += move;
    actor.maxX += move;

    // Zero horizontal contact flags
    actor.contacts &= ~(CONTACT_LEFT | CONTACT_RIGHT);

    return actor;
}

Actor PhysicsMoveY(const TileGrid* tiles, Actor actor, float amount)
{
    int sign = Sign((int)amount);

    Vector2 desired =
    {
        .x = (float)(actor.minX + 1),
        .y = (float)((sign == 1 ? actor.maxY : actor.minY) + amount)
    };

    // Get the tile(s) at our desired position.
    TilePosition minX = WorldToTilePoint(tiles, desired);
    desired.x = (float)(actor.maxX - 1);
    TilePosition maxX = WorldToTilePoint(tiles, desired);

    // Have we hit something?
    if (GetTileAt(tiles, minX) + GetTileAt(tiles, maxX) != 0)
    {
        // Which tile have we hit?
        TilePosition tile = GetTileAt(tiles, minX) != 0 ? minX : maxX;
        
        // Snap to the tile adjacent to it.
        Vector2 snapPoint = TileToWorldPoint(tiles, tile.x, (tile.y - sign));

        int height = actor.maxY - actor.minY;
        actor.minY = (int)roundf(snapPoint.y);
        actor.maxY = actor.minY + height;

        // Update contact flags
        actor.contacts |= sign == 1 ? CONTACT_BELOW : CONTACT_ABOVE;

        return actor;
    }

    // Nothing here, we can move unconstrained.
    int move = (int)roundf(amount);
    
    actor.minY += move;
    actor.maxY += move;

    // Zero vertical contact flags
    actor.contacts &= ~(CONTACT_ABOVE | CONTACT_BELOW);

    return actor;
}
