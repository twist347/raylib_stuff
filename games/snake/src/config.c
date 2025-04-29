#include "config.h"

#include "config_data.h"

void config_default_init(config_t *config) {
    config->screen_config.screen_res = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT};
    config->screen_config.fps = FPS;
    config->screen_config.title = TITLE;
    config->screen_config.bg_color = BG_COLOR;

    config->gameplay_config.cell_size = CELL_SIZE;

    config->markings_config.color = MARKINGS_COLOR;

    config->hud_config.fps_pos = HUD_FPS_POS;
    config->hud_config.score_pos = HUD_SCORE_POS;
    config->hud_config.score_font_size = HUD_SCORE_FONT_SIZE;
    config->hud_config.score_color = HUD_SCORE_COLOR;

    config->snake_config.speed = SNAKE_SPEED;
    config->snake_config.speed_factor = SNAKE_SPEED_FACTOR;
    config->snake_config.init_size = SNAKE_INIT_SIZE;
    config->snake_config.max_size = SNAKE_INIT_CAP;
    config->snake_config.head_color = SNAKE_HEAD_COLOR;
    config->snake_config.cell_color = SNAKE_CELL_COLOR;

    config->food_config.color = FOOD_COLOR;
}

