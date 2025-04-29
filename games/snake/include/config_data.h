// game default settings (kind of .ini file)

#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include "raylib.h"

// screen settings
#define SCREEN_WIDTH     1920.f
#define SCREEN_HEIGHT    1080.f
#define TITLE            "Snake"
#define BG_COLOR         BLACK
#define FPS              60

// gameplay settings
#define CELL_SIZE    120.f

// snake settings
#define SNAKE_SPEED            200.f
#define SNAKE_SPEED_FACTOR     1.05f
#define SNAKE_INIT_SIZE        3
#define SNAKE_INIT_CAP         8
#define SNAKE_HEAD_COLOR       BLUE
#define SNAKE_CELL_COLOR       GREEN

// food settings
#define FOOD_COLOR     RED

// markings settings
#define MARKINGS_COLOR    GRAY

// HUD settings
#define HUD_FPS_POS            (Vector2){SCREEN_WIDTH - 100.f, 0.f}
#define HUD_SCORE_POS          (Vector2){10.f, 10.f}
#define HUD_SCORE_FONT_SIZE    40
#define HUD_SCORE_COLOR        WHITE

#endif //CONFIG_DATA_H
