#pragma once
#include "player.h"
#include "tilemap.h"
#include "content.h"

typedef struct Game {
    Player player; 
    Tilemap map;
    Content* content;
} Game; 

Game LoadGame();
void UnloadGame(Game game);
void UpdateGame(Game* game);
