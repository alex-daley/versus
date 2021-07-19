#pragma once
#include "tilemap.h"

typedef struct PhysicsObject {
    double velocityX;
    double velocityY;
    int minX;
    int minY;
    int maxX;
    int maxY;
} PhysicsObject;

PhysicsObject MoveX(PhysicsObject object, Tilemap map, double amount);
PhysicsObject MoveY(PhysicsObject object, Tilemap map, double amount);
