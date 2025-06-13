#include "world.h"

#include <stdlib.h>
#include <assert.h>

bool has_components_group(const world_t *world, entity_t id, component_mask_t mask) {
    assert(world);

    return (world->component_mask[id] & mask) == mask;
}

entity_t find_entity(const world_t *world, component_mask_t mask) {
    assert(world);

    for (entity_t id = 0; id < MAX_ENTITIES; ++id) {
        if (has_components_group(world, id, mask)) {
            return id;
        }
    }
    return MAX_ENTITIES;
}

void world_create(world_t *world) {
    assert(world);

    world->entity_count = 0;
    for (entity_t id = 0; id < MAX_ENTITIES; ++id) {
        world->alive[id] = false;
        world->component_mask[id] = 0u;
    }
}

void world_destroy(world_t *world) {
    assert(world);

    (void) world;
}

entity_t entity_create(world_t *world) {
    assert(world);
    assert(world->entity_count < MAX_ENTITIES);

    for (entity_t id = 0; id < MAX_ENTITIES; ++id) {
        if (!world->alive[id]) {
            world->alive[id] = true;
            world->component_mask[id] = 0u;
            ++world->entity_count;
            return id;
        }
    }
    return MAX_ENTITIES;
}

void entity_destroy(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->alive[id] = false;
    world->component_mask[id] = 0u;
    --world->entity_count;
}

// transform component

void add_transform_c(world_t *world, entity_t id, float x, float y) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] |= COMPONENT_TRANSFORM;
    world->transforms[id].x = x;
    world->transforms[id].y = y;
}

void remove_transform_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] &= ~COMPONENT_TRANSFORM;
}

bool has_transform_c(const world_t *world, entity_t id) {
    assert(world);
    assert(id < MAX_ENTITIES);

    return (world->component_mask[id] & COMPONENT_TRANSFORM) != 0u;
}

transform_c *get_transform_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    return has_transform_c(world, id) ? &world->transforms[id] : NULL;
}

// input_component

void add_input_c(world_t *world, entity_t id, int up_key, int down_key) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] |= COMPONENT_INPUT;
    world->inputs[id].up_key = up_key;
    world->inputs[id].down_key = down_key;
}

void remove_input_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] &= ~COMPONENT_INPUT;
}

bool has_input_c(const world_t *world, entity_t id) {
    assert(world);
    assert(id < MAX_ENTITIES);

    return (world->component_mask[id] & COMPONENT_INPUT) != 0;
}

input_c *get_input_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    return has_input_c(world, id) ? &world->inputs[id] : NULL;
}

// velocity component

void add_phys_c(world_t *world, entity_t id, float vel, Vector2 dir) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] |= COMPONENT_PHYS;
    world->physes[id].vel = vel;
    world->physes[id].dir = dir;
}

void remove_phys_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] &= ~COMPONENT_PHYS;
}

bool has_phys_c(const world_t *world, entity_t id) {
    assert(world);
    assert(id < MAX_ENTITIES);

    return (world->component_mask[id] & COMPONENT_PHYS) != 0u;
}

phys_c *get_phys_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    return has_phys_c(world, id) ? &world->physes[id] : NULL;
}

// render component

void add_render_c(world_t *world, entity_t id, Color color) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] |= COMPONENT_RENDER;
    world->renders[id].color = color;
}

void remove_render_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] &= ~COMPONENT_RENDER;
}

bool has_render_c(const world_t *world, entity_t id) {
    assert(world);
    assert(id < MAX_ENTITIES);

    return (world->component_mask[id] & COMPONENT_RENDER) != 0u;
}

render_c *get_render_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    return has_render_c(world, id) ? &world->renders[id] : NULL;
}

// paddle component

void add_paddle_c(world_t *world, entity_t id, float width, float height, float init_vel) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] |= COMPONENT_PADDLE;
    world->paddles[id].width = width;
    world->paddles[id].height = height;
    world->paddles[id].init_vel = init_vel;
}

void remove_paddle_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] &= ~COMPONENT_PADDLE;
}

bool has_paddle_c(const world_t *world, entity_t id) {
    assert(world);
    assert(id < MAX_ENTITIES);

    return (world->component_mask[id] & COMPONENT_PADDLE) != 0u;
}

paddle_c *get_paddle_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    return has_paddle_c(world, id) ? &world->paddles[id] : NULL;
}

// ball component

void add_ball_c(world_t *world, entity_t id, float radius, float init_vel, float vel_scale) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] |= COMPONENT_BALL;
    world->balls[id].radius = radius;
    world->balls[id].init_vel = init_vel;
    world->balls[id].vel_scale = vel_scale;
}

void remove_ball_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] &= ~COMPONENT_BALL;
}

bool has_ball_c(const world_t *world, entity_t id) {
    assert(world);
    assert(id < MAX_ENTITIES);

    return (world->component_mask[id] & COMPONENT_BALL) != 0u;
}

ball_c *get_ball_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    return has_ball_c(world, id) ? &world->balls[id] : NULL;
}

// score component

void add_score_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] |= COMPONENT_SCORE;
    world->scores[id].player1_score = 0;
    world->scores[id].player2_score = 0;
}

void remove_score_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    world->component_mask[id] &= ~COMPONENT_SCORE;
}

bool has_score_c(const world_t *world, entity_t id) {
    assert(world);
    assert(id < MAX_ENTITIES);

    return (world->component_mask[id] & COMPONENT_SCORE) != 0u;
}

score_c *get_score_c(world_t *world, entity_t id) {
    assert(world);
    assert(world->alive[id]);
    assert(id < MAX_ENTITIES);

    return has_score_c(world, id) ? &world->scores[id] : NULL;
}
