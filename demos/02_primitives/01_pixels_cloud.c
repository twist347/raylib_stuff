#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int FPS = 60;

const int PIXELS_COUNT = 100000;

void draw_rand_pixels(int count) {
    for (int i = 0; i < count; ++i) {
        const int x = GetRandomValue(0, SCREEN_WIDTH - 1);
        const int y = GetRandomValue(0, SCREEN_HEIGHT - 1);
        const Color color = {
            GetRandomValue(0, 255),
            GetRandomValue(0, 255),
            GetRandomValue(0, 255),
            255
        };
        DrawPixel(x, y, color);
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "01_pixels_cloud");

    SetTargetFPS(FPS);               
    while (!WindowShouldClose())  {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawFPS(10, 10);

        draw_rand_pixels(PIXELS_COUNT); // increase

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
