#include <math.h>
#include <raylib.h>

static const double targetFrameTime = 1.0 / 60.0;

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
    SetTargetFPS(60);
    InitWindow(1280, 720, "Versus");
    
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
            // TODO: Update game here

            accumulator -= targetFrameTime;
        }

        BeginDrawing();
        ClearBackground(BLUE);
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
