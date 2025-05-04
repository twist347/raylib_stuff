#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include "raylib.h"

typedef enum {
    PLAYER_DIR_LEFT,
    PLAYER_DIR_RIGHT,
    PLAYER_DIR_UP,
    PLAYER_DIR_NONE
} player_dir_e;

typedef struct {
    player_dir_e dir;
    Rectangle rect; // (x, y) - pos of top left corner, (width, height) - sides of player
    Vector2 vel;
    bool on_ground;
    float jump_force;
    Color color;
} player_t;

void player_init(
    player_t *player,
    player_dir_e dir,
    Rectangle rect,
    Vector2 vel,
    bool on_ground,
    float jump_force,
    Color color
);

void player_input(player_t *player);

void player_update(player_t *player, float gravity, Vector2 screen_res, float dt);

void player_render(const player_t *player);

#endif //PLAYER_H
