#include "screen.h"

#include <stdio.h>

// TODO: what if screen res will change?

void screen_pause_render(int arr_len, const char **texts, Vector2 screen_res, int *font_sizes, Color *colors) {
    const int gap = 100;
    for (int i = 0; i < arr_len; ++i) {
        const int text_i_width = MeasureText(texts[i], font_sizes[i]);
        const Vector2 pos = {(screen_res.x - text_i_width) / 2, screen_res.y / 2 - gap + i * gap};
        DrawText(texts[i], pos.x, pos.y, font_sizes[i], colors[i]);
    }
}

void screen_game_over_render(
    int score,
    int arr_len,
    const char **texts,
    Vector2 screen_res,
    int *font_sizes,
    Color *colors
) {
    const int gap = 100;
    for (int i = 0; i < arr_len; ++i) {
        if (i == 1) {
            char buf[64];
            snprintf(buf, sizeof(buf), "%s %d", texts[i], score);
            const int text_i_width = MeasureText(buf, font_sizes[i]);
            const Vector2 pos = {(screen_res.x - text_i_width) / 2, screen_res.y / 2 - gap + i * gap};
            DrawText(buf, pos.x, pos.y, font_sizes[i], colors[i]);
        } else {
            const int text_i_width = MeasureText(texts[i], font_sizes[i]);
            const Vector2 pos = {(screen_res.x - text_i_width) / 2, screen_res.y / 2 - gap + i * gap};
            DrawText(texts[i], pos.x, pos.y, font_sizes[i], colors[i]);
        }
    }
}
