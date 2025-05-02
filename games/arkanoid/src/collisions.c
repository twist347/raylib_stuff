#include "collisions.h"

#include "math.h"

#include "raymath.h"

static float get_reflection_angle(const paddle_t *paddle, Vector2 ball_center);

void collisions_handle_paddle_ball(const paddle_t *paddle, ball_t *ball) {
    if (!CheckCollisionCircleRec(ball->center_pos, ball->radius, paddle->rect)) {
        return;
    }

    const float speed = hypotf(ball->velocity.x, ball->velocity.y);
    const float angle = get_reflection_angle(paddle, ball->center_pos);

    ball->velocity.x = speed * sinf(angle);
    ball->velocity.y = -speed * cosf(angle);
}

void collisions_handle_brick_ball(const brick_t *brick, ball_t *ball) {
    // TODO: pop ball out of brick
    // closest point
    const float closest_x = fmaxf(brick->rect.x, fminf(ball->center_pos.x, brick->rect.x + brick->rect.width));
    const float closest_y = fmaxf(brick->rect.y, fminf(ball->center_pos.y, brick->rect.y + brick->rect.height));

    // vector from closest point to ball center
    const float dx = ball->center_pos.x - closest_x;
    const float dy = ball->center_pos.y - closest_y;

    // calc the side of collision
    if (fabsf(dx) > fabsf(dy)) {
        ball->velocity.x *= -1.f;
    } else {
        ball->velocity.y *= -1.f;
    }
}

static float get_reflection_angle(const paddle_t *paddle, Vector2 ball_center) {
    static const float max_reflection_angle = 75.f * DEG2RAD;
    const float paddle_center_x = paddle->rect.x + paddle->rect.width / 2.f;
    const float intersect_x = ball_center.x - paddle_center_x;
    const float norm = Clamp(intersect_x / (paddle->rect.width / 2.f), -1.f, 1.f);
    return norm * max_reflection_angle;
}
