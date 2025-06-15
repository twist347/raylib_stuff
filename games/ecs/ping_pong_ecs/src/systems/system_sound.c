#include "systems/system_sound.h"

void system_sound(world_t *world) {
    for (entity_t id = 0; id < world->entity_count; ++id) {
        if (has_sound_c(world, id)) {
            sound_c *sound = get_sound_c(world, id);
            for (size_t i = 0; i < ASSETS_SFX_COUNT; ++i) {
                sound_slot_t *slot = &sound->slots[i];
                if (slot->playing) {
                    SetSoundVolume(*slot->sound, slot->volume);
                    PlaySound(*slot->sound);
                    slot->playing = false;
                }
            }
        }
    }
}

