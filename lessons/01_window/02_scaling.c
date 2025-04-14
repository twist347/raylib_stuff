#include <math.h>

#include "raylib.h"

const float ASPECT_RATIO_WIDTH = 16;
const float ASPECT_RATIO_HEIGHT = 9;
const float SCALE_FACTOR = 120;
const float BASE_SCREEN_WIDTH = ASPECT_RATIO_WIDTH * SCALE_FACTOR;
const float BASE_SCREEN_HEIGHT = ASPECT_RATIO_HEIGHT * SCALE_FACTOR;
const int FPS = 60;

const char *msg = "Hello world from RAYLIB";
const int BASE_FONT_SIZE = SCALE_FACTOR * 0.5f;

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "02_scaling");

    SetTargetFPS(FPS);
    while (!WindowShouldClose())  {
        const float CUR_SCREEN_WIDTH = GetScreenWidth();
        const float CUR_SCREEN_HEIGHT = GetScreenHeight();

        float scale_x = CUR_SCREEN_WIDTH / BASE_SCREEN_WIDTH;
        float scale_y = CUR_SCREEN_HEIGHT / BASE_SCREEN_HEIGHT;
        float scale = fminf(scale_x, scale_y);

        const float SWH = CUR_SCREEN_WIDTH / 2.f;
        const float SHH = CUR_SCREEN_HEIGHT / 2.f;
        const int CUR_FONT_SIZE = BASE_FONT_SIZE * scale;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        const int text_width = MeasureText(msg, CUR_FONT_SIZE);
        DrawText(msg, SWH - text_width / 2, SHH, CUR_FONT_SIZE, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
