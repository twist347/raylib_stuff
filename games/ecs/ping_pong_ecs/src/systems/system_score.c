#include "systems/system_score.h"

#include <assert.h>

/*
TODO: rewrite using signal. when player scores he emit signal to transform(?) system to reset position of ball
*/

static void reset_ball(
    const ball_c *ball, transform_c *ball_transform, phys_c *ball_phys,
    Vector2 screen_res,
    bool is_left
) {
    ball_transform->x = screen_res.x * 0.5f;
    ball_transform->y = screen_res.y * 0.5f;
    ball_phys->vel.x = is_left ? -ball->init_speed : ball->init_speed;
}

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