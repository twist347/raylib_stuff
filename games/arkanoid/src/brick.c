#include "brick.h"

void brick_init(brick_t* brick, Rectangle rect, bool active, Color color) {
    brick->rect = rect;
    brick->active = active;
    brick->color = color;
}

void brick_update(brick_t* brick);

void brick_render(const brick_t* brick) {
    DrawRectangleRec(brick->rect, brick->color);
}