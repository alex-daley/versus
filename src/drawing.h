#pragma once
#include <raylib.h>
#include "tilemap.h"
#include "editor.h"
#include "player.h"

void DrawEditor(Editor editor, Tilemap map);
void DrawTilemap(Tilemap map);
void DrawPlayer(Player player, Texture atlas);
