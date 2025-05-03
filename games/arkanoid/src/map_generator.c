#include "map_generator.h"

#include <stdlib.h>

static char helper_brick_type_to_char(brick_type_e brick_type);
static int helper_char_to_brick_type(char c);

int map_generator_count_active_bricks(const char *map[], int bricks_lines, int bricks_per_line) {
    int active_bricks_count = 0;
    for (int i = 0; i < bricks_lines; ++i) {
        for (int j = 0; j < bricks_per_line; ++j) {
            if (helper_char_to_brick_type(map[i][j]) != -1) {
                ++active_bricks_count;
            }
        }
    }
    return active_bricks_count;
}

void map_generator_gen_bricks_from_map(
    brick_t *bricks,
    const char *map[],
    int bricks_lines, int bricks_per_line,
    Vector2 screen_res,
    float brick_width,
    float brick_margin,
    Color brick_color
) {
    const Vector2 brick_sides = {
        (screen_res.x - brick_margin * (bricks_per_line + 1)) / bricks_per_line,
        brick_width
    };
    int idx = 0;
    for (int i = 0; i < bricks_lines; ++i) {
        for (int j = 0; j < bricks_per_line; ++j) {
            const int brick_type = helper_char_to_brick_type(map[i][j]);
            if (brick_type == -1) {
                continue;
            }
            const Rectangle rect = {
                brick_margin + j * (brick_sides.x + brick_margin),
                brick_margin + i * (brick_sides.y + brick_margin),
                brick_sides.x - brick_margin,
                brick_sides.y - brick_margin,
            };
            brick_init(&bricks[idx], brick_type, rect, true, brick_color);
            ++idx;
        }
    }
}

void map_generator_free(brick_t *bricks) {
    free(bricks);
}

static char helper_brick_type_to_char(brick_type_e brick_type) {
    switch (brick_type) {
        case BRICK_TYPE_SIMPLE:
            return 's';
        default:
            return '.';
    }
}

static int helper_char_to_brick_type(char c) {
    switch (c) {
        case 's':
            return BRICK_TYPE_SIMPLE;
        default:
            return -1;
    }
}
