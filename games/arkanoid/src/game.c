#include "game.h"
#include "config_data.h"
#include "collisions.h"

#include <stdlib.h>

static void helper_bricks_init(game_t *game);
static void helper_bricks_render(const brick_t *bricks, int count);
static void helper_handle_ball_bricks_collision(brick_t *bricks, int count, ball_t *ball);

game_t *game_init() {
    game_t *game = malloc(sizeof(game_t));

    screen_settings_init(&game->screen_settings, SCREEN_RES, SCREEN_TITLE, FPS, BG_COLOR);
    paddle_init(
        &game->paddle,
        (Rectangle){.x = PADDLE_INIT_POS.x, .y = PADDLE_INIT_POS.y, .width = PADDLE_SIDES.x, .height = PADDLE_SIDES.y},
        PADDLE_VELOCITY,
        PADDLE_COLOR
    );
    ball_init(&game->ball, BALL_INIT_POS, BALL_RADIUS, BALL_VELOCITY, BALL_COLOR);

    helper_bricks_init(game);

    InitWindow(game->screen_settings.res.x, game->screen_settings.res.y, game->screen_settings.title);
    SetTargetFPS(game->screen_settings.fps);

    game->active = true;

    return game;
}

void game_destroy(game_t *game) {
    free(game->bricks);
    free(game);
    CloseWindow();
}

void game_input(game_t *game) {
    paddle_input(&game->paddle);
}

void game_update(game_t *game, float dt) {
    paddle_update(&game->paddle, dt);
    paddle_handle_wall_collision(&game->paddle, game->screen_settings.res.x);
    ball_update(&game->ball, dt);
    ball_handle_wall_collision(&game->ball, game->screen_settings.res);
    collisions_handle_paddle_ball(&game->paddle, &game->ball);
    if (ball_check_bottom_collision(&game->ball, game->screen_settings.res.y)) {
        game->active = false;
    }
    helper_handle_ball_bricks_collision(game->bricks, game->bricks_count, &game->ball);
}

void game_render(const game_t *game) {
    BeginDrawing();

    ClearBackground(game->screen_settings.bg_color);

    paddle_render(&game->paddle);
    ball_render(&game->ball);
    helper_bricks_render(game->bricks, game->bricks_count);

    DrawFPS(10, 10);

    EndDrawing();
}

static void helper_bricks_init(game_t *game) {
    game->bricks_count = BRICKS_LINES * BRICKS_PER_LINE;
    game->bricks_cur_count = game->bricks_count;

    const Vector2 brick_sides = {(SCREEN_RES.x - BRICK_MARGIN * (BRICKS_PER_LINE + 1)) / BRICKS_PER_LINE, 40.f};
    game->bricks = malloc(game->bricks_count * sizeof(brick_t));
    for (int i = 0; i < BRICKS_LINES; ++i) {
        for (int j = 0; j < BRICKS_PER_LINE; ++j) {
            const int idx = i * BRICKS_PER_LINE + j;
            const Rectangle rect = {
                BRICK_MARGIN + j * (brick_sides.x + BRICK_MARGIN),
                BRICK_MARGIN + i * (brick_sides.y + BRICK_MARGIN),
                brick_sides.x - BRICK_MARGIN,
                brick_sides.y - BRICK_MARGIN,
            };
            brick_init(&game->bricks[idx], rect, true, BRICK_COLOR);
        }
    }
}

static void helper_bricks_render(const brick_t *bricks, int count) {
    for (int i = 0; i < count; ++i) {
        const brick_t *brick = &bricks[i];
        if (brick->active) {
            brick_render(brick);
        }
    }
}

static void helper_handle_ball_bricks_collision(brick_t *bricks, int count, ball_t *ball) {
    for (int i = 0; i < count; ++i) {
        brick_t *brick = &bricks[i];
        if (brick->active && CheckCollisionCircleRec(ball->center_pos, ball->radius, brick->rect)) {
            brick->active = false;
            ball->velocity.y *= -1.f;
            break;
        }
    }
}
