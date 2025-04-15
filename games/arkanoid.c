// TODO: check return in void handle_ball_brick_collision(GameState *game);
// TODO: check replacing Rectangle(pos, dims) with Vector2(pos) and Vector2(dims)
// TODO: rewrite using time related update instead of FPS
// TODO: rewrite TextFormat, because it recalculates in every frame

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include <raylib.h>

// screen settings
const float SCREEN_WIDTH = 1920.f;
const float SCREEN_HEIGHT = 1080.f;
const int FPS = 60;
const char *WINDOW_LABEL = "Arkanoid";
#define BG_COLOR BLACK

const int LIVES = 3;

// paddle settings
const float PADDLE_WIDTH = 250.f;
const float PADDLE_HEIGHT = 20.f;
const float PADDLE_POS_X = SCREEN_WIDTH / 2.f - PADDLE_WIDTH / 2.f;
const float PADDLE_POS_Y = SCREEN_HEIGHT - 50;
const float PADDLE_SPEED = 20.f;
#define PADDLE_COLOR WHITE

// ball settings
const float BALL_RADIUS = 15.f;
const float BALL_POS_X = PADDLE_POS_X + PADDLE_HEIGHT / 2;
const float BALL_POS_Y = PADDLE_POS_Y - BALL_RADIUS;
const float BALL_SPEED = 10.f;
#define BALL_COLOR RED

// brick settings
#define LINES_OF_BRICK 5
#define BRICKS_PER_LINE 8
const float BRICK_MARGIN = 5.f;
const float BRICK_WIDTH = SCREEN_WIDTH / BRICKS_PER_LINE;
const float BRICK_HEIGHT = 40.f;
#define BRICK_COLOR YELLOW

// text settings
const float TEXT_POS_X = 20.f;
const float TEXT_POS_Y = SCREEN_HEIGHT - 50.f;
const int TEXT_FONT_SIZE = 50;
#define TEXT_COLOR WHITE

// YOU WIN settings
const float WIN_TEXT_POS_X = SCREEN_WIDTH / 2.f - 160.f;
const float WIN_TEXT_POS_Y = SCREEN_HEIGHT / 2.f;
const char *WIN_TEXT = "YOU WIN";
const int WIN_TEXT_FONT_SIZE = 80;
#define WIN_TEXT_COLOR GREEN

// GAME OVER settings
const char *GAME_OVER_TEXT = "GAME OVER";
const float GAME_OVER_TEXT_POS_X = SCREEN_WIDTH / 2.f - 200.f;
const float GAME_OVER_TEXT_POS_Y = SCREEN_HEIGHT / 2.f;
const int GAME_OVER_TEXT_FONT_SIZE = 80;
#define GAME_OVER_TEXT_COLOR RED

// FPS text
const float FPS_TEXT_POS_X = SCREEN_WIDTH - 80.f; 
const float FPS_TEXT_POS_Y = SCREEN_HEIGHT - 20.f; 

typedef struct {
    Rectangle rect;
    float speed;
    int lives;
    Color color;
} Paddle;

typedef struct {
    Vector2 pos;
    float radius;
    Vector2 speed;
    bool launched;
    Color color;
} Ball;

typedef struct {
    Rectangle rect;
    bool active;
    Color color;
} Brick;

typedef enum {
    GAME_RUNNING,
    GAME_OVER,
    GAME_WIN
} GameStatus;

typedef struct {
    Paddle player;
    Ball ball;
    Brick bricks[LINES_OF_BRICK][BRICKS_PER_LINE];
    GameStatus status;
} GameState;

void init_game(GameState *game);

void input(GameState *game);

void handle_paddle_wall_collision(Paddle *paddle);
void handle_ball_wall_collision(GameState *game);
void handle_ball_paddle_collision(GameState *game);
void handle_ball_brick_collision(GameState *game);
void handle_ball_loss(GameState *game);
void reset_ball(GameState *game);
bool all_bricks_destroyed(GameState *game);
Vector2 get_ball_init_pos(GameState *game);

void update(GameState *game);

