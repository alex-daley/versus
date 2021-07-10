#include <raylib.h>
#include "game.h"

Player LoadPlayer(int minX, int minY) {
    Player player = { 0 };
    player.minX = minX;
    player.minY = minY;
    player.maxX = minX + playerWidth;
    player.maxY = minY + playerHeight;

    return player;
}
