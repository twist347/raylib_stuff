#include "systems/system_music.h"

void system_music(world_t *world) {
    for (entity_t id = 0; id < world->entity_count; ++id) {
        if (has_music_c(world, id)) {
            music_c *music = get_music_c(world, id);
            for (size_t i = 0; i < ASSETS_MUSIC_COUNT; ++i) {
                music_slot_t *slot = &music->slots[i];
                if (slot->playing) {
                    if (!IsMusicStreamPlaying(*slot->music)) {
                        SetMusicVolume(*slot->music, slot->volume);
                        PlayMusicStream(*slot->music);
                    }
                    slot->playing = false;
                }
                UpdateMusicStream(*slot->music);
            }
        }
    }
}