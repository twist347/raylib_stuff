#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"

typedef enum {
    ASSETS_SFX_BOUNCE = 0,
    ASSETS_SFX_WALL_HIT,
    ASSETS_SFX_COUNT
} assets_sound_id_e;

typedef enum {
    ASSETS_MUSIC_BG = 0,
    ASSETS_MUSIC_COUNT
} assets_music_id_e;

typedef struct {
    Sound sfx[ASSETS_SFX_COUNT];
    Music music[ASSETS_MUSIC_COUNT];
} assets_t;

#endif //ASSETS_H
