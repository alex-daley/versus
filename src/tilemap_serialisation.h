#pragma once
#include "tilemap.h"

Tilemap LoadTilemap(const char* fileName);
void UnloadTilemap(Tilemap map);
void WriteTilemap(Tilemap map, const char* fileName);
