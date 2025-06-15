#ifndef COMPONENT_SOUND_H
#define COMPONENT_SOUND_H

#include "raylib.h"

#include "assets.h"

typedef struct {
    Sound *sound;
    float volume; // 0..1
    bool playing;
} sound_slot_t;

// for arr for add func
typedef struct {
    assets_sound_id_e id;
    float volume;
} sound_info_t;

typedef struct {
    sound_slot_t slots[ASSETS_SFX_COUNT];
} sound_c;

#endif //COMPONENT_SOUND_H
