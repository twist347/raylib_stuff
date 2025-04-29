#include "hud.h"

static void draw_score(int score, Vector2 pos, int font_size, Color color);

static void draw_fps(Vector2 hud_pos);

void hud_render(int score, Vector2 score_pos, int score_font_size, Color score_color, Vector2 fps_pos) {
    draw_score(score, score_pos, score_font_size, score_color);
    draw_fps(fps_pos);
}

static void draw_score(int score, Vector2 pos, int font_size, Color color) {
    DrawText(TextFormat("%d", score), (int) pos.x, (int) pos.y, font_size, color);
}

static void draw_fps(Vector2 pos) {
    DrawFPS((int) pos.x, (int) pos.y);
}


