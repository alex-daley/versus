#pragma once
#include <math.h>
#include <raylib.h>
#include "config.h"
#include "editor.h"
#include "game.h"
#include "drawing.h"

static const int defaultWidth = 1280;
static const int defaultHeight = 720;
static const unsigned int flags = FLAG_VSYNC_HINT;
static const char* title = "Versus";

static inline double Min(double a, double b) {
    return a < b ? a : b;
}

static double CalculateScreenScale(double width, double height) {
    double x = width  / (double)logicalWidth;
    double y = height / (double)logicalHeight;
    return Min(x, y);
}

static void DrawPixelPerfect(Texture2D renderTarget) {
    double cx = (double)GetScreenWidth();
    double cy = (double)GetScreenHeight();
    double scale = CalculateScreenScale(cx, cy);

    Rectangle src = { 0.0f,  0.0f, (float)logicalWidth, (float)-logicalHeight };
    Rectangle dst = {
        (float)round(((cx - ((double)logicalWidth * scale)) / 2.0)),
        (float)round(((cy - ((double)logicalHeight * scale)) / 2.0)),
        (float)round(((double)logicalWidth * scale)),
        (float)round(((double)logicalHeight * scale))
    };

    DrawTexturePro(renderTarget, src, dst,
        (Vector2) { 0.0f, 0.0f }, 0.0f, WHITE);
}

static double SnapFrameTime(double frameTime, double fps) {
    const double precision = 0.0002;
    return fabs(frameTime - (1.0 / fps)) < precision
        ? 1.0 / fps
        : frameTime;
}

static double GetSnappedFrameTime() {
    double frameTime = GetFrameTime();
    frameTime = SnapFrameTime(frameTime, 60.0);
    frameTime = SnapFrameTime(frameTime, 30.0);
    frameTime = SnapFrameTime(frameTime, 20.0);
    frameTime = SnapFrameTime(frameTime, 15.0);

    return frameTime;
}

static Vector2 GetVirtualMousePosition() {
    float cx = (float)GetScreenWidth();
    float cy = (float)GetScreenHeight();
    float scale = (float)CalculateScreenScale(cx, cy);

    Vector2 mouse = GetMousePosition();
    mouse.x = (mouse.x - (GetScreenWidth()  - (logicalWidth  * scale)) / 2.0f) / scale;
    mouse.y = (mouse.y - (GetScreenHeight() - (logicalHeight * scale)) / 2.0f) / scale;
    return mouse;
}

int main() {
    SetConfigFlags(flags);
    SetTargetFPS(60);
    InitWindow(defaultWidth, defaultHeight, title);

    RenderTexture rt = LoadRenderTexture(logicalWidth, logicalHeight);
    Game game = LoadGame();
    Editor editor = { 0 };

    double accum = 0.0;
    
    while (!WindowShouldClose()) {
        // https://medium.com/@tglaiel/how-to-make-your-game-run-at-60fps-24c61210fe75
        accum += GetSnappedFrameTime();
        while (accum >= fixedDeltaTime) {
            UpdateGame(&game);
            accum -= fixedDeltaTime;
        }

        UpdateEditor(&editor, GetVirtualMousePosition(), game.map, mapName);

        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawDebugText(game);
        BeginTextureMode(rt);
        ClearBackground(BLACK);
        
        DrawGame(game);
        DrawEditor(editor, game);

        EndTextureMode();
        DrawPixelPerfect(rt.texture);
        EndDrawing();
    }
    
    UnloadGame(game);
    UnloadRenderTexture(rt);
    CloseWindow();

    return 0;
}