void draw(GameState *game);
void draw_bricks(GameState *game);

int main(void) {
    InitWindow((int) SCREEN_WIDTH, (int) SCREEN_HEIGHT, WINDOW_LABEL);
    SetTargetFPS(FPS);
    
    GameState game;
    init_game(&game);

    while (!WindowShouldClose()) {
        input(&game);
        update(&game);
        draw(&game);
    }

    CloseWindow();
}

void init_game(GameState *game) {
    Paddle paddle = {
        .rect = {PADDLE_POS_X, PADDLE_POS_Y, PADDLE_WIDTH, PADDLE_HEIGHT},
        .speed = PADDLE_SPEED,
        .lives = LIVES,
        .color = PADDLE_COLOR
    }; 

    Ball ball = {
        .pos = {BALL_POS_X, BALL_POS_Y},
        .radius = BALL_RADIUS,
        .speed = {BALL_SPEED, BALL_SPEED},
        .launched = false,
        .color = BALL_COLOR
    };

    game->player = paddle;
    game->ball = ball;

    for (size_t i = 0; i < LINES_OF_BRICK; ++i) {
        for (size_t j = 0; j < BRICKS_PER_LINE; ++j) {
            Brick *brick = &game->bricks[i][j];
            brick->rect = (Rectangle) {
                j * BRICK_WIDTH + BRICK_MARGIN,
                i * BRICK_HEIGHT + BRICK_MARGIN,
                BRICK_WIDTH - 2 * BRICK_MARGIN,
                BRICK_HEIGHT - 2 * BRICK_MARGIN
            };
            brick->active = true;
            brick->color = BRICK_COLOR;
        }
    }
    
    game->status = GAME_RUNNING;
}

void input(GameState *game) {
    if (game->status != GAME_RUNNING) {
        return;
    }

    if (IsKeyDown(KEY_LEFT)) {
        game->player.rect.x -= game->player.speed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        game->player.rect.x += game->player.speed;
    }
}

void handle_paddle_wall_collision(Paddle *paddle) {
    if (paddle->rect.x < 0) {
        paddle->rect.x = 0;
    }
    if (paddle->rect.x + paddle->rect.width > SCREEN_WIDTH) {
        paddle->rect.x = SCREEN_WIDTH - paddle->rect.width;
    }
}

void handle_ball_wall_collision(GameState *game) {
    if (game->ball.pos.x - game->ball.radius <= 0 || game->ball.pos.x + game->ball.radius >= SCREEN_WIDTH) {
        game->ball.speed.x *= -1.f;
    }

    if (game->ball.pos.y - game->ball.radius <= 0) {
        game->ball.speed.y *= -1.f;
    }
}

void handle_ball_paddle_collision(GameState *game) {
    if (game->ball.speed.y > 0 && 
        CheckCollisionCircleRec(game->ball.pos, game->ball.radius, game->player.rect)) {
        
        const float paddle_center = game->player.rect.x + game->player.rect.width / 2.0f;
        const float relative_intersect_x = game->ball.pos.x - paddle_center;
        float inter_factor = relative_intersect_x / (game->player.rect.width / 2.0f);
        
        static const float max_normalized = 0.8f;
        if (inter_factor > max_normalized) { 
            inter_factor = max_normalized;
        }
        if (inter_factor < -max_normalized) {
            inter_factor = -max_normalized;
        }

        game->ball.speed.x = inter_factor * BALL_SPEED;
        const float new_speed_y = sqrtf(BALL_SPEED * BALL_SPEED - game->ball.speed.x * game->ball.speed.x);
        game->ball.speed.y = -new_speed_y; 
        
        // prevent stuck in paddle
        game->ball.pos.y = game->player.rect.y - game->ball.radius;
    }
    /*
    if (CheckCollisionCircleRec(game->ball.pos, game->ball.radius, game->player.rect)) {
        game->ball.speed.y *= -1.f; 
        game->ball.pos.y -= game->ball.radius;
    }
    */
}

