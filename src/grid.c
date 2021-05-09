#include "grid.h"
#include "raylib.h"

static const Color gridColour = { 80, 80, 80, 255 };
static const float gridThickness = 1.0f;

void DrawGrid2D(int columns, int rows, int spacing)
{
    const int width = columns * spacing;
    const int height = rows * spacing;
    const float offset = gridThickness / 2.0f;

    // Border.
    DrawRectangleLinesEx((Rectangle) { 0, 0, width, height }, 1, gridColour);

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
