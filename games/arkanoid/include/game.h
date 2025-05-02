#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "screen_settings.h"
#include "hud.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"

typedef struct {
    screen_settings_t screen_settings;
    hud_t hud;
    paddle_t paddle;
    ball_t ball;
    int bricks_count;
    int bricks_cur_count;
    brick_t *bricks;
    int lives;
    bool active;
} game_t;

game_t *game_init();

void game_destroy(game_t *game);

void game_input(game_t *game);

void game_update(game_t *game, float dt);

void game_render(const game_t *game);

#endif //GAME_H
