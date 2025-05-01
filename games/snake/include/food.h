#ifndef FOOD_H
#define FOOD_H

#include <stdbool.h>

#include "raylib.h"

typedef enum {
    FoodShapeCircle = 0,
    FoodShapeSquare,
    FoodShapeTriangle,
    FoodShapeCount
} food_shape_e;

typedef enum {
    FoodCostCircle = 1,
    FoodCostSquare,
    FoodCostTriangle,
} food_cost_e;

typedef struct {
    Vector2 pos; // top left corner of cell
    food_shape_e shape;
    food_cost_e cost;
    Vector2 last_score_pos;
    int last_score;
    float last_score_timer;
    Color color;
} food_t;

void food_init(food_t *food, Vector2 screen_res, float cell_size, Color color);

void food_update(food_t *food);

void food_render(const food_t *food, float cell_size);

void food_spawn(food_t *food, Vector2 screen_res, float cell_size);

int food_get_cost(const food_t *food);

void food_timer_update(food_t *food, float dt);

void food_render_pop_up_score(Vector2 pos, int score, int font_size, Color color, float timer);

#endif //FOOD_H
