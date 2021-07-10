#include <raylib.h>
#include "editor.h"
#include "tilemap_serialisation.h"

static int RoundTo(int value, int multiple) {
    return value - value % multiple;
}

static bool TileMouseOver(Tilemap map, Vector2 cursor, int* x, int* y) {
    if (cursor.x < 0 || cursor.y < 0)
        return false;

    int tileSize = map.tileSize;
    *x = RoundTo((int)cursor.x, tileSize) / tileSize;
    *y = RoundTo((int)cursor.y, tileSize) / tileSize;

    return *x < map.columns&&* y < map.rows;
}

void UpdateEditor(Editor* editor, Vector2 cursor, Tilemap map, const char* mapFileName) {
    if (IsKeyReleased(KEY_F3)) {
        editor->showGrid = !editor->showGrid;
    }

    if (IsKeyPressed(KEY_F5)) {
        WriteTilemap(map, mapFileName);
    }

    int x, y;
    if (TileMouseOver(map, cursor, &x, &y)) {
        Tile* tile = &map.tiles[x + map.columns * y];

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            *tile = 1;
        else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
            *tile = 0;
    }
}
