#ifndef HUD_H
#define HUD_H

#include "raylib.h"

typedef struct {
    Vector2 fps_pos;
    Rectangle live_rect;
    float live_margin;
    int font_size;
    Color color;
} hud_t;

void hud_init(hud_t *hud, Vector2 screen_res, int font_size, Color color);

void hud_render(const hud_t *hud, int lives);

#endif //HUD_H
