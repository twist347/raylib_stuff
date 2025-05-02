#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include "raylib.h"

// screen settings
#define SCREEN_RES      (Vector2){1920.f, 1080.f}
#define SCREEN_TITLE    "Arkanoid"
#define FPS             60
#define BG_COLOR        BLACK

// paddle settings
#define PADDLE_SIDES       (Vector2){250.f, 30.f}
#define PADDLE_INIT_POS    (Vector2){(SCREEN_RES.x - PADDLE_SIDES.x) / 2.f, SCREEN_RES.y - 80.f}
#define PADDLE_VELOCITY    600.f
#define PADDLE_COLOR       WHITE

// ball settings
#define BALL_RADIUS      20.f
#define BALL_INIT_POS    (Vector2){PADDLE_INIT_POS.x + PADDLE_SIDES.x / 2.f, PADDLE_INIT_POS.y - BALL_RADIUS * 2}
#define BALL_VELOCITY    (Vector2){500.f, 500.f}
#define BALL_COLOR       RED

// brick settings
#define BRICK_MARGIN       5.f
#define BRICKS_LINES       5
#define BRICKS_PER_LINE    8
// #define BRICK_SIDES        (Vector2){SCREEN_RES.x / BRICKS_PER_LINE, 40.f}
#define BRICK_COLOR        YELLOW

#endif //CONFIG_DATA_H
