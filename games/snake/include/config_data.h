// game default settings (kind of .ini file)

#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include "raylib.h"

// TODO: (maybe) add pause and game over screens settings, because there are settings for markings

// screen settings
#define SCREEN_RES    (Vector2){1920.f, 1080.f}
#define TITLE         "Snake"
#define BG_COLOR      BLACK
#define FPS           60

// pause screen settings
#define PAUSE_SCREEN_TITLES        (const char *[]){"PAUSED", "Press P to resume"}
#define PAUSE_SCREEN_FONT_SIZES    (int []){80, 50}
#define PAUSE_SCREEN_GAP           50.f
#define PAUSE_SCREEN_TEXT_COLORS   (Color []){YELLOW, WHITE}

// game over screen settings
#define GAME_OVER_SCREEN_TITLES        (const char *[]){"GAME OVER", "Final score", "Press ENTER to restart", "Press Esc to Exit"}
#define GAME_OVER_SCREEN_FONT_SIZES    (int []){80, 50, 50, 50}
#define GAME_OVER_SCREEN_GAP           50.f
#define GAME_OVER_SCREEN_TEXT_COLORS   (Color []){RED, WHITE, WHITE, WHITE}

// markings settings
#define MARKINGS_COLOR    GRAY

// game settings
#define CELL_SIZE    120.f

// HUD settings
#define HUD_FPS_POS            (Vector2){SCREEN_RES.x - 100.f, 0.f}
#define HUD_SCORE_POS          (Vector2){10.f, 10.f}
#define HUD_SCORE_FONT_SIZE    40
#define HUD_SCORE_COLOR        WHITE

// sounds settings
#define SOUNDS_PATH     ASSETS_DIR "/sounds/"
#define SOUNDS_NAMES    (const char *[]){\
                            SOUNDS_PATH "bite.wav",\
                            SOUNDS_PATH "button_click.wav"\
                        }

// snake settings
#define SNAKE_SPEED            200.f
#define SNAKE_SPEED_FACTOR     1.05f
#define SNAKE_INIT_SIZE        3
#define SNAKE_INIT_CAP         8
#define SNAKE_HEAD_COLOR       BLUE
#define SNAKE_CELL_COLOR       GREEN

// food settings
#define FOOD_COLOR     RED

#endif //CONFIG_DATA_H
