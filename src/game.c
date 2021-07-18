#include "game.h"
#include "config.h"
#include "tilemap_serialisation.h"

Game LoadGame() {
    Game game = { 0 };
    game.map = LoadTilemap(mapName);
    game.content = LoadContent();
    game.player = LoadPlayer();

    return game;
}

void UnloadGame(Game game) {
    UnloadTilemap(game.map);
    UnloadContent(game.content);
}

void UpdateGame(Game* game) {
    UpdatePlayer(&game->player, game->content, game->map);
}
