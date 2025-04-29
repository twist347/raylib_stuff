#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"

typedef struct {
    Vector2 screen_res;
    int fps;
    const char *title;
    Color bg_color;
} screen_config_t;

typedef struct {
    float cell_size;
} game_play_config_t;

typedef struct {
    Color color;
} markings_config_t;

typedef struct {
    Vector2 fps_pos;
    Vector2 score_pos;
    int score_font_size;
    Color score_color;
} hud_config_t;

typedef struct {
    float speed;
    float speed_factor;
    int init_size;
    int max_size;
    Color head_color;
    Color cell_color;
} snake_config_t;

typedef struct {
    Color color;
} food_config_t;

typedef struct {
    screen_config_t screen_config;
    game_play_config_t gameplay_config;
    markings_config_t markings_config;
    hud_config_t hud_config;
    snake_config_t snake_config;
    food_config_t food_config;
} config_t;

void config_default_init(config_t *config);

#endif //CONFIG_H
