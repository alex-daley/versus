#include <stdlib.h>
#include "player.h"
#include "config.h"

static const float maxSpeed = 96.0f;

static void UpdatePlayerAnimator(Player* player, const Content* content) {

    switch (player->state) {
        case PLAYER_RUNNING:
            player->currentAnimation = &content->playerMoveAnimation;
            break;
        default:
            player->currentAnimation = &content->playerIdleAnimation;
            break;
    }

    UpdateAnimator(&player->animator, *player->currentAnimation);
}

Player LoadPlayer() {
    int x = logicalWidth / 2;
    int y = logicalHeight / 2;
    
    Player player = { 0 };

    player.physics.minX = x;
    player.physics.minY = y;
    player.physics.maxX = x + playerWidth;
    player.physics.maxY = y + playerHeight;

    return player;
}

void UpdatePlayer(Player* player, const Content* content, Tilemap map) {
    UpdatePlayerAnimator(player, content);

    int xInput = 0;
    if (IsKeyDown(KEY_D)) xInput += 1;
    if (IsKeyDown(KEY_A)) xInput -= 1;

    player->physics = MoveX(player->physics, map, xInput * maxSpeed * fixedDeltaTime);
    player->physics = MoveY(player->physics, map, 1);

    if (xInput != 0) {
        player->state = PLAYER_RUNNING;
        player->animator.flipX = xInput == -1;
    }
    else {
        player->state = PLAYER_IDLE;
    }
}
