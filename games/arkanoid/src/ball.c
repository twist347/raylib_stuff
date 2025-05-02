#include "ball.h"

#include "raylib.h"

void ball_init(ball_t *ball, Vector2 center_pos, float radius, Vector2 velocity, Color color) {
    ball->center_pos = center_pos;
    ball->radius = radius;
    ball->velocity = velocity;
    ball->color = color;
}

void ball_update(ball_t *ball, float dt) {
    ball->center_pos.x += ball->velocity.x * dt;
    ball->center_pos.y += ball->velocity.y * dt;
}

void ball_render(const ball_t *ball) {
    DrawCircleV(ball->center_pos, ball->radius, ball->color);
}

void ball_handle_wall_collision(ball_t *ball, Vector2 screen_res) {
    // left and right walls
    if (CheckCollisionCircleLine(
            ball->center_pos, ball->radius,
            (Vector2){0, 0}, (Vector2){0, screen_res.y}
        ) ||
        CheckCollisionCircleLine(
            ball->center_pos, ball->radius,
            (Vector2){screen_res.x, 0}, (Vector2){screen_res.x, screen_res.y}
        )
    ) {
        ball->velocity.x *= -1.f;
    }

    // top wall
    if (CheckCollisionCircleLine(
            ball->center_pos, ball->radius,
            (Vector2){0, 0}, (Vector2){screen_res.x, 0}
        )
    ) {
        ball->velocity.y *= -1.f;
    }
}

bool ball_check_bottom_collision(const ball_t *ball, float height) {
    return ball->center_pos.y + ball->radius > height;
}
