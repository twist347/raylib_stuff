#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "snake.h"
#include "food.h"

bool collisions_check_snake_cell_food(const snake_cell_t *cell, float cell_size, const food_t *food);

#endif //COLLISIONS_H
