#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int SWH = SCREEN_WIDTH / 2;
const int SHH = SCREEN_HEIGHT / 2;

const int FPS = 60;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "01_pixels");

    SetTargetFPS(FPS);               
    while (!WindowShouldClose())  {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawFPS(10, 10);

        DrawPixel(SWH, SHH, RED);
        DrawPixelV((Vector2){SWH + 100, SHH + 100}, GREEN);

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
