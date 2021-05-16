#include "editor.h"
#include "grid.h"
#include <math.h>
#include <raylib.h>

#define GRID_COLUMNS 20
#define GRID_ROWS    15
#define GRID_SPACING 16

typedef struct EditorState
{
    bool drawGrid;
    int cells[GRID_COLUMNS * GRID_ROWS];
} EditorState;

static EditorState editor = { 0 };

static int RoundTo(int value, int multiple)
{
    return value - value % multiple;
}

void UpdateEditor(Vector2 mousePosition)
{
    if (IsKeyPressed(KEY_F3))
    {
        editor.drawGrid = !editor.drawGrid;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mousePosition.x > 0 && mousePosition.y > 0)
    {
        int x = RoundTo((int)mousePosition.x, GRID_SPACING) / GRID_SPACING;
        int y = RoundTo((int)mousePosition.y, GRID_SPACING) / GRID_SPACING;

        if (x < GRID_COLUMNS && y < GRID_ROWS)
        {
            TraceLog(LOG_INFO, "Clicked cell: %i %i", x, y);
            editor.cells[x + GRID_COLUMNS * y] = 1;
        }
    }
}

void DrawEditor()
{
    if (editor.drawGrid)
    {
        DrawGrid2D(GRID_COLUMNS, GRID_ROWS, GRID_SPACING);
    }
}
