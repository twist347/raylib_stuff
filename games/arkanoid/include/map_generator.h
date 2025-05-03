#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include "brick.h"

int map_generator_count_active_bricks(const char *map[], int bricks_lines, int bricks_per_line);

void map_generator_gen_bricks_from_map(
    brick_t *bricks,
    const char *map[],
    int bricks_lines, int bricks_per_line,
    Vector2 screen_res,
    float brick_width,
    float brick_margin,
    Color brick_color
);

void map_generator_free(brick_t *bricks);

#endif //MAP_GENERATOR_H
