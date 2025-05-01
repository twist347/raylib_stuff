#ifndef SCREENS_H
#define SCREENS_H

#include "raylib.h"

// TODO: rewrite it

typedef struct {
    const char *text;
    int text_font_size;
    int text_width;
    Vector2 text_pos;
    Color text_color;
} pause_screen_item_t;

typedef struct {
    pause_screen_item_t pause_item;
    pause_screen_item_t resume_item;
} pause_screen_t;

typedef struct {
    const char *text;
    int text_font_size;
    int text_width;
    Vector2 text_pos;
    Color text_color;
} game_over_screen_item_t;

typedef struct {
    game_over_screen_item_t game_over_item;
    game_over_screen_item_t score_item;
    game_over_screen_item_t restart_item;
    game_over_screen_item_t exit_item;
} game_over_screen_t;

// void screen_

void screen_pause_init(
    pause_screen_t *screen,
    Vector2 screen_res,
    const char **titles,
    int *font_sizes,
    Color *text_colors
);

void screen_pause_render(const pause_screen_t *screen);

void screen_game_over_init(
    game_over_screen_t *screen,
    Vector2 screen_res,
    const char **titles,
    int *font_sizes,
    Color *text_colors
);

void screen_game_over_render(const game_over_screen_t *screen, int final_score);

#endif //SCREENS_H
