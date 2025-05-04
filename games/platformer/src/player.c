#include "player.h"

static void helper_apply_gravity(player_t *player, float gravity, float dt);
static void helper_floor_collision(player_t *player, Vector2 screen_res);

void player_init(
    player_t *player,
    player_dir_e dir,
    Rectangle rect,
    Vector2 vel,
    bool on_ground,
    float jump_force,
    Color color
) {
    player->dir = dir;
    player->rect = rect;
    player->vel = vel;
    player->on_ground = on_ground;
    player->jump_force = jump_force;
    player->color = color;
}

void player_input(player_t *player) {
    const bool left = IsKeyDown(KEY_LEFT);
    const bool right = IsKeyDown(KEY_RIGHT);
    const bool jump = IsKeyDown(KEY_SPACE);

    if (left && right) {
        player->dir = PLAYER_DIR_NONE;
    } else if (left) {
        player->dir = PLAYER_DIR_LEFT;
    } else if (right) {
        player->dir = PLAYER_DIR_RIGHT;
    }

    if (jump && player->on_ground) {
        player->dir = PLAYER_DIR_UP;
    }
}

void player_update(player_t *player, float gravity, Vector2 screen_res, float dt) {
    switch (player->dir) {
        case PLAYER_DIR_LEFT:
            player->rect.x -= player->vel.x * dt;
            break;
        case PLAYER_DIR_RIGHT:
            player->rect.x += player->vel.x * dt;
            break;
        case PLAYER_DIR_UP:
            if (player->on_ground) {
                player->vel.y = -player->jump_force;
                player->on_ground = false;
            }
            // for hor move in jump
            player->dir = PLAYER_DIR_NONE;
        case PLAYER_DIR_NONE:
            break;
    }

    helper_apply_gravity(player, gravity, dt);
    helper_floor_collision(player, screen_res);
}

void player_render(const player_t *player) {
    DrawRectangleRec(player->rect, player->color);
}

static void helper_apply_gravity(player_t *player, float gravity, float dt) {
    player->vel.y += gravity * dt;
    player->rect.y += player->vel.y * dt;
}

static void helper_floor_collision(player_t *player, Vector2 screen_res) {
    const float floor_level = screen_res.y - player->rect.height;
    if (player->rect.y >= floor_level) {
        player->rect.y = floor_level;
        player->on_ground = true;
        player->vel.y = 0;
    }
}