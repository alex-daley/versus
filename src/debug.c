#include "debug.h"
#include "raylib.h"

static const Color gridColour = { 80, 80, 80, 255 };
static const float gridThickness = 1.0f;

void DebugGrid(int columns, int rows, int spacing)
{
    const float width  = (float)columns * spacing;
    const float height = (float)rows * spacing;
    const float offset = gridThickness / 2.0f;

    // Border.
    DrawRectangleLinesEx((Rectangle) { 0.0f, 0.0f, width, height }, 1, gridColour);

    // Rows.
    for (int y = 0; y < rows; y++)
    {
        Vector2 p1 = { 0, (y * spacing) - offset };
        Vector2 p2 = { width, p1.y };
        DrawLineEx(p1, p2, gridThickness, gridColour);
    }

    // Columns.
    for (int x = 0; x < columns; x++)
    {
        Vector2 p1 = { (x * spacing) - offset, 0 };
        Vector2 p2 = { p1.x, height };
        DrawLineEx(p1, p2, gridThickness, gridColour);
    }
}
