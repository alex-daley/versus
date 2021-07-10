#pragma once
#include "tilemap.h"

typedef struct Editor {
    bool showGrid;
} Editor;

void UpdateEditor(Editor* editor, Vector2 cursor, Tilemap map, const char* mapFileName);
