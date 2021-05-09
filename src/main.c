#include <math.h>
#include <raylib.h>
#include "editor.h"

#define MIN(a, b) (a < b ? a : b)

static const char* title = "Versus";

static const double targetFrameTime = 1.0 / 60.0;
static const int targetFrameRate = 60;
static const int flags = FLAG_VSYNC_HINT;

static const int nativeWidth  = 320;
static const int nativeHeight = 240;
static const int screenWidth  = 1280;
static const int screenHeight = 720;

typedef struct Resources
{
    RenderTexture renderTarget;
} Resources;

static Resources Initialise()
{
    SetConfigFlags(flags);
    SetTargetFPS(targetFrameRate);
    InitWindow(screenWidth, screenHeight, title);

    Resources resources = { 0 };
    resources.renderTarget = LoadRenderTexture(nativeWidth, nativeHeight);

    return resources;
}

static void Shutdown(Resources* resources)
{
    UnloadRenderTexture(resources->renderTarget);
    CloseWindow();
}

static double SnapFrameTime(double frameTime, double fps)
{
    const double precision = 0.0002;
    return fabs(frameTime - (1.0 / fps)) < precision
        ? 1.0 / fps
        : frameTime;
}

static void DrawRenderTarget(const RenderTexture* target)
{
    // Scale native game resolution to window resolution.

    float cx = (float)GetScreenWidth();
    float cy = (float)GetScreenHeight();
    float scale = MIN(cx / nativeWidth, cy / nativeHeight);

    Rectangle source = { 0.0f,  0.0f,  nativeWidth,  -nativeHeight };
    Rectangle destination = {
        (cx - ((float)nativeWidth  * scale)) / 2.0f,
        (cy - ((float)nativeHeight * scale)) / 2.0f,
        nativeWidth * scale,
        nativeHeight * scale
    };

    // Draw

    DrawTexturePro(
        target->texture,
        source,
        destination,
        (Vector2) { 0.0f, 0.0f },
        0.0f,
        WHITE);
}

int main()
{
    Resources resources = Initialise();
    RenderTexture* renderTarget = &resources.renderTarget;

    double accumulator = 0.0;
    while (!WindowShouldClose())
    {
        double frameTime = GetFrameTime();
        frameTime = SnapFrameTime(frameTime, 60.0);
        frameTime = SnapFrameTime(frameTime, 30.0);
        frameTime = SnapFrameTime(frameTime, 20.0);
        frameTime = SnapFrameTime(frameTime, 15.0);
        accumulator += frameTime;

        // https://medium.com/@tglaiel/how-to-make-your-game-run-at-60fps-24c61210fe75
        while (accumulator >= targetFrameTime)
        {
            UpdateEditor();
            accumulator -= targetFrameTime;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginTextureMode(*renderTarget);
        ClearBackground(BLACK);
        DrawEditor();
        EndTextureMode();
        
        DrawRenderTarget(renderTarget);

        EndDrawing();
    }

    Shutdown(&resources);

    return 0;
}
