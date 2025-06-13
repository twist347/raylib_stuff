#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>

#include "config.h"
#include "components/component_all.h"

typedef unsigned int entity_t;
typedef unsigned int component_mask_t;

// 32 components max
#define COMPONENT_TRANSFORM    (1u << 0)
#define COMPONENT_INPUT        (1u << 1)
#define COMPONENT_PHYS         (1u << 2)
#define COMPONENT_RENDER       (1u << 3)
#define COMPONENT_PADDLE       (1u << 4)
#define COMPONENT_BALL         (1u << 5)
#define COMPONENT_SCORE        (1u << 6)

typedef struct {
    bool alive[MAX_ENTITIES];
    unsigned int entity_count;
    component_mask_t component_mask[MAX_ENTITIES];

    transform_c transforms[MAX_ENTITIES];
    input_c inputs[MAX_ENTITIES];
    phys_c physes[MAX_ENTITIES];
    render_c renders[MAX_ENTITIES];
    paddle_c paddles[MAX_ENTITIES];
    ball_c balls[MAX_ENTITIES];
    score_c scores[MAX_ENTITIES];
} world_t;

// helper funcs
bool has_components_group(const world_t *world, entity_t id, component_mask_t mask);
entity_t find_entity(const world_t *world, component_mask_t mask);

// world funcs
void world_create(world_t *world);
void world_destroy(world_t *world);

// entity funcs
entity_t entity_create(world_t *world);
void entity_destroy(world_t *world, entity_t id);

// transform funcs
void add_transform_c(world_t *world, entity_t id, float x, float y);
void remove_transform_c(world_t *world, entity_t id);
bool has_transform_c(const world_t *world, entity_t id);
transform_c *get_transform_c(world_t *world, entity_t id);

// input funcs
void add_input_c(world_t *world, entity_t id, int up_key, int down_key);
void remove_input_c(world_t *world, entity_t id);
bool has_input_c(const world_t *world, entity_t id);
input_c *get_input_c(world_t *world, entity_t id);

// render funcs
void add_render_c(world_t *world, entity_t id, Color color);
void remove_render_c(world_t *world, entity_t id);
bool has_render_c(const world_t *world, entity_t id);
render_c *get_render_c(world_t *world, entity_t id);

// phys funcs
void add_phys_c(world_t *world, entity_t id, float vel, Vector2 dir);
void remove_phys_c(world_t *world, entity_t id);
bool has_phys_c(const world_t *world, entity_t id);
phys_c *get_phys_c(world_t *world, entity_t id);

// paddle funcs
void add_paddle_c(world_t *world, entity_t id, float width, float height, float init_vel);
void remove_paddle_c(world_t *world, entity_t id);
bool has_paddle_c(const world_t *world, entity_t id);
paddle_c *get_paddle_c(world_t *world, entity_t id);

// ball funcs
void add_ball_c(world_t *world, entity_t id, float radius, float init_vel, float vel_scale);
void remove_ball_c(world_t *world, entity_t id);
bool has_ball_c(const world_t *world, entity_t id);
ball_c *get_ball_c(world_t *world, entity_t id);

// score funcs
void add_score_c(world_t *world, entity_t id);
void remove_score_c(world_t *world, entity_t id);
bool has_score_c(const world_t *world, entity_t id);
score_c *get_score_c(world_t *world, entity_t id);

#endif //WORLD_H
