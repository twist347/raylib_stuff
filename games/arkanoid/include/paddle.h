#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"

typedef enum {
    PADDLE_MOVE_NONE = 0,
    PADDLE_MOVE_LEFT,
    PADDLE_MOVE_RIGHT,
} paddle_move_dir_e;

typedef struct {
    Rectangle rect; // (x, y) - pos of top left corner, (width, height) - sides of paddle
    paddle_move_dir_e move_dir;
    float velocity;
    Color color;
} paddle_t;

void paddle_init(paddle_t *paddle, Rectangle rect, float velocity, Color color);

void paddle_input(paddle_t *paddle);

void paddle_update(paddle_t *paddle, float dt);

void paddle_render(const paddle_t *paddle);

void paddle_handle_wall_collision(paddle_t *paddle, float screen_width);

#endif //PADDLE_H
