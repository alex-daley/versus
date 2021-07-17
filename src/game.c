#include <raylib.h>
#include "game.h"

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

Player LoadPlayer(int minX, int minY) {
    Player player = { 0 };
    player.minX = minX;
    player.minY = minY;
    player.maxX = minX + playerWidth;
    player.maxY = minY + playerHeight;

    return player;
}

void UpdatePlayer(Player* player, GameInput input, Content* content) {
    UpdateAnimator(player, content->playerMoveAnimation);

    player->velocity = input.horizontal;

    if (input.horizontal != 0) {
        player->state = PLAYER_RUNNING;
        player->flipX = input.horizontal == -1;
    } 
    else {
        player->state = PLAYER_IDLE;
    }
}
