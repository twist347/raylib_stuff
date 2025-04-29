#include "food.h"

void food_init(food_t *food, Vector2 screen_res, float cell_size, Color color) {
    food->active = true;
    food->cell_size = cell_size;
    food_spawn(food, screen_res);
    food->color = color;
}

void food_update(food_t *food) {
    // TODO:
    (void)food;
}

void food_render(const food_t *food) {
    const float x = food->pos.x, y = food->pos.y;
    const float cell_size = food->cell_size;
    switch (food->shape) {
        case FoodShapeCircle:
            DrawCircle(x + cell_size / 2.f, y + cell_size / 2.f, cell_size / 2.f, food->color);
            break;
        case FoodShapeSquare:
            DrawRectangle(x, y, cell_size, cell_size, food->color);
            break;
        case FoodShapeTriangle: { // for -pedatinc
            const Vector2 v1 = {x + cell_size / 2.f, y};
            const Vector2 v2 = {x, y + cell_size};
            const Vector2 v3 = {x + cell_size, y + cell_size};
            DrawTriangle(v1, v2, v3, food->color);
            break;
        }
    }
}

void food_spawn(food_t *food, Vector2 screen_res) {
    const float cell_size = food->cell_size;
    const int cols = screen_res.x / cell_size;
    const int rows = screen_res.y / cell_size;
    food->pos = (Vector2) {
        .x = GetRandomValue(1, cols - 1) * cell_size,
        .y = GetRandomValue(1, rows - 1) * cell_size
    };
    food->shape = GetRandomValue(0, 2);
}