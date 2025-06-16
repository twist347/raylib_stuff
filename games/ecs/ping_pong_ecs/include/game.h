#ifndef GAME_H
#define GAME_H

#include "world.h"

typedef enum {
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSE,
    GAME_STATE_MENU
} game_state_t;

typedef struct {
    world_t world;
    game_state_t state;
    Vector2 screen_res;
    const char *window_title;
    bool running;
} game_t;

game_t *game_create();
void game_load_resources(game_t *game);
void game_init(game_t *game);
void game_update(game_t *game, float dt);
void game_render(game_t *game);
void game_unload_resources(game_t *game);
void game_destroy(game_t *game);

#endif
