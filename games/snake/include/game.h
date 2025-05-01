#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "screen_settings.h"
#include "markings.h"
#include "hud.h"
#include "audio.h"
#include "food.h"
#include "snake.h"

typedef enum {
    STATE_PLAYING = 0,
    STATE_PAUSED = 1,
    STATE_GAME_OVER
} game_state_e;

typedef struct {
    screen_settings_t screen_settings;
    markings_t markings;
    float cell_size;
    hud_t hud;
    Sound sounds[SOUNDS_LEN];
    snake_t snake;
    food_t food;
    int score;
    game_state_e state;
} game_t;

void game_init(game_t *game);

void game_destroy(game_t *game);

void game_input(game_t *game);

void game_update(game_t *game, float dt);

void game_render(const game_t *game);

void game_reset(game_t *game);

#endif //GAME_H
