#ifndef HUD_H
#define HUD_H

#include "raylib.h"

typedef struct {
    Vector2 fps_pos;
    Vector2 score_pos;
    int score_font_size;
    Color score_color;
} hud_t;

void hud_init(
    hud_t *hud,
    Vector2 fps_pos,
    Vector2 score_pos,
    int score_font_size,
    Color score_color
);

void hud_render(const hud_t *hud, int score);

#endif //HUD_H
