#include "game.h"

#include <stdbool.h>
#include <stdlib.h>

#include "raylib.h"

#include "config.h"
#include "systems/system_all.h"

game_t *game_create() {
    game_t *game = malloc(sizeof(game_t));
    game->screen_res = SCREEN_RES;
    game->window_title = SCREEN_TITLE;
    game->running = true;

    InitWindow((int) game->screen_res.x, (int) game->screen_res.y, game->window_title);
    SetTargetFPS(TARGET_FPS);

    world_create(&game->world);
    return game;
}

void game_init(game_t *game) {
    world_t *world = &game->world;
    const Vector2 sr = game->screen_res;

    const entity_t left_paddle = entity_create(world);
    add_transform_c(world, left_paddle, 50.f, sr.y * 0.5f - 50.f);
    add_input_c(world, left_paddle, KEY_W, KEY_S);
    add_render_c(world, left_paddle, PADDLE_COLOR);
    add_phys_c(world, left_paddle, (Vector2){0.f, PADDLE_VEL});
    add_paddle_c(world, left_paddle, PADDLE_SIZE.x, PADDLE_SIZE.y);

    const entity_t right_paddle = entity_create(world);
    add_transform_c(world, right_paddle, sr.x - 60.f, sr.y * 0.5f - 50.f);
    add_render_c(world, right_paddle, PADDLE_COLOR);
    add_input_c(world, right_paddle, KEY_UP, KEY_DOWN);
    add_phys_c(world, right_paddle, (Vector2){0.f, PADDLE_VEL});
    add_paddle_c(world, right_paddle, PADDLE_SIZE.x, PADDLE_SIZE.y);

    const entity_t ball = entity_create(world);
    add_transform_c(world, ball, sr.x * 0.5f, sr.y * 0.5f);
    add_phys_c(world, ball, BALL_VEL);
    add_ball_c(world, ball, BALL_RADIUS, BALL_VEL.x);
    add_render_c(world, ball, BALL_COLOR);

    const entity_t score = entity_create(world);
    add_score_c(world, score);
    add_render_c(world, score, HUD_COLOR);
}

void game_update(game_t *game, float dt) {
    if (WindowShouldClose()) {
        game->running = false;
        return;
    }

    system_input(&game->world);
    system_transform(&game->world, dt);
    system_collisions(&game->world, game->screen_res);
    system_score(&game->world, game->screen_res);
}

void game_render(game_t *game) {
    BeginDrawing();

    ClearBackground(BG_COLOR);

    DrawFPS(10, 10);

    system_render(&game->world, game->screen_res);

    EndDrawing();
}

void game_destroy(game_t *game) {
    world_destroy(&game->world);
    free(game);
    CloseWindow();
}
