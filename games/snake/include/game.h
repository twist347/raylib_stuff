#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "config.h"
#include "food.h"
#include "snake.h"

typedef struct {
    config_t config;
    snake_t snake;
    food_t food;
    int score;
    bool running;
} game_t;

void game_init(game_t *game);

void game_update(game_t *game, float dt);

void game_render(game_t *game);

void game_destroy(game_t *game);

#endif //GAME_H
