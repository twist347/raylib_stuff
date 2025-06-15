#include "systems/system_transform.h"

static void handle_paddle_transform(
    transform_c *paddle_trans,
    const phys_c *paddle_phys,
    float dt
);

static void handle_ball_transform(transform_c *ball_trans, const phys_c *ball_phys, float dt);

void system_transform(world_t *world, float dt) {
    static const component_mask_t ball_m = COMPONENT_BALL | COMPONENT_TRANSFORM;
    static const component_mask_t paddle_m = COMPONENT_PADDLE | COMPONENT_INPUT | COMPONENT_PHYS;

    for (entity_t id = 0; id < world->entity_count; ++id) {
        if (has_components_group(world, id, paddle_m)) {
            handle_paddle_transform(
                get_transform_c(world, id),
                get_phys_c(world, id),
                dt
            );
        }
    }

    for (entity_t id = 0; id < world->entity_count; ++id) {
        if (has_components_group(world, id, ball_m)) {
            handle_ball_transform(
                get_transform_c(world, id),
                get_phys_c(world, id),
                dt
            );
        }
    }
}

static void handle_paddle_transform(
    transform_c *paddle_trans,
    const phys_c *paddle_phys,
    float dt
) {
    paddle_trans->x += paddle_phys->vel * paddle_phys->dir.x * dt;
    paddle_trans->y += paddle_phys->vel * paddle_phys->dir.y * dt;
}

static void handle_ball_transform(transform_c *ball_trans, const phys_c *ball_phys, float dt) {
    ball_trans->x += ball_phys->vel * ball_phys->dir.x * dt;
    ball_trans->y += ball_phys->vel * ball_phys->dir.y * dt;
}
