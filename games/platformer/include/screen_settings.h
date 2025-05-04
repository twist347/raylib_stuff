#ifndef SCREEN_SETTINGS_H
#define SCREEN_SETTINGS_H

#include "raylib.h"

typedef struct {
    Vector2 res;
    const char *title;
    int fps;
    Color bg_color;
} screen_settings_t;

void screen_settings_init(
    screen_settings_t *screen_settings,
    Vector2 screen_res,
    const char *title,
    int fps,
    Color bg_color
);

#endif //SCREEN_SETTINGS_H
