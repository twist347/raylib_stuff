#include <math.h>

#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int FPS = 60;

const float RADIUS = 60.f;
const int FRAMES_UNTIL_DIE = 60;

#define MAX_PIXELS 100000   
#define PIXELS_PER_FRAME 80       

typedef struct {
    Vector2 pos;
    Color color;
    int frames_until_die;
} Pixel;

void draw_sparks(Pixel *pixels, int *pix_idx) {
    for (int i = 0; i < PIXELS_PER_FRAME; ++i) {
        const Vector2 mouse_pos = GetMousePosition();
        // const int dx = GetRandomValue(-RADIUS, RADIUS);
        // const int dy = GetRandomValue(-RADIUS, RADIUS);

        const float angle = GetRandomValue(0, 359) * DEG2RAD;
        const float r = RADIUS * sqrt((float)GetRandomValue(0, 100) / 100.0f);
        const int dx = (int)(r * cos(angle));
        const int dy = (int)(r * sin(angle));
        
        pixels[*pix_idx].pos.x = mouse_pos.x + dx;
        pixels[*pix_idx].pos.y = mouse_pos.y + dy;
        pixels[*pix_idx].color = BLACK;
        pixels[*pix_idx].frames_until_die = FRAMES_UNTIL_DIE;
        
        *pix_idx = (*pix_idx + 1) % MAX_PIXELS;  // buffer
    }
    
    for (int i = 0; i < MAX_PIXELS; ++i) {
        if (pixels[i].frames_until_die > 0) {
            const float alpha = (float)pixels[i].frames_until_die / 60.0f;
            Color spark_сolor = { 
                pixels[i].color.r,
                pixels[i].color.g,
                pixels[i].color.b,
                (unsigned char)(255 * alpha)
            };
            // DrawCircleV(pixels[i].pos, 3, spark_сolor);
            DrawPixelV(pixels[i].pos, spark_сolor);
            --pixels[i].frames_until_die;
        }
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "01_pixels_sparks");
    SetTargetFPS(FPS);
    
    Pixel pixels[MAX_PIXELS] = {0};
    int pix_idx = 0;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        
        draw_sparks(pixels, &pix_idx);
        
        DrawFPS(10, 10);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
