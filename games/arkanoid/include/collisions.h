#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "ball.h"
#include "brick.h"
#include "paddle.h"

void collisions_handle_paddle_ball(const paddle_t *paddle, ball_t *ball);

bool collisions_brick_ball(const brick_t *brick, ball_t *ball);

#endif //COLLISIONS_H
