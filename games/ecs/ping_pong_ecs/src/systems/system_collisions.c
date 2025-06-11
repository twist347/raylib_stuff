#include "systems/system_collisions.h"

#include <assert.h>

#include "raymath.h"

static void handle_ball_screen_collisions(
    const ball_c *ball, transform_c *ball_trans, phys_c *ball_phys,
    Vector2 screen_res
) {
    if (ball_trans->y - ball->radius <= 0 || ball_trans->y + ball->radius > screen_res.y) {
        ball_phys->vel.y *= -1.f;
        ball_trans->y = Clamp(ball_trans->y, ball->radius, screen_res.y - ball->radius);
    }
}

static void handle_ball_paddle_collisions(
    const ball_c *ball, transform_c *ball_trans, phys_c *ball_phys,
    const transform_c *paddle_trans, const paddle_c *paddle
) {
    const Rectangle paddle_rect = {
        paddle_trans->x,
        paddle_trans->y,
        paddle->width,
        paddle->height
    };
    if (CheckCollisionCircleRec((Vector2){ball_trans->x, ball_trans->y}, ball->radius, paddle_rect)) {
        ball_phys->vel.x *= -1.f;
        if (ball_phys->vel.x > 0) {
            ball_trans->x = paddle_trans->x + paddle->width + ball->radius;
        } else {
            ball_trans->x = paddle_trans->x - ball->radius;
        }
    }
}

static void handle_paddle_screen_collisions(const paddle_c *paddle, transform_c *paddle_trans, Vector2 screen_res) {
    paddle_trans->y = Clamp(paddle_trans->y, 0, screen_res.y - paddle->height);
}

void system_collisions(world_t *world, Vector2 screen_res) {
    const entity_t ball_id = find_entity(world, COMPONENT_BALL | COMPONENT_TRANSFORM | COMPONENT_PHYS);
    assert(ball_id != MAX_ENTITIES);

    transform_c *ball_trans = get_transform_c(world, ball_id);
    phys_c *ball_phys = get_phys_c(world, ball_id);
    const ball_c *ball = get_ball_c(world, ball_id);

    handle_ball_screen_collisions(ball, ball_trans, ball_phys, screen_res);

    for (entity_t id = 0; id < ball_id; id++) {
        if (has_components_group(world, id, COMPONENT_PADDLE | COMPONENT_TRANSFORM)) {
            transform_c *paddle_trans = get_transform_c(world, id);
            const paddle_c *paddle = get_paddle_c(world, id);
            handle_ball_paddle_collisions(ball, ball_trans, ball_phys, paddle_trans, paddle);
            handle_paddle_screen_collisions(paddle, paddle_trans, screen_res);
        }
    }
}
