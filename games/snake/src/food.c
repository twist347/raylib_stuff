#include "food.h"

#include "math.h"

void food_init(food_t *food, Vector2 screen_res, float cell_size, Color color) {
    food_spawn(food, screen_res, cell_size);
    food->last_score_pos = (Vector2){0};
    food->last_score = 0;
    food->last_score_timer = 0.f;
    food->color = color;
}

void food_update(food_t *food) {
    // TODO:
    (void) food;
}

void food_render(const food_t *food, float cell_size) {
    const float x = food->pos.x, y = food->pos.y;
    switch (food->shape) {
        case FoodShapeCircle:
            DrawCircle(x + cell_size / 2.f, y + cell_size / 2.f, cell_size / 2.f, food->color);
            break;
        case FoodShapeSquare:
            DrawRectangle(x, y, cell_size, cell_size, food->color);
            break;
        case FoodShapeTriangle: { // block for -pedatinc
            const Vector2 v1 = {x + cell_size / 2.f, y};
            const Vector2 v2 = {x, y + cell_size};
            const Vector2 v3 = {x + cell_size, y + cell_size};
            DrawTriangle(v1, v2, v3, food->color);
            break;
        }
        default:
            break;
    }
}

void food_spawn(food_t *food, Vector2 screen_res, float cell_size) {
    const int cols = screen_res.x / cell_size;
    const int rows = screen_res.y / cell_size;
    food->pos = (Vector2){
        .x = GetRandomValue(1, cols - 1) * cell_size,
        .y = GetRandomValue(1, rows - 1) * cell_size
    };
    food->shape = GetRandomValue(0, FoodShapeCount - 1);
    food->cost = food_get_cost(food);
}

int food_get_cost(const food_t *food) {
    switch (food->shape) {
        case FoodShapeCircle:
            return FoodCostCircle;
        case FoodShapeSquare:
            return FoodCostSquare;
        case FoodShapeTriangle:
            return FoodCostTriangle;
        default:
            return 0;
    }
}

void food_timer_update(food_t *food, float dt) {
    food->last_score_timer = fmaxf(0.0f, food->last_score_timer - dt);
}

void food_render_pop_up_score(Vector2 pos, int score, int font_size, Color color, float timer) {
    if (timer > 0.0f) {
        const char *text = TextFormat("+%d", score);
        const int text_width = MeasureText(text, font_size);
        DrawText(text, pos.x + text_width, pos.y - font_size - 5, font_size, color);
    }
}
