#ifndef VERSUS_EDITOR_H
#define VERSUS_EDITOR_H
#include "tilegrid.h"
#include "world.h"
#include <raylib.h>

void UpdateEditor(TileGrid* tileGrid, Vector2 mousePosition);
void DrawEditor(const World* tileGrid);

#endif
