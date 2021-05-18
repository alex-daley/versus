#include "editor.h"
#include "debug.h"
#include <math.h>
#include <raylib.h>

typedef struct EditorState
{
    bool drawGrid;
} EditorState;

static EditorState editor = { 0 };

static int RoundTo(int value, int multiple)
{
    return value - value % multiple;
}

static bool TileMouseOver(TileGrid grid, Vector2 cursor, int* x, int* y)
{
    if (cursor.x < 0 || cursor.y < 0) 
        return false;

    int cellSize = grid.cellSize;
    *x = RoundTo((int)cursor.x, cellSize) / cellSize;
    *y = RoundTo((int)cursor.y, cellSize) / cellSize; 

    return *x < grid.columns && *y < grid.rows;
}

void UpdateEditor(TileGrid* grid, Vector2 cursor)
{
    if (IsKeyPressed(KEY_F3))
    {
        editor.drawGrid = !editor.drawGrid;
    }

    int x = 0;
    int y = 0;
    if (TileMouseOver(*grid, cursor, &x, &y))
    {
        int* tile = grid->tiles[x + grid->columns * y];

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            *tile = 1;
        else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
            *tile = 0;
    }
}

void DrawEditor(TileGrid tileGrid)
{
    for (int y = 0; y < tileGrid.rows; y++)
    {
        for (int x = 0; x < tileGrid.columns; x++)
        {
            if (tileGrid.tiles[x + tileGrid.columns * y] == 1)
            {
                DrawRectangle(x * tileGrid.cellSize, y * tileGrid.cellSize, tileGrid.cellSize, tileGrid.cellSize, WHITE);
            }
        }
    }

    if (editor.drawGrid)
    {
        DebugGrid(tileGrid.columns, tileGrid.rows, tileGrid.cellSize);
    }
}
