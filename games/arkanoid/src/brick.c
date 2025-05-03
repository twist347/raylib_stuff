#include "brick.h"

void brick_init(brick_t *brick, brick_type_e brick_type, Rectangle rect, bool active, Color color) {
    brick->type = brick_type;
    brick->rect = rect;
    brick->active = active;
    brick->color = color;
}

void brick_update(brick_t *brick) {
    (void) brick;
}

void brick_render(const brick_t *brick) {
    DrawRectangleRec(brick->rect, brick->color);
}
