#include <raylib.h>
#include "drawing.h"

static const Color gridColour = { 80, 80, 80, 255 };
static const float gridThickness = 1.0f;

static void DebugGrid(int columns, int rows, int spacing) {
    const float width = (float)columns * spacing;
    const float height = (float)rows * spacing;
    const float offset = gridThickness / 2.0f;

    // Border.
    DrawRectangleLinesEx((Rectangle) { 0.0f, 0.0f, width, height }, 1, gridColour);

    // Rows.
    for (int y = 0; y < rows; y++) {
        Vector2 p1 = { 0, (y * spacing) - offset };
        Vector2 p2 = { width, p1.y };
        DrawLineEx(p1, p2, gridThickness, gridColour);
    }

    // Columns.
    for (int x = 0; x < columns; x++) {
        Vector2 p1 = { (x * spacing) - offset, 0 };
        Vector2 p2 = { p1.x, height };
        DrawLineEx(p1, p2, gridThickness, gridColour);
    }
}

void DrawEditor(Editor editor, Tilemap map) {
    if (editor.showGrid) {
        DebugGrid(map.columns, map.rows, map.tileSize);
    }
}

void DrawTilemap(Tilemap map) {
    for (int y = 0; y < map.rows; y++) {
        for (int x = 0; x < map.columns; x++) {
            if (map.tiles[x + map.columns * y] == 1) {

                int size = map.tileSize;
                DrawRectangle(x * size, y * size, size, size, WHITE);
            }
        }
    }
}

void DrawPlayer(Player player, Texture atlas, const Content* content) {
    Animation currentAnimation = { 0 };
    
    switch (player.state) {
        case PLAYER_IDLE:
            currentAnimation = content->playerIdleAnimation;
            break;

        case PLAYER_RUNNING:
            currentAnimation = content->playerMoveAnimation;
            break;
    }

    Rectangle src = currentAnimation.rectangles[player.currentFrame];
    
    if (player.flipX) {
        src.width = -src.width;
    }

    Rectangle dst = {
        (float)player.minX,
        (float)player.minY,
        (float)player.maxX - player.minX,
        (float)player.maxY - player.minY
    };

    DrawRectangleLinesEx(dst, 1, RED);

    DrawTexturePro(atlas, src, dst, (Vector2) { 0.0f, 0.0f }, 0.0f, WHITE);
}
