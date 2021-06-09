#ifndef VERSUS_PHYSICS_H
#define VERSUS_PHYSICS_H
#include "tilegrid.h"

typedef enum
{
    CONTACT_NONE  = (1 << 0),
    CONTACT_ABOVE = (1 << 1),
    CONTACT_BELOW = (1 << 2),
    CONTACT_LEFT  = (1 << 3),
    CONTACT_RIGHT = (1 << 4)
} Contact;

typedef struct Actor 
{
    int minX;
    int minY;
    int maxX;
    int maxY;
    Contact contacts;
} Actor;

Actor PhysicsMoveX(const TileGrid* tiles, Actor actor, float amount);
Actor PhysicsMoveY(const TileGrid* tiles, Actor actor, float amount);

#endif
