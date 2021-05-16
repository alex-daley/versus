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

void UpdateEditor(TileGrid* tileGrid, Vector2 mousePosition)
{
    if (IsKeyPressed(KEY_F3))
    {
        editor.drawGrid = !editor.drawGrid;
    }

    if (mousePosition.x > 0 && mousePosition.y > 0)
    {

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            int x = RoundTo((int)mousePosition.x, tileGrid->cellSize) / tileGrid->cellSize;
            int y = RoundTo((int)mousePosition.y, tileGrid->cellSize) / tileGrid->cellSize;

            if (x < tileGrid->columns && y < tileGrid->rows)
            {
                tileGrid->tiles[x + tileGrid->columns * y] = 1;
            }
        }
        else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            int x = RoundTo((int)mousePosition.x, tileGrid->cellSize) / tileGrid->cellSize;
            int y = RoundTo((int)mousePosition.y, tileGrid->cellSize) / tileGrid->cellSize;

            if (x < tileGrid->columns && y < tileGrid->rows)
            {
                tileGrid->tiles[x + tileGrid->columns * y] = 0;
            }
        }
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
