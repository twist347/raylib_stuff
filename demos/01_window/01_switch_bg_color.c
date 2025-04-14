#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SWH = SCREEN_WIDTH / 2;
const int SHH = SCREEN_HEIGHT / 2;
const int FPS = 60;

const int FONT_SIZE = 50;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "02_switch_bg_color");

    SetTargetFPS(FPS);

    Color bg_color = WHITE;

    while (!WindowShouldClose())  {
        if (IsKeyPressed(KEY_R)) {
            bg_color = RED;
        }
        if (IsKeyPressed(KEY_G)) {
            bg_color = GREEN;
        }
        if (IsKeyPressed(KEY_B)) {
            bg_color = BLUE;
        }

        BeginDrawing();

        ClearBackground(bg_color);

        DrawText("Hello world from RAYLIB", SWH - 300, SHH, FONT_SIZE, BLACK);

        EndDrawing();
    }

    CloseWindow();
     
    return 0;
}
