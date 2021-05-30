#include "editor.h"
#include "debug.h"
#include "drawing.h"
#include "tilegrid_serialisation.h"
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

    if (IsKeyPressed(KEY_F5))
    {
        WriteTileGrid(grid);
    }

    int x = 0;
    int y = 0;
    if (TileMouseOver(*grid, cursor, &x, &y))
    {
        int* tile = &grid->tiles[x + grid->columns * y];

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            *tile = 1;
        else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
            *tile = 0;
    }
}

void DrawEditor(const World* world)
{
    const TileGrid* tileGrid = &world->tileGrid;

    if (editor.drawGrid)
    {
        DebugGrid(tileGrid->columns, tileGrid->rows, tileGrid->cellSize);
    }
}
