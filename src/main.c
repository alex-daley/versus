#include <math.h>
#include <raylib.h>

#include "drawing.h"
#include "editor.h"
#include "game.h"
#include "tilemap.h"
#include "tilemap_serialisation.h"

static const int logicalWidth       = 320;
static const int logicalheight      = 240;
static const int defaultWidth       = 1280;
static const int defaultHeight      = 720;
static const unsigned int flags     = FLAG_VSYNC_HINT;
static const int targetFPS          = 60;
static const double targetFrameTime = 1.0 / 60.0;
static const char* title            = "Versus";
static const char* tilemapFile      = "Versus.world";
static const char* playerAtlasFile  = "export/player.png";

static inline double Min(double a, double b) {
    return a < b ? a : b;
}

static double CalculateScreenScale(double width, double height) {
    double x = width  / (double)logicalWidth;
    double y = height / (double)logicalheight;
    return Min(x, y);
}

static void DrawPixelPerfect(Texture2D renderTarget) {
    double cx = (double)GetScreenWidth();
    double cy = (double)GetScreenHeight();
    double scale = CalculateScreenScale(cx, cy);

    Rectangle src = { 0.0f,  0.0f, (float)logicalWidth, (float)-logicalheight };
    Rectangle dst = {
        (float)((cx - ((double)logicalWidth  * scale)) / 2.0),
        (float)((cy - ((double)logicalheight * scale)) / 2.0),
        (float)logicalWidth  * scale,
        (float)logicalheight * scale
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
    mouse.y = (mouse.y - (GetScreenHeight() - (logicalheight * scale)) / 2.0f) / scale;
    return mouse;
}

int main() {
    SetConfigFlags(flags);
    SetTargetFPS(targetFPS);
    InitWindow(defaultWidth, defaultHeight, title);

    RenderTexture renderTarget = LoadRenderTexture(logicalWidth, logicalheight);
    Tilemap map = LoadTilemap(tilemapFile);
    Texture playerAtlas = LoadTexture(playerAtlasFile);
    Player player = LoadPlayer((logicalWidth / 2), (logicalheight / 2));
    Editor editor = { 0 };

    double frameAccumulator = 0.0;

    while (!WindowShouldClose()) {
        
        // https://medium.com/@tglaiel/how-to-make-your-game-run-at-60fps-24c61210fe75
        frameAccumulator += GetSnappedFrameTime();
        while (frameAccumulator >= targetFrameTime) {
            frameAccumulator -= targetFrameTime;
        }

        Vector2 cursor = GetVirtualMousePosition();
        UpdateEditor(&editor, cursor, map, tilemapFile);

        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginTextureMode(renderTarget);
        
        ClearBackground(BLACK);
        DrawTilemap(map);
        DrawPlayer(player, playerAtlas);
        DrawEditor(editor, map);

        EndTextureMode();
        DrawPixelPerfect(renderTarget.texture);
        EndDrawing();
    }

    UnloadRenderTexture(renderTarget);
    UnloadTilemap(map);
    UnloadTexture(playerAtlas);
    CloseWindow();

    return 0;
}
