#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"

void screen_pause_render(int arr_len, const char **texts, Vector2 screen_res, int *font_sizes, Color *colors);

void screen_game_over_render(
    int score,
    int arr_len,
    const char **texts,
    Vector2 screen_res,
    int *font_sizes,
    Color *colors
);

// void screen_game_over_render(const game_over_screen_t *screen, int final_score);

#endif //SCREENS_H
