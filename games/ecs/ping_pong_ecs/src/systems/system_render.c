#include "systems/system_render.h"

#include <stdio.h>

static void render_paddle(const paddle_c *paddle, const transform_c *paddle_trans, const render_c *paddle_render) {
    DrawRectangle(
        (int) paddle_trans->x, (int) paddle_trans->y,
        (int) paddle->width, (int) paddle->height,
        paddle_render->color
    );
}

static void render_ball(const ball_c *ball, const transform_c *ball_trans, const render_c *ball_render) {
    DrawCircle(
        (int) ball_trans->x, (int) ball_trans->y,
        ball->radius,
        ball_render->color
    );
}

static void render_score(const score_c *score, const render_c *score_render, Vector2 screen_res) {
    static char score_text[64];
    sprintf(score_text, "%d : %d", score->player1_score, score->player2_score);
    static const int font_size = 40;
    const float text_width = (float) MeasureText(score_text, font_size);
    DrawText(
        score_text,
        (int) (screen_res.x * 0.5f - text_width * 0.5f), 20,
        font_size,
        score_render->color
    );
}

void system_render(world_t *world, Vector2 screen_res) {
    static const component_mask_t paddle_m = COMPONENT_PADDLE | COMPONENT_TRANSFORM | COMPONENT_RENDER;
    static const component_mask_t ball_m = COMPONENT_BALL | COMPONENT_TRANSFORM | COMPONENT_RENDER;
    static const component_mask_t score_m = COMPONENT_SCORE | COMPONENT_RENDER;

    for (entity_t id = 0; id < MAX_ENTITIES; ++id) {
        if (has_components_group(world, id, paddle_m)) {
            render_paddle(
                get_paddle_c(world, id),
                get_transform_c(world, id),
                get_render_c(world, id)
            );
        }
    }

    for (entity_t id = 0; id < MAX_ENTITIES; ++id) {
        if (has_components_group(world, id, ball_m)) {
            render_ball(get_ball_c(world, id), get_transform_c(world, id), get_render_c(world, id));
        }
    }

    for (entity_t id = 0; id < MAX_ENTITIES; ++id) {
        if (has_components_group(world, id, score_m)) {
            render_score(get_score_c(world, id), get_render_c(world, id), screen_res);
        }
    }
}
