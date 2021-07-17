#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <raylib.h>

#include "content.h"
#include "drawing.h"
#include "editor.h"
#include "game.h"
#include "player.h"
#include "tilemap.h"
#include "tilemap_serialisation.h"

static const int logicalWidth       = 320;
static const int logicalHeight      = 240;
static const int defaultWidth       = 1280;
static const int defaultHeight      = 720;
static const unsigned int flags     = FLAG_VSYNC_HINT;
static const int targetFPS          = 60;
static const double targetFrameTime = 1.0 / 60.0;
static const char* title            = "Versus";
static const char* tilemapFile      = "Versus.world";
static const char* playerAtlasFile  = "export/player.png";

typedef struct Resources {
    RenderTexture renderTarget;
    Tilemap map;
    Texture playerAtlas;
    Player player;
    Editor editor;
} Resources;

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
        (float)((cx - ((double)logicalWidth  * scale)) / 2.0),
        (float)((cy - ((double)logicalHeight * scale)) / 2.0),
        (float)((double)logicalWidth  * scale),
        (float)((double)logicalHeight * scale)
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

static GameInput GetInput() {
    GameInput input = { 0 };

    // TODO: Controller input.
    if (IsKeyDown(KEY_D)) input.horizontal += 1;
    if (IsKeyDown(KEY_A)) input.horizontal -= 1;

    return input;
}

static Resources* LoadResources() {
    Resources* resources = malloc(sizeof(Resources));
    assert(resources);

    resources->renderTarget = LoadRenderTexture(logicalWidth, logicalHeight);
    resources->playerAtlas = LoadTexture(playerAtlasFile);
    resources->player = LoadPlayer((logicalWidth / 2), (logicalHeight / 2));
    resources->map = LoadTilemap(tilemapFile);
    resources->editor = (Editor){ 0 };

    return resources;
}

static void UnloadResources(Resources* resources) {
    UnloadRenderTexture(resources->renderTarget);
    UnloadTilemap(resources->map);
    UnloadTexture(resources->playerAtlas);
    free(resources);
}

int main() {
    SetConfigFlags(flags);
    SetTargetFPS(targetFPS);
    InitWindow(defaultWidth, defaultHeight, title);

    Resources* resources = LoadResources();
    Content* content = LoadContent();
    GameInput input = GetInput();
    double frameAccumulator = 0.0;

    while (!WindowShouldClose()) {
        
        // https://medium.com/@tglaiel/how-to-make-your-game-run-at-60fps-24c61210fe75
        frameAccumulator += GetSnappedFrameTime();
        while (frameAccumulator >= targetFrameTime) {

            UpdatePlayer(&resources->player, input, content);
            frameAccumulator -= targetFrameTime;
        }

        Vector2 cursor = GetVirtualMousePosition();
        input = GetInput();

        UpdateEditor(&resources->editor, cursor, resources->map, tilemapFile);

        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginTextureMode(resources->renderTarget);
        
        ClearBackground(BLACK);
        DrawTilemap(resources->map);
        DrawPlayer(resources->player, resources->playerAtlas, content);
        DrawEditor(resources->editor, resources->map);

        EndTextureMode();
        DrawPixelPerfect(resources->renderTarget.texture);
        EndDrawing();
    }

    UnloadResources(resources);
    UnloadContent(content);
    CloseWindow();

    return 0;
}
