#ifndef FOOD_H
#define FOOD_H

#include <stdbool.h>

#include "raylib.h"

typedef enum {
    FoodShapeCircle = 0,
    FoodShapeSquare,
    FoodShapeTriangle,
} food_shape_e;

typedef struct {
    bool active;
    float cell_size;
    Vector2 pos;
    food_shape_e shape;
    Color color;
} food_t;

void food_init(food_t *food, Vector2 screen_res, float cell_size, Color color);

void food_update(food_t *food);

void food_render(const food_t *food);

void food_spawn(food_t *food, Vector2 screen_res);

#endif //FOOD_H
