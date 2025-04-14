#include "raylib.h"

const float SCREEN_WIDTH = 1920.f;
const float SCREEN_HEIGHT = 1080.f;
const float SWH = SCREEN_WIDTH / 2.f;
const float SHH = SCREEN_HEIGHT / 2.f;
const int FPS = 60;

const int FONT_SIZE = 50;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "01_window");

    SetTargetFPS(FPS);               
    while (!WindowShouldClose())  {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hello world from RAYLIB", SWH - 300, SHH, FONT_SIZE, RED);

        EndDrawing();
    }

    CloseWindow();
     
    return 0;
}
