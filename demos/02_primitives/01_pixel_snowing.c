#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int FPS = 60;

#define NUM_SNOW 10000

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "01_snowing");
    SetTargetFPS(FPS);

    Vector2 snoflakes[NUM_SNOW];
    for (int i = 0; i < NUM_SNOW; ++i) {
        snoflakes[i] = 
            (Vector2){GetRandomValue(0, SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT)};
    }

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        for (int i = 0; i < NUM_SNOW; ++i) {
            ++snoflakes[i].y;
            if (snoflakes[i].y > SCREEN_HEIGHT) {
                snoflakes[i].y = 0;    
            } 
            DrawPixel(snoflakes[i].x, snoflakes[i].y, WHITE);
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}