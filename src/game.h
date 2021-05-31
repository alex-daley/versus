#ifndef VERSUS_GAME_H
#define VERSUS_GAME_H
#include <raylib.h>
#include "content.h"
#include "player.h"

typedef struct Game {
    Content* content;
    Player player;
} Game;

Game InitGame(Content* content);
void UpdateGame(Game* game);
void DrawGame(const Game* game);

#endif
