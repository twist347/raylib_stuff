#include "snake.h"

#include <stdlib.h>

static void init_cells(snake_cell_t **cells, int len, int cap, float cell_size, Vector2 screen_res, Color cell_color);

static void snake_move(snake_t *snake, float dt);

void snake_init(
    snake_t *snake,
    int len,
    int cap,
    float cell_size,
    float speed,
    float speed_factor,
    Color head_color,
    Color cell_color,
    Vector2 screen_res
) {
    snake->len = len;
    snake->cap = cap;
    snake->cell_size = cell_size;
    init_cells(&snake->cells, len, cap, cell_size, screen_res, cell_color);
    snake->dir = SNAKE_RIGHT;
    snake->speed = speed;
    snake->speed_factor = speed_factor;
    snake->move_acc = 0.0f;
    snake->head_color = head_color;
}

void snake_destroy(snake_t *snake) {
    free(snake->cells);
}

void snake_input(snake_t *snake) {
    if (IsKeyDown(KEY_UP) && snake->dir != SNAKE_DOWN) {
        snake->dir = SNAKE_UP;
    } else if (IsKeyDown(KEY_DOWN) && snake->dir != SNAKE_UP) {
        snake->dir = SNAKE_DOWN;
    } else if (IsKeyDown(KEY_LEFT) && snake->dir != SNAKE_RIGHT) {
        snake->dir = SNAKE_LEFT;
    } else if (IsKeyDown(KEY_RIGHT) && snake->dir != SNAKE_LEFT) {
        snake->dir = SNAKE_RIGHT;
    }
}

void snake_update(snake_t *snake, float dt) {
    snake_move(snake, dt);
}

void snake_render(const snake_t *snake) {
    for (int i = 0; i < snake->len; ++i) {
        const Color color = i == 0 ? snake->head_color : snake->cells[i].color;
        const Rectangle rect = {snake->cells[i].pos.x, snake->cells[i].pos.y, snake->cell_size, snake->cell_size};
        DrawRectangleRounded(rect, 0.5f, 1, color);
    }
}

void snake_grow(snake_t *snake) {
    if (snake->len == snake->cap) {
        const int new_cap = snake->cap == 0 ? 1 : snake->cap * 2;
        snake_cell_t *tmp = realloc(snake->cells, sizeof(snake_cell_t) * new_cap);
        if (!tmp) {
            // TODO: handle realloc
        }
        snake->cells = tmp;
        snake->cap = new_cap;
    }
    snake->cells[snake->len] = snake->cells[snake->len - 1];
    ++snake->len;
}

bool snake_check_walls_collision(const snake_t *snake, Vector2 screen_res) {
    // TODO: use proper funcs to compare floats
    const float head_x = snake->cells[0].pos.x, head_y = snake->cells[0].pos.y;
    if (head_x < 0 || head_x >= screen_res.x || head_y < 0 || head_y >= screen_res.y) {
        return true;
    }
    return false;
}

bool snake_check_self_collision(const snake_t *snake) {
    // TODO: use proper funcs to compare floats
    const float head_x = snake->cells[0].pos.x, head_y = snake->cells[0].pos.y;
    for (int i = 1; i < snake->len; ++i) { // i = 1
        const float cells_i_x = snake->cells[i].pos.x, cells_i_y = snake->cells[i].pos.y;
        if (head_x == cells_i_x && head_y == cells_i_y) {
            return true;
        }
    }
    return false;
}

void snake_grow_speed(snake_t *snake) {
    snake->speed *= snake->speed_factor;
}

static void init_cells(snake_cell_t **cells, int len, int cap, float cell_size, Vector2 screen_res, Color cell_color) {
    // TODO: handle malloc
    *cells = malloc(cap * sizeof(snake_cell_t));
    const int mid_cell_x = (int) (screen_res.x / 2.0f) / cell_size;
    const int mid_cell_y = (int) (screen_res.y / 2.0f) / cell_size;
    for (int i = 0; i < len; ++i) {
        const float xi = (mid_cell_x - i) * cell_size;
        const float yi = mid_cell_y * cell_size;
        (*cells)[i] = (snake_cell_t){(Vector2){xi, yi}, cell_color};
    }
}

static void snake_move(snake_t *snake, float dt) {
    const float cell_size = snake->cell_size;
    snake->move_acc += snake->speed * dt;
    while (snake->move_acc >= cell_size) {
        // shift back
        for (int i = snake->len - 1; i > 0; --i) {
            snake->cells[i] = snake->cells[i - 1];
        }
        // new head
        snake_cell_t head = snake->cells[0];
        switch (snake->dir) {
            case SNAKE_UP:
                head.pos.y -= cell_size;
                break;
            case SNAKE_DOWN:
                head.pos.y += cell_size;
                break;
            case SNAKE_LEFT:
                head.pos.x -= cell_size;
                break;
            case SNAKE_RIGHT:
                head.pos.x += cell_size;
                break;
        }
        snake->cells[0] = head;
        snake->move_acc -= cell_size;
    }
}