void handle_ball_brick_collision(GameState *game) {
    for (size_t i = 0; i < LINES_OF_BRICK; ++i) {
        for (size_t j = 0; j < BRICKS_PER_LINE; ++j) {
            Brick *brick = &game->bricks[i][j];
            if (!brick->active) {
                continue;
            }

            if (CheckCollisionCircleRec(game->ball.pos, game->ball.radius, brick->rect)) {
                brick->active = false;
                game->ball.speed.y *= -1.f;
                // return; 
            }
        }
    }
}

void handle_ball_loss(GameState *game) {
    if (game->ball.pos.y + game->ball.radius > SCREEN_HEIGHT) {
        --game->player.lives;

        if (game->player.lives == 0) {
            game->status = GAME_OVER;
        }
        reset_ball(game);
    }
}

void reset_ball(GameState *game) {
    game->ball.launched = false;
    
    game->ball.pos = get_ball_init_pos(game);
    
    const float angle_rad = (45.f + (float) GetRandomValue(0, 90)) * (PI / 180.f); 

    game->ball.speed = (Vector2) {BALL_SPEED * cosf(angle_rad), BALL_SPEED * sinf(angle_rad)};
}

bool all_bricks_destroyed(GameState *game) {
    for (size_t i = 0; i < LINES_OF_BRICK; ++i) {
        for (size_t j = 0; j < BRICKS_PER_LINE; ++j) {
            if (game->bricks[i][j].active) {
                return false;
            }
        }
    }
    return true;
}

void update(GameState *game) {
    if (game->status != GAME_RUNNING) {
        return;
    }
    
    handle_paddle_wall_collision(&game->player); 
    
    if (!game->ball.launched) {
        game->ball.pos = get_ball_init_pos(game);
        if (IsKeyPressed(KEY_SPACE)) {
            const float angle_rad = (45.f + (float) GetRandomValue(0, 90)) * (PI / 180.f);
            game->ball.speed = (Vector2){BALL_SPEED * cosf(angle_rad), -BALL_SPEED * sinf(angle_rad)};
            game->ball.launched = true;
        }        
    } else {
        game->ball.pos.x += game->ball.speed.x;
        game->ball.pos.y += game->ball.speed.y;

        handle_ball_wall_collision(game);
        handle_ball_paddle_collision(game);
        handle_ball_brick_collision(game);
        
        handle_ball_loss(game);
        
        if (all_bricks_destroyed(game)) {
            game->status = GAME_WIN;
        }
    }
}

Vector2 get_ball_init_pos(GameState *game) {
    return (Vector2) {
        .x = game->player.rect.x + game->player.rect.width / 2.f,
        .y = game->player.rect.y - game->ball.radius
    };
}

void draw(GameState *game) {
    BeginDrawing();
    
    ClearBackground(BG_COLOR);
    
    DrawFPS(FPS_TEXT_POS_X, FPS_TEXT_POS_Y);

    DrawRectangleRec(game->player.rect, game->player.color);

    DrawCircleV(game->ball.pos, game->ball.radius, game->ball.color);

    draw_bricks(game);

    DrawText(TextFormat("%d", game->player.lives), TEXT_POS_X, TEXT_POS_Y, TEXT_FONT_SIZE, TEXT_COLOR);
    
    if (game->status == GAME_OVER) {
        DrawText(GAME_OVER_TEXT, GAME_OVER_TEXT_POS_X, GAME_OVER_TEXT_POS_Y, GAME_OVER_TEXT_FONT_SIZE, GAME_OVER_TEXT_COLOR);
    } else if (game->status == GAME_WIN) {
        DrawText(WIN_TEXT, WIN_TEXT_POS_X, WIN_TEXT_POS_Y, WIN_TEXT_FONT_SIZE, WIN_TEXT_COLOR);
    }

    EndDrawing();
}

void draw_bricks(GameState *game) {
    for (size_t i = 0; i < LINES_OF_BRICK; ++i) {
        for (size_t j = 0; j < BRICKS_PER_LINE; ++j) {
            Brick *brick = &game->bricks[i][j];
            if (brick->active) {
                DrawRectangleRec(brick->rect, brick->color);
            }
        }
    }
}

