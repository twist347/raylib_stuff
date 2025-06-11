#pragma once

#include "raylib.h"

#define MAX_ENTITIES    128

#define SCREEN_RES      (Vector2){1920.f, 1080.f}
#define SCREEN_TITLE    "Ping Pong"
#define TARGET_FPS      60
#define BG_COLOR        BLACK

#define PADDLE_VEL      300.f
#define PADDLE_SIZE     (Vector2){10.f, 100.f}
#define PADDLE_COLOR    GREEN

#define BALL_VEL       (Vector2){300.f, 300.f}
#define BALL_RADIUS    10.f
#define BALL_COLOR     RED

#define HUD_COLOR    WHITE
