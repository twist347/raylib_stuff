#include "screen_settings.h"

void screen_settings_init(screen_settings_t *settings, Vector2 screen_res, int fps, const char *title, Color bg_color) {
    settings->res = screen_res;
    settings->fps = fps;
    settings->title = title;
    settings->bg_color = bg_color;
}