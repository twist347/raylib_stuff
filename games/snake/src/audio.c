#include "audio.h"

void sound_init(Sound *sound, const char *path) {
    *sound = LoadSound(path);
}

void sound_init_all(Sound *sounds, const char **sound_names) {
    for (int i = 0; i < SOUNDS_LEN; ++i) {
        sound_init(&sounds[i], sound_names[i]);
    }
}

void sound_destroy(Sound *sound) {
    UnloadSound(*sound);
}

void sound_destroy_all(Sound *sounds) {
    for (int i = 0; i < SOUNDS_LEN; ++i) {
        sound_destroy(&sounds[i]);
    }
}

// void audio_destroy() {
//     for (int i = 0; i < SOUNDS_LEN; ++i) {
//         UnloadSound(soun)
//     }
// }