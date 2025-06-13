#include "systems/system_collisions.h"

#include <assert.h>
#include <math.h>

#include "raymath.h"

static void handle_ball_screen_collision(
    const ball_c *ball, transform_c *ball_trans, phys_c *ball_phys,
    Vector2 screen_res
);

static void increase_speed_by_factor(float *vel, float init_vel, float scale_factor);

static void handle_ball_paddle_collision(
    const ball_c *ball, transform_c *ball_trans, phys_c *ball_phys,
    const paddle_c *paddle, const transform_c *paddle_trans
);

static void handle_paddle_screen_collision(const paddle_c *paddle, transform_c *paddle_trans, Vector2 screen_res);

void system_collisions(world_t *world, Vector2 screen_res) {
    const entity_t ball_id = find_entity(world, COMPONENT_BALL | COMPONENT_TRANSFORM | COMPONENT_PHYS);
    assert(ball_id != MAX_ENTITIES);

    transform_c *ball_trans = get_transform_c(world, ball_id);
    phys_c *ball_phys = get_phys_c(world, ball_id);
    const ball_c *ball = get_ball_c(world, ball_id);

    handle_ball_screen_collision(ball, ball_trans, ball_phys, screen_res);

    for (entity_t id = 0; id < ball_id; id++) {
        if (has_components_group(world, id, COMPONENT_PADDLE | COMPONENT_TRANSFORM)) {
            transform_c *paddle_trans = get_transform_c(world, id);
            const paddle_c *paddle = get_paddle_c(world, id);
            handle_ball_paddle_collision(ball, ball_trans, ball_phys, paddle, paddle_trans);
            handle_paddle_screen_collision(paddle, paddle_trans, screen_res);
        }
    }
}

static void handle_ball_screen_collision(
    const ball_c *ball, transform_c *ball_trans, phys_c *ball_phys,
    Vector2 screen_res
) {
    if (ball_trans->y - ball->radius <= 0 ||
        ball_trans->y + ball->radius >= screen_res.y) {
        ball_phys->dir.y *= -1.f;

        ball_trans->y = Clamp(
            ball_trans->y,
            ball->radius,
            screen_res.y - ball->radius
        );
    }
}

static void increase_speed_by_factor(float *vel, float init_vel, float scale_factor) {
    *vel += init_vel * scale_factor;
}

static void handle_ball_paddle_collision(
    const ball_c *ball, transform_c *ball_trans, phys_c *ball_phys,
    const paddle_c *paddle, const transform_c *paddle_trans
) {
    static const float max_bounce_angle = 60.f * (DEG2RAD);

    const Rectangle paddle_rect = {paddle_trans->x, paddle_trans->y, paddle->width, paddle->height};
    const Vector2 ball_pos = {ball_trans->x, ball_trans->y};
    if (CheckCollisionCircleRec(ball_pos, ball->radius, paddle_rect)) {
        const float paddle_center = paddle_trans->y + paddle->height * 0.5f;
        const float norm_y = Clamp((ball_trans->y - paddle_center) / (paddle->height * 0.5f), -1.f, 1.f);
        const float bounce_angle = norm_y * max_bounce_angle;
        const float dir_x = (ball_phys->dir.x > 0.f) ? -1.f : 1.f;

        ball_phys->dir = (Vector2){cosf(bounce_angle) * dir_x, sinf(bounce_angle)};

        if (ball_phys->dir.x < 0) {
            ball_trans->x = paddle_trans->x - ball->radius;
        } else {
            ball_trans->x = paddle_trans->x + paddle->width + ball->radius;
        }
        increase_speed_by_factor(&ball_phys->vel, ball->init_vel, ball->vel_scale);
    }
}

static void handle_paddle_screen_collision(const paddle_c *paddle, transform_c *paddle_trans, Vector2 screen_res) {
    paddle_trans->y = Clamp(paddle_trans->y, 0, screen_res.y - paddle->height);
}
