#include <assert.h>
#include <math.h>
#include <raylib.h>
#include "game.h"
#include "tilemap.h"

static const float maxSpeed = 96.0f;

typedef struct Point {
    int x; 
    int y;
} Point;

static int RoundTo(int value, int multiple) {
    return value - value % multiple;
}

static Point WorldToTilePoint(Tilemap map, Vector2 position) {
    int tileSize = map.tileSize;
    int x = RoundTo((int)position.x, tileSize) / tileSize;
    int y = RoundTo((int)position.y, tileSize) / tileSize;
    return (Point) { x, y };
}

Vector2 TileToWorldPoint(Tilemap map, Point point) {
    assert(point.x < map.columns);
    assert(point.x >= 0);
    assert(point.y < map.rows);
    assert(point.y >= 0);

    return (Vector2) {
        point.x * map.tileSize,
        point.y * map.tileSize
    };
}

static Tile GetTileAt(Tilemap map, int x, int y) {
    assert(x < map.columns);
    assert(x >= 0);
    assert(y < map.rows);
    assert(y >= 0);

    return map.tiles[x + map.columns * y];
}

static void UpdateAnimator(Player* player, Animation currentAnimation) {
    int* frameCounter = &player->frameCounter;
    int* currentFrame = &player->currentFrame;

    (*frameCounter)++;
    if (*frameCounter >= (60 / currentAnimation.frameSpeed)) {
        *frameCounter = 0;
        (*currentFrame)++;

        if (*currentFrame >= currentAnimation.frameCount) {
            (*currentFrame) = 0;
        }
    }
}

static void MoveX(Player* player, Tilemap map, float translationX) {
    player->velocity += translationX;
    int move = (int)roundf(translationX);

    if (move == 0) {
        return;
    }

    player->velocity -= (float)move;
    int sign = move < 0 ? -1 : 1;

    while (move != 0) {
        // TODO: Tidy up
        int origin = sign == 1 ? player->maxX : player->minX;
        int target = origin + (sign);
        Point point = WorldToTilePoint(map, (Vector2) { target, player->minY });
        Tile tile = GetTileAt(map, point.x, point.y);

        if (tile == 0) {
            player->minX += sign;
            player->maxX += sign;
            move -= sign;
        }
        else {
            /*
            // Snap to the tile adjacent to it.
            Vector2 snapPoint = TileToWorldPoint(map, (Point) { .x = point.x - sign, .y = point.y });
            int width = player->maxX - player->minX;
            player->minX = (int)roundf(snapPoint.x);
            player->maxX = player->minX + width;
            */
            break;
        }
    }
}

Player LoadPlayer(int minX, int minY) {
    Player player = { 0 };
    player.minX = minX;
    player.minY = minY;
    player.maxX = minX + playerWidth;
    player.maxY = minY + playerHeight;

    return player;
}

void UpdatePlayer(Player* player, GameInput input, GameTime time, Tilemap map, Content* content) {
    UpdateAnimator(player, content->playerMoveAnimation);

    MoveX(player, map, input.horizontal * maxSpeed * time.dt);

    if (input.horizontal != 0) {
        player->state = PLAYER_RUNNING;
        player->flipX = input.horizontal == -1;
    } 
    else {
        player->state = PLAYER_IDLE;
    }
}
