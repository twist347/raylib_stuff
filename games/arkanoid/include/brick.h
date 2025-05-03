#ifndef BRICK_H
#define BRICK_H

#include <stdbool.h>

#include "raylib.h"

typedef enum {
    BRICK_TYPE_SIMPLE
} brick_type_e;

typedef struct {
    brick_type_e type;
    Rectangle rect; // (x, y) - pos of top left corner, (width, height) - sides of brick
    bool active;
    Color color;
} brick_t;

void brick_init(brick_t* brick, brick_type_e brick_type, Rectangle rect, bool active, Color color);

void brick_update(brick_t* brick);

void brick_render(const brick_t* brick);

#endif //BRICK_H
