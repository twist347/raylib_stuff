#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int SWH = SCREEN_WIDTH / 2;
const int SHH = SCREEN_HEIGHT / 2;

const int FPS = 60;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "04_rects");

    const Rectangle rect = {100, 100, 200, 150};

    SetTargetFPS(FPS);               
    while (!WindowShouldClose())  {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangle(SWH, SHH, 200, 100, RED);
        DrawRectangleV((Vector2){SWH / 2., SHH / 2.}, (Vector2){100, 200}, GREEN);
        DrawRectangleRec(rect, YELLOW);
        DrawRectanglePro(rect, (Vector2){200, 150}, 90, PURPLE);
        DrawRectangleLines(300, 300, 120, 60, BLUE);
        DrawRectangleLinesEx((Rectangle){100, 300, 200, 100}, 20.0f, DARKBLUE);

        DrawRectangleRounded((Rectangle){700, 800, 200, 100}, .5f, 100, WHITE);
        DrawRectangleRoundedLines((Rectangle){700, 600, 200, 100}, .3f, 12, WHITE);
        DrawRectangleRoundedLinesEx((Rectangle){900, 500, 200, 100}, .5f, 10, 10.f, ORANGE);


        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
