#include "raylib.h"

int main() {
    const int WIDTH = 1920, HEIGHT = 1080;
    InitWindow(WIDTH, HEIGHT, "Mandelbrot Set");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                float zx = 0.0f, zy = 0.0f;
                float cx = (x - WIDTH / 2.0f) * 4.0f / WIDTH;
                float cy = (y - HEIGHT / 2.0f) * 4.0f / HEIGHT;
                int i = 0;
                while (zx * zx + zy * zy < 4.0f && i < 255) {
                    float tmp = zx * zx - zy * zy + cx;
                    zy = 2.0f * zx * zy + cy;
                    zx = tmp;
                    i++;
                }
                DrawPixel(x, y, (Color){(unsigned char) i, (unsigned char) i, (unsigned char) i, 255});
            }
        }

        DrawText("Mandelbrot Set", 10, 10, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
