#pragma once
#include "tilemap.h"

typedef enum
{
    CONTACT_NONE = (1 << 0),
    CONTACT_ABOVE = (1 << 1),
    CONTACT_BELOW = (1 << 2),
    CONTACT_LEFT = (1 << 3),
    CONTACT_RIGHT = (1 << 4)
} Contact;

typedef struct PhysicsObject {
    double moveRemainderX;
    double moveRemainderY;
    Contact contacts;

    int minX;
    int minY;
    int maxX;
    int maxY;
} PhysicsObject;

PhysicsObject MoveX(PhysicsObject object, Tilemap map, double amount);
PhysicsObject MoveY(PhysicsObject object, Tilemap map, double amount);
