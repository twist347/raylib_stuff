#ifndef GAME_H
#define GAME_H

#include "screen_settings.h"
#include "player.h"

typedef struct {
    screen_settings_t screen;
    player_t player;
    float gravity;
} game_t;

game_t *game_init();

void game_destroy(game_t *game);

void game_input(game_t *game);

void game_update(game_t *game, float dt);

void game_render(const game_t *game);

#endif //GAME_H
