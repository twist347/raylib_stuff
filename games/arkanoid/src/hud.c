#include "hud.h"

#include "raylib.h"

static void helper_hud_fps_render(const hud_t *hud);

static void helper_hud_lives_render(const hud_t *hud, int lives);

void hud_init(hud_t *hud, Vector2 screen_res, int font_size, Color color) {
    hud->fps_pos = (Vector2){10, 10};
    hud->live_rect = (Rectangle){
        50.f, screen_res.y - 30.f,
        40.f, 10.f
    };
    hud->live_margin = 5.f;
    hud->font_size = font_size;
    hud->color = color;
}

void hud_render(const hud_t *hud, int lives) {
    helper_hud_fps_render(hud);
    helper_hud_lives_render(hud, lives);
}

static void helper_hud_fps_render(const hud_t *hud) {
    DrawFPS(hud->fps_pos.x, hud->fps_pos.y);
}

static void helper_hud_lives_render(const hud_t *hud, int lives) {
    for (int i = 0; i < lives; ++i) {
        DrawRectangle(
            hud->live_rect.x + i * (hud->live_rect.x + hud->live_margin),
            hud->live_rect.y, hud->live_rect.width, hud->live_rect.height,
            hud->color
        );
    }
}
