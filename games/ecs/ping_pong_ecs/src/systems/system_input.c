#include "systems/system_input.h"

static void handle_paddle_input(input_c *paddle_input) {
    const bool is_up = IsKeyDown(paddle_input->up_key);
    const bool is_down = IsKeyDown(paddle_input->down_key);
    paddle_input->move_dir = (Vector2){0.f, 0.f};
    if (is_up && !is_down) {
        paddle_input->move_dir.y = -1.f;
    } else if (!is_up && is_down) {
        paddle_input->move_dir.y = +1.f;
    }
}

void system_input(world_t *world) {
    static const component_mask_t paddle_input_m = COMPONENT_PADDLE | COMPONENT_INPUT;
    for (entity_t id = 0; id < MAX_ENTITIES; ++id) {
        if (has_components_group(world, id, paddle_input_m)) {
            handle_paddle_input(get_input_c(world, id));
        }
    }
}