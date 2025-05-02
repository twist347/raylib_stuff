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

bool collisions_brick_ball(const brick_t *brick, ball_t *ball) {
    // nearest to ball center point on brick
    const Vector2 nearest = {
        fmax(brick->rect.x, fmin(ball->center_pos.x, brick->rect.x + brick->rect.width)),
        fmax(brick->rect.y, fmin(ball->center_pos.y, brick->rect.y + brick->rect.height))
    };

    // vector from nearest to ball center
    const Vector2 delta = {ball->center_pos.x - nearest.x, ball->center_pos.y - nearest.y};

    const float dist2 = delta.x * delta.x + delta.y * delta.y;
    if (dist2 < ball->radius * ball->radius) {
        // hor or vert collision
        if (fabs(delta.x) > fabs(delta.y)) {
            ball->velocity.x *= -1;
        } else {
            ball->velocity.y *= -1;
        }

        // slightly pop out ball (prevent sticking in brick)
        const float dist = sqrt(dist2);
        const float overlap = ball->radius - dist;
        if (dist != 0) {
            const Vector2 norm = {delta.x / dist, delta.y / dist};
            ball->center_pos.x += norm.x * overlap;
            ball->center_pos.y += norm.y * overlap;
        } else {
            ball->center_pos.y -= overlap;
        }
        return true;
    }
    return false;
}

static float get_reflection_angle(const paddle_t *paddle, Vector2 ball_center) {
    static const float max_reflection_angle = 75.f * DEG2RAD;
    const float paddle_center_x = paddle->rect.x + paddle->rect.width / 2.f;
    const float intersect_x = ball_center.x - paddle_center_x;
    const float norm = Clamp(intersect_x / (paddle->rect.width / 2.f), -1.f, 1.f);
    return norm * max_reflection_angle;
}
