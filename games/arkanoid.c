// TODO: check return in void handle_ball_brick_collision(GameState *game);
// TODO: check replacing Rectangle(pos, dims) with Vector2(pos) and Vector2(dims)
// TODO: rewrite using time related update instead of FPS

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

// paddle settings
const float PADDLE_SPEED = 20.f;
const float PADDLE_WIDTH = 250.f;
const float PADDLE_HEIGHT = 20.f;
#define PADDLE_COLOR WHITE

// ball settings
const float BALL_SIZE = 30.f;
const float BALL_SPEED = 10.f;
const float BALL_POS_X = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
const float BALL_POS_Y = SCREEN_HEIGHT - 500;
#define BALL_COLOR RED

// brick settings
#define LINES_OF_BRICK 5
#define BRICKS_PER_LINE 25
const float BRICK_MARGIN = 5.f;
const float BRICK_WIDTH = SCREEN_WIDTH / BRICKS_PER_LINE;
const float BRICK_HEIGHT = 40.f;
#define BRICK_COLOR YELLOW

// text settings
const float TEXT_POS_X = 20;
const float TEXT_POS_Y = SCREEN_HEIGHT - 50;
const int TEXT_FONT_SIZE = 50;
#define TEXT_COLOR WHITE

// FPS text
const float FPS_TEXT_POS_X = SCREEN_WIDTH - 80; 
const float FPS_TEXT_POS_Y = SCREEN_HEIGHT - 20; 

typedef struct {
    Rectangle rect;
    float speed;
    int lives;
    Color color;
} Paddle;

typedef struct {
    Rectangle rect;
    Vector2 speed;
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

void update(GameState *game);

void draw(GameState *game);
void draw_bricks(GameState *game);

int main() {
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
        .rect = {SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, SCREEN_HEIGHT - 50, PADDLE_WIDTH, PADDLE_HEIGHT},
        .speed = PADDLE_SPEED,
        .lives = 3,
        .color = PADDLE_COLOR
    }; 

    Ball ball = {
        .rect = {BALL_POS_X, BALL_POS_Y, BALL_SIZE, BALL_SIZE},
        .speed = {BALL_SPEED, BALL_SPEED},
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
                BRICK_HEIGHT - BRICK_MARGIN
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

void update(GameState *game) {
    if (game->status != GAME_RUNNING) {
        return;
    }

    handle_paddle_wall_collision(&game->player); 
    handle_ball_wall_collision(game);
    handle_ball_paddle_collision(game);
    handle_ball_brick_collision(game);
    
    game->ball.rect.x += game->ball.speed.x;
    game->ball.rect.y += game->ball.speed.y;
    
    handle_ball_loss(game);
    if (all_bricks_destroyed(game)) {
        game->status = GAME_WIN;
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
    if (game->ball.rect.x <= 0 || game->ball.rect.x + game->ball.rect.width >= SCREEN_WIDTH) {
        game->ball.speed.x = -game->ball.speed.x;
    }

    if (game->ball.rect.y <= 0) {
        game->ball.speed.y = -game->ball.speed.y;
    }
}

void handle_ball_paddle_collision(GameState *game) {
    const Vector2 ball_center = {
        game->ball.rect.x + BALL_SIZE / 2,
        game->ball.rect.y + BALL_SIZE / 2
    };

    if (CheckCollisionCircleRec(ball_center, BALL_SIZE / 2, game->player.rect)) {
        game->ball.speed.y = -game->ball.speed.y; 
        game->ball.rect.y -= game->ball.rect.height;
    }
}

void handle_ball_brick_collision(GameState *game) {
    for (size_t i = 0; i < LINES_OF_BRICK; ++i) {
        for (size_t j = 0; j < BRICKS_PER_LINE; ++j) {
            Brick *brick = &game->bricks[i][j];
            if (!brick->active) {
                continue;
            }

            if (CheckCollisionCircleRec(
                (Vector2) {
                    game->ball.rect.x + BALL_SIZE / 2,
                    game->ball.rect.y + BALL_SIZE / 2
                },
                BALL_SIZE / 2,
                brick->rect
            )) {
                brick->active = false;
                game->ball.speed.y = -game->ball.speed.y;
                return; 
            }
        }
    }
}

void handle_ball_loss(GameState *game) {
    if (game->ball.rect.y > SCREEN_HEIGHT) {
        --game->player.lives;

        if (game->player.lives == 0) {
            game->status = GAME_OVER;
        }
        reset_ball(game);
    }
}

void reset_ball(GameState *game) {
    game->ball.rect.x = BALL_POS_X;
    game->ball.rect.y = BALL_POS_Y;
    
    const float angle_deg = 45.f + (float)GetRandomValue(0, 90); 
    const float angle_rad = angle_deg * (PI / 180.f);

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

void draw(GameState *game) {
    BeginDrawing();
    
    ClearBackground(BG_COLOR);
    
    DrawFPS(FPS_TEXT_POS_X, FPS_TEXT_POS_Y);

    DrawRectangleRec(game->player.rect, game->player.color);
    DrawCircle(
        game->ball.rect.x + game->ball.rect.width / 2,
        game->ball.rect.y + game->ball.rect.height / 2,
        game->ball.rect.width / 2,
        game->ball.color
    );

    draw_bricks(game);
    DrawText(TextFormat("%d", game->player.lives), TEXT_POS_X, TEXT_POS_Y, TEXT_FONT_SIZE, TEXT_COLOR);
    
    if (game->status == GAME_OVER) {
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2, 60, RED);
    } else if (game->status == GAME_WIN) {
        DrawText("YOU WIN!", SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT / 2, 60, GREEN);
    }

    EndDrawing();
}

void draw_bricks(GameState *game) {
    for (size_t i = 0; i < LINES_OF_BRICK; ++i) {
        for (size_t j = 0; j < BRICKS_PER_LINE; ++j) {
            if (game->bricks[i][j].active) {
                Brick *brick = &game->bricks[i][j];
                DrawRectangleRec(brick->rect, brick->color);
            }
        }
    }
}

