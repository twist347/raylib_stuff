#ifndef PLATFORM_H
#define PLATFORM_H

#include "raylib.h"

typedef struct {
    Rectangle rect;
    bool is_moving;
    bool is_fragile;
    Vector2 vel;
} platform_t;

#endif //PLATFORM_H
