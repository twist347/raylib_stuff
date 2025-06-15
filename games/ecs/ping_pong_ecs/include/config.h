#pragma once

#include "raylib.h"

#define MAX_ENTITIES    256

#define SCREEN_RES      (Vector2){1920.f, 1080.f}
#define SCREEN_TITLE    "Ping Pong"
#define TARGET_FPS      60
#define BG_COLOR        BLACK

#define PADDLE_VEL      500.f
#define PADDLE_SIZE     (Vector2){20.f, 150.f}
#define PADDLE_COLOR    BLUE

#define BALL_VEL          500.f
#define BALL_RADIUS       15.f
#define BALL_VEL_SCALE    0.1f
#define BALL_COLOR        RED

#define HUD_COLOR    YELLOW
