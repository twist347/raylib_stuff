#include "game.h"

#include "config_data.h"

#include <stdlib.h>

game_t *game_init() {
    game_t *game = malloc(sizeof(game_t));

    screen_settings_init(&game->screen, SCREEN_RES, SCREEN_TITLE, FPS, BG_COLOR);

    player_init(
        &game->player,
        PLAYER_DIR_NONE,
        (Rectangle){
            .x = game->screen.res.x / 2.f, .y = game->screen.res.y - PLAYER_HEIGHT,
            .width = PLAYER_WIDTH, .height = PLAYER_HEIGHT
        },
        PLAYER_VEL,
        true,
        PLAYER_JUMP_FORCE,
        PLAYER_COLOR
    );

    game->gravity = GRAVITY;

    InitWindow(game->screen.res.x, game->screen.res.y, game->screen.title);
    SetTargetFPS(game->screen.fps);

    return game;
}

void game_destroy(game_t *game) {
    free(game);
    CloseWindow();
}

void game_input(game_t *game) {
    player_input(&game->player);
}

void game_update(game_t *game, float dt) {
    player_update(&game->player, game->gravity, game->screen.res, dt);
}

void game_render(const game_t *game) {
    BeginDrawing();

    ClearBackground(game->screen.bg_color);

    player_render(&game->player);

    EndDrawing();
}