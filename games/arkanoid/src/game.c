#include "game.h"
#include "config_data.h"
#include "collisions.h"
#include "ui.h"

#include <stdlib.h>
#include <assert.h>

static void helper_bricks_init(brick_t *bricks);
static void helper_bricks_render(const brick_t *bricks, int count);
static void helper_handle_ball_bricks_collision(brick_t *bricks, int count, int *cur_count, ball_t *ball);
static void helper_reset_ball_and_paddle(game_t *game);
static void helper_handle_game_over(game_t *game);
static void helper_game_reset(game_t *game);
static void helper_game_play_render(const game_t *game);
static void helper_game_play_update(game_t *game, float dt);

game_t *game_init() {
    // TODO: handle malloc
    game_t *game = malloc(sizeof(game_t));

    game->state = GAME_STATE_PLAY;
    screen_settings_init(&game->screen_settings, SCREEN_RES, SCREEN_TITLE, FPS, BG_COLOR);
    hud_init(&game->hud, game->screen_settings.res, HUD_TEXT_FONT_SIZE, HUD_TEXT_COLOR);
    helper_reset_ball_and_paddle(game);

    game->bricks_count = BRICKS_LINES * BRICKS_PER_LINE;
    game->bricks_cur_count = game->bricks_count;
    // TODO: handle malloc
    brick_t *bricks = malloc(game->bricks_count * sizeof(brick_t));
    helper_bricks_init(bricks);
    game->bricks = bricks;

    assert(game);
    InitWindow(game->screen_settings.res.x, game->screen_settings.res.y, game->screen_settings.title);
    SetTargetFPS(game->screen_settings.fps);

    game->lives = PLAYER_LIVES;

    return game;
}

void game_destroy(game_t *game) {
    free(game->bricks);
    free(game);
    CloseWindow();
}

void game_input(game_t *game) {
    switch (game->state) {
        case GAME_STATE_PLAY:
            paddle_input(&game->paddle);
            if (IsKeyPressed(KEY_P)) {
                game->state = GAME_STATE_PAUSE;
            }
            break;
        case GAME_STATE_PAUSE:
            if (IsKeyPressed(KEY_P)) {
                game->state = GAME_STATE_PLAY;
            }
            break;
        case GAME_STATE_GAME_OVER:
            if (IsKeyPressed(KEY_ENTER)) {
                helper_game_reset(game);
            }
            break;
    }
}

void game_update(game_t *game, float dt) {
    switch (game->state) {
        case GAME_STATE_PLAY:
            helper_game_play_update(game, dt);
            break;
        case GAME_STATE_PAUSE:
            break;
        case GAME_STATE_GAME_OVER:
            break;
    }
}

void game_render(const game_t *game) {
    BeginDrawing();

    ClearBackground(game->screen_settings.bg_color);

    switch (game->state) {
        case GAME_STATE_PLAY:
            helper_game_play_render(game);
            break;
        case GAME_STATE_PAUSE:
            helper_game_play_render(game);
            ui_render_pause(game->screen_settings.res);
            break;
        case GAME_STATE_GAME_OVER:
            ui_render_game_over(game->screen_settings.res);
            break;
    }

    EndDrawing();
}

static void helper_bricks_init(brick_t *bricks) {
    const Vector2 brick_sides = {
        (SCREEN_RES.x - BRICK_MARGIN * (BRICKS_PER_LINE + 1)) / BRICKS_PER_LINE,
        BRICK_WIDTH
    };
    for (int i = 0; i < BRICKS_LINES; ++i) {
        for (int j = 0; j < BRICKS_PER_LINE; ++j) {
            const int idx = i * BRICKS_PER_LINE + j;
            const Rectangle rect = {
                BRICK_MARGIN + j * (brick_sides.x + BRICK_MARGIN),
                BRICK_MARGIN + i * (brick_sides.y + BRICK_MARGIN),
                brick_sides.x - BRICK_MARGIN,
                brick_sides.y - BRICK_MARGIN,
            };
            brick_init(&bricks[idx], rect, true, BRICK_COLOR);
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

static void helper_handle_ball_bricks_collision(brick_t *bricks, int count, int *cur_count, ball_t *ball) {
    for (int i = 0; i < count; ++i) {
        brick_t *brick = &bricks[i];
        if (brick->active && CheckCollisionCircleRec(ball->center_pos, ball->radius, brick->rect)) {
            brick->active = false;
            --(*cur_count);
            collisions_handle_brick_ball(brick, ball);
            break;
        }
    }
}

static void helper_reset_ball_and_paddle(game_t *game) {
    paddle_init(
        &game->paddle,
        (Rectangle){.x = PADDLE_INIT_POS.x, .y = PADDLE_INIT_POS.y, .width = PADDLE_SIDES.x, .height = PADDLE_SIDES.y},
        PADDLE_VELOCITY,
        PADDLE_COLOR
    );
    ball_init(&game->ball, BALL_INIT_POS, BALL_RADIUS, BALL_VELOCITY, BALL_COLOR);
}

static void helper_handle_game_over(game_t *game) {
    if (ball_check_bottom_collision(&game->ball, game->screen_settings.res.y)) {
        --game->lives;
        if (game->lives > 0) {
            helper_reset_ball_and_paddle(game);
        } else {
            game->state = GAME_STATE_GAME_OVER;
        }
    }
}

static void helper_game_reset(game_t *game) {
    helper_reset_ball_and_paddle(game);
    helper_bricks_init(game->bricks);
    game->lives = PLAYER_LIVES;
    game->state = GAME_STATE_PLAY;
}

static void helper_game_play_render(const game_t *game) {
    paddle_render(&game->paddle);
    ball_render(&game->ball);
    helper_bricks_render(game->bricks, game->bricks_count);
    hud_render(&game->hud, game->lives);
}

static void helper_game_play_update(game_t *game, float dt) {
    paddle_update(&game->paddle, dt);
    paddle_handle_wall_collision(&game->paddle, game->screen_settings.res.x);
    ball_update(&game->ball, dt);
    ball_handle_wall_collision(&game->ball, game->screen_settings.res);
    collisions_handle_paddle_ball(&game->paddle, &game->ball);
    helper_handle_ball_bricks_collision(game->bricks, game->bricks_count, &game->bricks_cur_count, &game->ball);
    helper_handle_game_over(game);
}
