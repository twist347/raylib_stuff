#ifndef BALL_H
#define BALL_H

#include <stdbool.h>

#include "raylib.h"

typedef struct {
    Vector2 center_pos;
    float radius;
    Vector2 velocity;
    Color color;
} ball_t;

void ball_init(ball_t *ball, Vector2 center_pos, float radius, Vector2 velocity, Color color);

void ball_update(ball_t *ball, float dt);

void ball_render(const ball_t *ball);

void ball_handle_wall_collision(ball_t *ball, Vector2 screen_res);

bool ball_check_bottom_collision(const ball_t *ball, float height);

#endif //BALL_H
