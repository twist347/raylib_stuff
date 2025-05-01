#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

typedef enum {
    SOUND_BITE = 0,
    SOUND_CLICK_BUTTON,
    SOUNDS_LEN
} sounds_e;

void sound_init(Sound *sound, const char *path);

void sound_init_all(Sound *sounds, const char **sound_names);

void sound_destroy(Sound *sound);

void sound_destroy_all(Sound *sounds);

#endif //AUDIO_H
