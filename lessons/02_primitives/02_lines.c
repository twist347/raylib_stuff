#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int SWH = SCREEN_WIDTH / 2;
const int SHH = SCREEN_HEIGHT / 2;

const int FPS = 60;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "01_lines");

    const Vector2 points[] = {
        {SWH, SHH},
        {SWH - 300, SHH},
        {SWH - 300, SHH + 300},
        {SWH, SHH + 300},
    };

    SetTargetFPS(FPS);               
    while (!WindowShouldClose())  {
        const Vector2 mouse_pos = GetMousePosition();
        BeginDrawing();

        ClearBackground(BLACK);

        DrawLine(SWH, SHH, SWH + 300, SHH + 300, GREEN);
        DrawLineV((Vector2){SWH, SHH}, (Vector2){SWH - 300, SHH - 300}, BLUE);
        DrawLineEx((Vector2){SWH, SHH}, (Vector2){SWH + 300, SHH - 300}, 30.0f, YELLOW);
        DrawLineStrip(points, sizeof(points) / sizeof(Vector2), RED);
        DrawLineBezier((Vector2){SWH, SHH}, mouse_pos, 30.f, PINK);
        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
