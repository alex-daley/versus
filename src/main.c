#include <math.h>
#include <raylib.h>
#include "content.h"
#include "game.h"
#include "game_constants.h"
#include "editor.h"
#include "tilegrid.h"

#define MIN(a, b) (a < b ? a : b)
#define LOGICAL_W 320
#define LOGICAL_H 240

static float GameToScreenScale()
{
    float cx = (float)GetScreenWidth();
    float cy = (float)GetScreenHeight();
    return MIN(cx / LOGICAL_W, cy / LOGICAL_H);
}

static Vector2 GetVirtualMousePosition()
{
    float scale = GameToScreenScale();
    Vector2 mouse = GetMousePosition();
    mouse.x = (mouse.x - (GetScreenWidth()  - (LOGICAL_W * scale)) * 0.5f) / scale;
    mouse.y = (mouse.y - (GetScreenHeight() - (LOGICAL_H * scale)) * 0.5f) / scale;
    return mouse;
}

static void Present(const RenderTexture* renderTarget)
{
    float cx = (float)GetScreenWidth();
    float cy = (float)GetScreenHeight();
    float scale = GameToScreenScale();

    Rectangle source = { 0.0f,  0.0f,  LOGICAL_W,  -LOGICAL_H };
    Rectangle destination = {
        (cx - ((float)LOGICAL_W * scale)) / 2.0f,
        (cy - ((float)LOGICAL_H * scale)) / 2.0f,
        LOGICAL_W* scale,
        LOGICAL_H* scale
    };

    DrawTexturePro(
        renderTarget->texture,
        source,
        destination,
        (Vector2) { 0.0f, 0.0f },
        0.0f,
        WHITE);
}

static double SnapFrameTime(double frameTime, double fps)
{
    const double precision = 0.0002;
    return fabs(frameTime - (1.0 / fps)) < precision
        ? 1.0 / fps
        : frameTime;
}

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(TARGET_FRAMERATE);
    InitWindow(1280, 720, "Versus");

    RenderTexture renderTarget = LoadRenderTexture(320, 240);
    Content* content = LoadContent();
    Game game = InitGame(content);

    double accumulator = 0.0;

    while (!WindowShouldClose())
    {
        // https://medium.com/@tglaiel/how-to-make-your-game-run-at-60fps-24c61210fe75
        double frameTime = GetFrameTime();
        frameTime = SnapFrameTime(frameTime, 60.0);
        frameTime = SnapFrameTime(frameTime, 30.0);
        frameTime = SnapFrameTime(frameTime, 20.0);
        frameTime = SnapFrameTime(frameTime, 15.0);
        accumulator += frameTime;

        Vector2 mouse = GetVirtualMousePosition();
        while (accumulator >= TARGET_FRAMETIME)
        {
            UpdateEditor(&content->tileGrid, mouse);
            UpdateGame(&game);
            accumulator -= TARGET_FRAMETIME;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginTextureMode(renderTarget);
        ClearBackground(BLACK);

        DrawGame(&game);
        DrawEditor(&game.content->tileGrid);

        EndTextureMode();
        
        Present(&renderTarget);
        EndDrawing();
    }

    UnloadContent(content);
    UnloadRenderTexture(renderTarget);
    CloseWindow();
    
    return 0;
}
