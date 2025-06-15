#ifndef COMPONENT_COLLIDER_H
#define COMPONENT_COLLIDER_H

#include "raylib.h"

// unused

typedef enum {
    COLLIDER_TYPE_RECT,
    COLLIDER_TYPE_CIRCLE,
} collider_type_e;

typedef struct {
    collider_type_e type;

    union {
        Rectangle rect;
        float radius;
    } shape;

} collider_c;

#endif //COMPONENT_COLLIDER_H
