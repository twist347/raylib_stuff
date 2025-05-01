#include "game.h"

#include <time.h>

#include "config_data.h"
#include "utils.h"
#include "screen.h"

static bool check_snake_cell_food_collision(const snake_cell_t *cell, float cell_size, const food_t *food);

static bool snake_eat_food(const snake_t *snake, const food_t *food);

static bool food_on_snake(const food_t *food, const snake_t *snake);

static void render_game_play(const game_t *game);

static void update_game_play(game_t *game, float dt);

static bool try_toggle_pause(game_t *game);

void game_init(game_t *game) {
    screen_settings_init(&game->screen_settings, SCREEN_RES, FPS, TITLE, BG_COLOR);
    screen_pause_init(
        &game->pause_screen,
        game->screen_settings.res,
        PAUSE_SCREEN_TITLES,
        PAUSE_SCREEN_FONT_SIZES,
        PAUSE_SCREEN_TEXT_COLORS
    );
    screen_game_over_init(
        &game->game_over_screen,
        game->screen_settings.res,
        GAME_OVER_SCREEN_TITLES,
        GAME_OVER_SCREEN_FONT_SIZES,
        GAME_OVER_SCREEN_TEXT_COLORS
    );

    InitWindow(VEC2_SPLIT(game->screen_settings.res), game->screen_settings.title);
    SetTargetFPS(game->screen_settings.fps);

    // for food spawn
    SetRandomSeed(time(NULL));

    markings_init(&game->markings, MARKINGS_COLOR);

    game->cell_size = CELL_SIZE;

    hud_init(&game->hud, HUD_FPS_POS, HUD_SCORE_POS, HUD_SCORE_FONT_SIZE, HUD_SCORE_COLOR);

    InitAudioDevice();
    sound_init_all(game->sounds, SOUNDS_NAMES);

    snake_init(
        &game->snake,
        SNAKE_INIT_SIZE,
        SNAKE_INIT_CAP,
        game->cell_size,
        SNAKE_SPEED,
        SNAKE_SPEED_FACTOR,
        SNAKE_HEAD_COLOR,
        SNAKE_CELL_COLOR,
        game->screen_settings.res
    );

    food_init(&game->food, game->screen_settings.res, game->cell_size, FOOD_COLOR);

    while (food_on_snake(&game->food, &game->snake)) {
        food_spawn(&game->food, game->screen_settings.res);
    }

    game->score = 0;
    game->running = true;
    game->state = STATE_PLAYING;
}

void game_reset(game_t *game) {
    snake_destroy(&game->snake);

    snake_init(
        &game->snake,
        SNAKE_INIT_SIZE,
        SNAKE_INIT_CAP,
        game->cell_size,
        SNAKE_SPEED,
        SNAKE_SPEED_FACTOR,
        SNAKE_HEAD_COLOR,
        SNAKE_CELL_COLOR,
        game->screen_settings.res
    );

    food_init(&game->food, game->screen_settings.res, game->cell_size, FOOD_COLOR);

    game->score = 0;
    game->running = true;
    game->state = STATE_PLAYING;
}

void game_destroy(game_t *game) {
    snake_destroy(&game->snake);
    sound_destroy_all(game->sounds);
    CloseAudioDevice();
    CloseWindow();
}

void game_update(game_t *game, float dt) {
    try_toggle_pause(game);

    switch (game->state) {
        case STATE_PLAYING:
            update_game_play(game, dt);
            break;
        case STATE_PAUSED:
            // nothing to do
            break;
        case STATE_GAME_OVER:
            if (IsKeyPressed(KEY_ENTER)) {
                game_reset(game);
            }
            break;
    }
}

void game_render(const game_t *game) {
    BeginDrawing();

    ClearBackground(game->screen_settings.bg_color);

    if (game->state != STATE_GAME_OVER) {
        render_game_play(game);
    }
    if (game->state == STATE_PAUSED) {
        screen_pause_render(&game->pause_screen);
    } else if (game->state == STATE_GAME_OVER) {
        screen_game_over_render(&game->game_over_screen, game->score);
    }

    EndDrawing();
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

static void render_game_play(const game_t *game) {
    markings_render(&game->markings, game->screen_settings.res, game->cell_size);
    snake_render(&game->snake);
    food_render(&game->food);
    hud_render(&game->hud, game->score);
}

static void update_game_play(game_t *game, float dt) {
    snake_update(&game->snake, dt);

    // TODO: maybe place snake_check_self_collision and snake_check_self_collision into snake_update
    if (snake_check_self_collision(&game->snake) || snake_check_walls_collision(&game->snake, game->screen_settings.res)) {
        game->state = STATE_GAME_OVER;
        return;
    }

    if (snake_eat_food(&game->snake, &game->food)) {
        PlaySound(game->sounds[SOUND_BITE]);
        snake_grow(&game->snake);
        ++game->score;

        do {
            food_spawn(&game->food, game->screen_settings.res);
        } while (food_on_snake(&game->food, &game->snake));

        snake_grow_speed(&game->snake);
    }
}

static bool try_toggle_pause(game_t *game) {
    if (game->state != STATE_GAME_OVER && IsKeyPressed(KEY_P)) {
        PlaySound(game->sounds[SOUND_CLICK_BUTTON]);
        game->state = (game->state == STATE_PLAYING) ? STATE_PAUSED : STATE_PLAYING;
        return true;
    }
    return false;
}
