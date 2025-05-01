#include "collisions.h"

#include "raylib.h"

bool collisions_check_snake_cell_food(const snake_cell_t *cell, float cell_size, const food_t *food) {
    return CheckCollisionPointRec(
        (Vector2){cell->pos.x + cell_size / 2.f, cell->pos.y + cell_size / 2.f},
        (Rectangle){food->pos.x, food->pos.y, cell_size, cell_size}
    );
}