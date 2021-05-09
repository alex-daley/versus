#include "editor.h"
#include "grid.h"
#include <raylib.h>

typedef struct EditorState 
{
    bool drawGrid;
} EditorState;

static const int gridColumns = 20;
static const int gridRows    = 15;
static const int gridSpacing = 16;

static EditorState editor = { 0 };

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
        DrawGrid2D(gridColumns, gridRows, gridSpacing);
    }
}
