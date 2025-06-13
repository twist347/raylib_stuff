#ifndef COMPONENT_PHYS_H
#define COMPONENT_PHYS_H

#include "raylib.h"

typedef struct {
    float vel;
    Vector2 dir; // normalized vector
    // acceleration, mass, is_static etc
} phys_c;

#endif //COMPONENT_PHYS_H
