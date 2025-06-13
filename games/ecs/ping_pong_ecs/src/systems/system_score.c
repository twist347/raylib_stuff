#include "systems/system_score.h"

#include <assert.h>
#include <stdlib.h>
#include <math.h>

static void reset_ball(
    const ball_c *ball, transform_c *ball_transform, phys_c *ball_phys,
    Vector2 screen_res,
    bool is_left
);

void system_score(world_t *world, Vector2 screen_res) {
    const entity_t ball_id = find_entity(world, COMPONENT_BALL | COMPONENT_TRANSFORM | COMPONENT_PHYS);
    assert(ball_id != MAX_ENTITIES);

    const entity_t score_id = find_entity(world, COMPONENT_SCORE);

    const ball_c *ball = get_ball_c(world, ball_id);
    transform_c *ball_trans = get_transform_c(world, ball_id);
    phys_c *ball_phys = get_phys_c(world, ball_id);

    if (ball_trans->x - ball->radius <= 0) {
        ++get_score_c(world, score_id)->player2_score;
        reset_ball(ball, ball_trans, ball_phys, screen_res, true);
    }
    if (ball_trans->x + ball->radius >= screen_res.x) {
        ++get_score_c(world, score_id)->player1_score;
        reset_ball(ball, ball_trans, ball_phys, screen_res, false);
    }
}

static void reset_ball(
    const ball_c *ball, transform_c *ball_transform, phys_c *ball_phys,
    Vector2 screen_res,
    bool is_left
) {
    static const float max_angle = 45.0f;

    ball_transform->x = screen_res.x * 0.5f;
    ball_transform->y = screen_res.y * 0.5f;

    ball_phys->vel = ball->init_vel;

    const float t = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
    const float angle = t * (max_angle * (float)M_PI / 180.0f);
    const float base = is_left ? (float)M_PI : 0.0f;  // 0 = вправо, π = влево
    const float final_angle = base + angle;
    ball_phys->dir.x = cosf(final_angle);
    ball_phys->dir.y = sinf(final_angle);
}