#pragma once

#include "raylib.h"

#define MAX_ENTITIES    256

#define SCREEN_RES      (Vector2){1920.f, 1080.f}
#define SCREEN_TITLE    "TDS"
#define TARGET_FPS      60
#define BG_COLOR        BLACK

#define PLAYER_SIZE     50.f
#define PLAYER_VEL      300.f
#define PLAYER_COLOR    WHITE

#define ENEMY_SIZE    50.f
#define ENEMY_VEL     300.f
#define ENEMY_COLOR   PURPLE

#define PROJECTILE_COLOR     RED
#define PROJECTILE_VEL       800.f
#define PROJECTILE_RADIUS    30.f

#define HUD_COLOR    YELLOW