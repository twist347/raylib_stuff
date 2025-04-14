#include "raylib.h"

const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;
const float SWH = SCREEN_WIDTH / 2;
const float SHH = SCREEN_HEIGHT / 2;
const int FPS = 60;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "03_triangles");

    SetTargetFPS(FPS);
    while (!WindowShouldClose())  {
        BeginDrawing();

        ClearBackground(BLACK);

        Vector2 triangle1[3] = {{SWH - 300, SHH - 200}, {SWH - 100, SHH - 200}, {SWH - 200, SHH - 400}};
        DrawTriangle(triangle1[0], triangle1[1], triangle1[2], RED);

        Vector2 triangle2[3] = {{SWH + 200, SHH - 200}, {SWH + 400, SHH - 200}, {SWH + 300, SHH - 400}};
        DrawTriangleLines(triangle2[0], triangle2[1], triangle2[2], BLUE);

        Vector2 triangle3[] = {
                {SWH, SHH},                                     // центр
                { SWH + 100, SHH },              // справа
                { SWH + 70,  SHH + 70 },          // снизу-справа
                { SWH,       SHH + 100 },         // снизу
                { SWH - 70,  SHH + 70 },          // снизу-слева
                { SWH - 100, SHH },              // слева
                { SWH - 70,  SHH - 70 },          // сверху-слева
                { SWH,       SHH - 100 },         // сверху
                { SWH + 70,  SHH - 70 },          // сверху-справа
                { SWH + 100, SHH }               // замыкаем (повтор первой точки)
        };

//        Vector2 triangle3[3] = {{SWH + 200, SHH + 200}, {SWH + 400, SHH + 200}, {SWH + 300, SHH + 400}};
        DrawTriangleFan(triangle3, sizeof(triangle3) / sizeof(Vector2), YELLOW);
//
//        const Vector2 triangleStrip[] = {
//            {SWH - 500, SHH - 700},
//            {SWH - 400, SHH - 700},
//            {SWH - 300, SHH - 800},
//            {SWH - 200, SHH - 700},
//            {SWH - 100, SHH - 800},
//            {SWH, SHH - 700},
//        };
//        DrawTriangleStrip(triangleStrip, 6, ORANGE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
