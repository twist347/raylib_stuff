#ifndef GAME_H
#define GAME_H

// #include "ecs.h"

#include "world.h"

typedef struct {
    world_t world;
    Vector2 screen_res;
    const char *window_title;
    bool running;
} game_t;

game_t *game_create();
void game_init(game_t *game);
void game_update(game_t *game, float dt);
void game_render(game_t *game);
void game_destroy(game_t *game);

#endif
