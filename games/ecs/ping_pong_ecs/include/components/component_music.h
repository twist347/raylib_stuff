#ifndef COMPONENT_MUSIC_H
#define COMPONENT_MUSIC_H

#include "raylib.h"

typedef struct {
    Music *music;
    float volume;
    bool playing;
} music_slot_t;

typedef struct {
    music_slot_t slots[ASSETS_MUSIC_COUNT];
} music_c;

#endif //COMPONENT_MUSIC_H
