#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include "raylib.h"

// screen settings
#define SCREEN_RES      (Vector2){1920.f, 1080.f}
#define SCREEN_TITLE    "Platformer"
#define FPS             60
#define BG_COLOR        BLACK

// physics settings
#define GRAVITY    1000.f

// player settings
#define PLAYER_WIDTH         40.f
#define PLAYER_HEIGHT        200.f
#define PLAYER_JUMP_FORCE    800.f
#define PLAYER_VEL           (Vector2){200.f, 200.f}
#define PLAYER_COLOR         BLUE

#endif //CONFIG_DATA_H
