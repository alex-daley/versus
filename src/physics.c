#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "physics.h"

static const int skin = 1;

static inline int Height(PhysicsObject object, int skin_) {
    return (object.maxY - object.minY) - (skin_ * 2);
}

static inline int Width(PhysicsObject object, int skin_) {
    return (object.maxX - object.minX) - (skin_ * 2);
}

static inline PhysicsObject Translate(PhysicsObject object, int x, int y) {
    object.minX += x;
    object.maxX += x;
    object.minY += y;
    object.maxY += y;
    return object;
}

static inline int Sign(int number) {
    return number < 0 ? -1 : 1;
}

PhysicsObject MoveX(PhysicsObject object, Tilemap map, double amount) {
    object.velocityX += amount;
    int move = (int)round(amount);
    if (move == 0) {
        return object;
    }
    
    object.velocityX -= (double)move;
    int sign = Sign(move);
    
    while (move != 0) {
        const int origin = sign == 1 ? object.maxX : object.minX;
        const int target = origin + sign;
        const int height = Height(object, skin);
        
        bool blocked = false;
        int tileX, tileY;
        for (int i = 0; i < height; i++) {
            WorldToTilePoint(map, target, object.minY + i, &tileX, &tileY);
            Tile tile = TileAt(map, tileX, tileY);
            if (!blocked) {
                blocked = tile != 0;
            }
        }

        if (!blocked) {
            object = Translate(object, sign, 0);
            move -= sign;
        }
        else {
            float x, y;
            TileToWorldPoint(map, tileX - sign, tileY, &x, &y);
            
            int width = Width(object, 0);
            object.minX = (int)roundf(x);
            object.maxX = object.minX + width;
            break;
        }
    }

    return object;
}

PhysicsObject MoveY(PhysicsObject object, Tilemap map, double amount) {
    object.velocityY += amount;
    int move = (int)round(amount);
    if (move == 0) {
        return object;
    }

    object.velocityY -= (double)move;
    int sign = Sign(move);

    while (move != 0) {
        const int origin = sign == 1 ? object.maxY : object.minY;
        const int target = origin + sign + 1;
        const int width = Width(object, skin);

        bool blocked = false;
        int tileX, tileY;
        for (int i = 0; i < width; i++) {
            WorldToTilePoint(map, object.minX + i, target, &tileX, &tileY);
            Tile tile = TileAt(map, tileX, tileY);
            if (!blocked) {
                blocked = tile != 0;
            }
        }

        if (!blocked) {
            object = Translate(object, 0, sign);
            move -= sign;
        }
        else {
            float x, y;
            TileToWorldPoint(map, tileX, tileY, &x, &y);

            int height = Height(object, 0);
            object.maxY = (int)roundf(y);
            object.minY = object.maxY - height;
            
            break;
        }
    }

    return object;
}
