#ifndef COMPONENT_INPUT_H
#define COMPONENT_INPUT_H

#include "raylib.h"

typedef struct {
    Vector2 move_dir; // (-1..1, -1..1)
    int up_key;
    int down_key;
    // and/or move direction
} input_c;

#endif //COMPONENT_INPUT_H
