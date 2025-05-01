#ifndef MARKINGS_H
#define MARKINGS_H

#include "raylib.h"

typedef struct {
    Color color;
} markings_t;

void markings_init(markings_t *markings, Color color);

void markings_render(const markings_t *markings, Vector2 screen_res, float cell_size);

#endif //MARKINGS_H
