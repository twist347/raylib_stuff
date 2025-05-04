#include "screen_settings.h"

void screen_settings_init(
    screen_settings_t *screen_settings,
    Vector2 screen_res,
    const char *title,
    int fps,
    Color bg_color
) {
    screen_settings->res = screen_res;
    screen_settings->title = title;
    screen_settings->fps = fps;
    screen_settings->bg_color = bg_color;
}