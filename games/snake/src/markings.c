#include "markings.h"

void markings_init(markings_t *markings, Color color) {
    markings->color = color;
}

void markings_render(const markings_t *markings, Vector2 screen_res, float cell_size) {
    for (int x = (int) cell_size; x < screen_res.x; x += (int) cell_size) {
        DrawLine(x, 0, x, screen_res.y, markings->color);
    }

    for (int y = (int) cell_size; y < screen_res.y; y += (int) cell_size) {
        DrawLine(0, y, screen_res.x, y, markings->color);
    }
}