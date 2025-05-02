#include "paddle.h"

#include <stdbool.h>

void paddle_init(paddle_t *paddle, Rectangle rect, float velocity, Color color) {
    paddle->rect = rect;
    paddle->move_dir = PADDLE_MOVE_NONE;
    paddle->velocity = velocity;
    paddle->color = color;
}

void paddle_input(paddle_t *paddle) {
    const bool left = IsKeyDown(KEY_LEFT);
    const bool right = IsKeyDown(KEY_RIGHT);

    if (left && right) {
        paddle->move_dir = PADDLE_MOVE_NONE;
    } else if (left) {
        paddle->move_dir = PADDLE_MOVE_LEFT;
    } else if (right) {
        paddle->move_dir = PADDLE_MOVE_RIGHT;
    } else {
        paddle->move_dir = PADDLE_MOVE_NONE;
    }
}

void paddle_update(paddle_t *paddle, float dt) {
    switch (paddle->move_dir) {
        case PADDLE_MOVE_LEFT:
            paddle->rect.x -= paddle->velocity * dt;
            break;
        case PADDLE_MOVE_RIGHT:
            paddle->rect.x += paddle->velocity * dt;
            break;
        case PADDLE_MOVE_NONE:
            break;
    }
}

void paddle_render(const paddle_t *paddle) {
    DrawRectangleRounded(paddle->rect, 1.f, 1, paddle->color);
}

void paddle_handle_wall_collision(paddle_t *paddle, float screen_width) {
    if (paddle->rect.x < 0.f) {
        paddle->rect.x = 0.f;
    }
    if (paddle->rect.x + paddle->rect.width > screen_width) {
        paddle->rect.x = screen_width - paddle->rect.width;
    }
}
