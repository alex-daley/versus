#include "editor.h"
#include <raylib.h>

typedef struct EditorState 
{
    bool drawGrid;
} EditorState;

static const Color gridColour    = { 80, 80, 80, 255 };
static const float gridThickness = 1.0f;
static const int gridColumns     = 20;
static const int gridRows        = 15;
static const int gridSpacing     = 16;

static EditorState editor   = { 0 };

static void DrawGrid(int columns, int rows, int spacing)
{
    const int width  = columns * spacing;
    const int height = rows    * spacing;
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

void UpdateEditor()
{
    if (IsKeyPressed(KEY_F3))
    {
        editor.drawGrid = !editor.drawGrid;
    }
}

void DrawEditor()
{
    if (editor.drawGrid)
    {
        DrawGrid(gridColumns, gridRows, gridSpacing);
    }
}
