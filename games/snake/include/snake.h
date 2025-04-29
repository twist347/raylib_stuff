#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "raylib.h"

typedef enum {
    SNAKE_UP = 0,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT,
} snake_direction_e;

typedef struct {
    Vector2 pos; // top left corner of the cell
    Color color;
} snake_cell_t;

typedef struct {
    int len;
    int cap;
    float cell_size;
    snake_cell_t *cells;
    snake_direction_e dir;
    float speed;
    float speed_factor;
    float move_acc;
    Color head_color;
} snake_t;

void snake_init(
    snake_t *snake,
    int len,
    int cap,
    float cell_size,
    float speed,
    float speed_factor,
    Color head_color,
    Color cell_color,
    Vector2 screen_res
);

void snake_destroy(snake_t *snake);

void snake_update(snake_t *snake, float dt);

void snake_render(const snake_t *snake);

void snake_grow(snake_t *snake);

bool snake_check_walls_collision(const snake_t *snake, Vector2 screen_res);

bool snake_check_self_collision(const snake_t *snake);

void snake_grow_speed(snake_t *snake);

#endif //SNAKE_H
