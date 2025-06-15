#include "game.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "raylib.h"

#include "config.h"
#include "systems/system_all.h"

static Vector2 random_direction(float max_angle_deg, bool to_left);

game_t *game_create() {
    game_t *game = malloc(sizeof(game_t));
    game->screen_res = SCREEN_RES;
    game->window_title = SCREEN_TITLE;
    game->running = true;

    InitWindow((int) game->screen_res.x, (int) game->screen_res.y, game->window_title);
    SetTargetFPS(TARGET_FPS);
    srand(time(NULL));

    InitAudioDevice();

    world_create(&game->world);
    return game;
}

void game_load_resources(game_t *game) {
    game->world.assets.sfx[ASSETS_SFX_BOUNCE] = LoadSound(ASSETS_DIR "/sounds/bounce.wav");
    game->world.assets.sfx[ASSETS_SFX_WALL_HIT] = LoadSound(ASSETS_DIR "/sounds/wall_hit.wav");
    game->world.assets.music[ASSETS_MUSIC_BG] = LoadMusicStream(ASSETS_DIR "/music/bg_music.ogg");
}

void game_init(game_t *game) {
    world_t *world = &game->world;
    const Vector2 sr = game->screen_res;

    const entity_t left_paddle = entity_create(world);
    add_transform_c(world, left_paddle, 50.f, sr.y * 0.5f - 50.f);
    add_input_c(world, left_paddle, KEY_W, KEY_S);
    add_render_c(world, left_paddle, PADDLE_COLOR);
    add_phys_c(world, left_paddle, PADDLE_VEL, (Vector2){0.f, 0.f});
    add_paddle_c(world, left_paddle, PADDLE_SIZE.x, PADDLE_SIZE.y, PADDLE_VEL);

    const entity_t right_paddle = entity_create(world);
    add_transform_c(world, right_paddle, sr.x - 60.f, sr.y * 0.5f - 50.f);
    add_render_c(world, right_paddle, PADDLE_COLOR);
    add_input_c(world, right_paddle, KEY_UP, KEY_DOWN);
    add_phys_c(world, right_paddle, PADDLE_VEL, (Vector2){0.f, 0.f});
    add_paddle_c(world, right_paddle, PADDLE_SIZE.x, PADDLE_SIZE.y, PADDLE_VEL);

    const entity_t ball = entity_create(world);
    add_transform_c(world, ball, sr.x * 0.5f, sr.y * 0.5f);
    add_phys_c(world, ball, BALL_VEL, random_direction(45.f, true));
    add_ball_c(world, ball, BALL_RADIUS, BALL_VEL, BALL_VEL_SCALE);
    add_render_c(world, ball, BALL_COLOR);
    const sound_info_t ball_sounds[] = {{ASSETS_SFX_BOUNCE, 1.f}, {ASSETS_SFX_WALL_HIT, 1.f}};
    add_sounds(world, ball, ball_sounds, sizeof(ball_sounds) / sizeof(ball_sounds[0]));

    const entity_t score = entity_create(world);
    add_score_c(world, score);
    add_render_c(world, score, HUD_COLOR);

    const entity_t bg_music = entity_create(world);
    add_music_c(world, bg_music, ASSETS_MUSIC_BG, 0.7f, true, true);
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
    system_sound(&game->world);
    system_music(&game->world);
}

void game_render(game_t *game) {
    BeginDrawing();

    ClearBackground(BG_COLOR);

    DrawFPS(10, 10);

    system_render(&game->world, game->screen_res);

    EndDrawing();
}

void game_unload_resources(game_t *game) {
    for (size_t i = 0; i < ASSETS_SFX_COUNT; ++i) {
        UnloadSound(game->world.assets.sfx[i]);
    }
    for (size_t i = 0; i < ASSETS_MUSIC_COUNT; ++i) {
        UnloadMusicStream(game->world.assets.music[i]);
    }
}

void game_destroy(game_t *game) {
    world_destroy(&game->world);
    CloseAudioDevice();
    CloseWindow();
    free(game);
}

static Vector2 random_direction(float max_angle_deg, bool to_left) {
    const float max_rad = max_angle_deg * DEG2RAD;
    const float t = ((float) rand() / (float) RAND_MAX) * 2.0f - 1.0f;
    const float base = to_left ? (float) M_PI : 0.0f;
    const float angle = base + t * max_rad;
    return (Vector2){cosf(angle), sinf(angle)};
}
