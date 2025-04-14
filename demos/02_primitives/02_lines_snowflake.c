#include "raylib.h"

#include <math.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SWH = SCREEN_WIDTH / 2;
const int SHH = SCREEN_HEIGHT / 2;
const int FPS = 60;

const int BRANCH_COUNT = 5;
const float BRANCH_ANGLE = 2.0 * PI / BRANCH_COUNT;
const int BRANCH_LEN = 250;
const float BRANCH_THICK = 10.0;
const int LEVEL = 5;  

void draw_snowflake(Vector2 center, float len, float thick, int level) {
    if (level <= 0) {
        return;
    }

    for (int i = 0; i < BRANCH_COUNT; ++i) {
        const Vector2 branch = (Vector2){
            center.x + cos(BRANCH_ANGLE * i) * len,
            center.y + sin(BRANCH_ANGLE * i) * len
        };
        DrawLineEx(center, branch, thick, RED);
        draw_snowflake(branch, len * 0.5f, thick * 0.5f, level - 1);
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "01_lines_snowflakes");

    SetTargetFPS(FPS);               
    while (!WindowShouldClose())  {
        BeginDrawing();
        DrawFPS(10, 10);

        ClearBackground(BLACK);

        draw_snowflake((Vector2){SWH, SHH}, BRANCH_LEN, BRANCH_THICK, LEVEL);

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
