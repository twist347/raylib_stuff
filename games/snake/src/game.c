#include "game.h"

#include <time.h>

#include "markings.h"
#include "hud.h"

#define VEC2_SPLIT(v) ((v).x), ((v).y)

static bool check_snake_cell_food_collision(const snake_cell_t *cell, float cell_size, const food_t *food);

static bool snake_eat_food(const snake_t *snake, const food_t *food);

static bool food_on_snake( const food_t *food, const snake_t *snake);

void game_init(game_t *game) {
    config_default_init(&game->config);

    InitWindow(VEC2_SPLIT(game->config.screen_config.screen_res), game->config.screen_config.title);
    SetTargetFPS(game->config.screen_config.fps);

    // for food spawn
    SetRandomSeed(time(NULL));

    snake_init(
        &game->snake,
        game->config.snake_config.init_size,
        game->config.snake_config.max_size,
        game->config.gameplay_config.cell_size,
        game->config.snake_config.speed,
        game->config.snake_config.speed_factor,
        game->config.snake_config.head_color,
        game->config.snake_config.cell_color,
        game->config.screen_config.screen_res
    );

    food_init(
        &game->food,
        game->config.screen_config.screen_res,
        game->config.gameplay_config.cell_size,
        game->config.food_config.color
    );

    while (food_on_snake(&game->food, &game->snake)) {
        food_spawn(&game->food, game->config.screen_config.screen_res);
    }

    game->score = 0;
    game->running = true;
}

void game_update(game_t *game, float dt) {
    // TODO: maybe place snake_check_self_collision and snake_check_self_collision into snake_update
    snake_update(&game->snake, dt);

    if (
        snake_check_self_collision(&game->snake) ||
        snake_check_walls_collision(&game->snake, game->config.screen_config.screen_res)
    ) {
        game->running = false;
    }

    if (snake_eat_food(&game->snake, &game->food)) {
        snake_grow(&game->snake);
        ++game->score;
        do {
            food_spawn(&game->food, game->config.screen_config.screen_res);
        } while (food_on_snake(&game->food, &game->snake));
        snake_grow_speed(&game->snake);
    }
}

void game_render(game_t *game) {
    BeginDrawing();

    ClearBackground(game->config.screen_config.bg_color);

    markings_render(
        game->config.screen_config.screen_res,
        game->config.gameplay_config.cell_size,
        game->config.markings_config.color
    );
    snake_render(&game->snake);
    food_render(&game->food);
    hud_render(
        game->score,
        game->config.hud_config.score_pos,
        game->config.hud_config.score_font_size,
        game->config.hud_config.score_color,
        game->config.hud_config.fps_pos
    );

    EndDrawing();
}

void game_destroy(game_t *game) {
    snake_destroy(&game->snake);
    CloseWindow();
}

static bool check_snake_cell_food_collision(const snake_cell_t *cell, float cell_size, const food_t *food) {
    return CheckCollisionPointRec(
        (Vector2){cell->pos.x + cell_size / 2.f, cell->pos.y + cell_size / 2.f},
        (Rectangle){food->pos.x, food->pos.y, cell_size, cell_size}
    );
}

static bool snake_eat_food(const snake_t *snake, const food_t *food) {
    return check_snake_cell_food_collision(&snake->cells[0], snake->cell_size, food);
}

static bool food_on_snake(const food_t *food, const snake_t *snake) {
    for (int i = 0; i < snake->len; ++i) {
        if (check_snake_cell_food_collision(&snake->cells[i], snake->cell_size, food)) {
            return true;
        }
    }
    return false;
}
