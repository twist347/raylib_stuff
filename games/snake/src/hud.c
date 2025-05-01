#include "hud.h"

static void draw_score(int score, Vector2 pos, int font_size, Color color);

static void draw_fps(Vector2 hud_pos);

void hud_init(
    hud_t *hud,
    Vector2 fps_pos,
    Vector2 score_pos,
    int score_font_size,
    Color score_color
) {
    hud->fps_pos = fps_pos;
    hud->score_pos = score_pos;
    hud->score_font_size = score_font_size;
    hud->score_color = score_color;
}

void hud_render(const hud_t *hud, int score) {
    draw_score(score, hud->score_pos, hud->score_font_size, hud->score_color);
    draw_fps(hud->fps_pos);
}

static void draw_score(int score, Vector2 pos, int font_size, Color color) {
    DrawText(TextFormat("%d", score), (int) pos.x, (int) pos.y, font_size, color);
}

static void draw_fps(Vector2 pos) {
    DrawFPS((int) pos.x, (int) pos.y);
}


