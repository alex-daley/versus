#pragma once
#include <stdbool.h>
#include "tilemap.h"

typedef struct PhysicsObject {
    double moveRemainderX;
    double moveRemainderY;
    bool isGrounded;

    int minX;
    int minY;
    int maxX;
    int maxY;
} PhysicsObject;

PhysicsObject MoveX(PhysicsObject object, Tilemap map, double amount);
PhysicsObject MoveY(PhysicsObject object, Tilemap map, double amount);
