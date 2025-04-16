#include <stdbool.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"

// screen settings
const float SCREEN_WIDTH = 1920.f;
const float SCREEN_HEIGHT = 1080.f;
const char *WINDOW_LABEL = "Ping Pong V2";
#define BG_COLOR BLACK

// fps settings
const int FPS = 60;
const float FPS_POS_X = 10.f;
const float FPS_POS_Y = 10.f;

// paddles settings
const float PADDLE_WIDTH = 20.f;
const float PADDLE_HEIGHT = 200.f;
const float LEFT_PADDLE_POS_X = 20.f;
const float LEFT_PADDLE_POS_Y = SCREEN_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f;
const float RIGHT_PADDLE_POS_X = SCREEN_WIDTH - 20.f - PADDLE_WIDTH;
const float RIGHT_PADDLE_POS_Y = LEFT_PADDLE_POS_Y;
const float PADDLE_VELOCITY = 500.f;
#define PADDLE_COLOR WHITE

// ball settings
const float BALL_RADIUS = 15.f;
const float BALL_POS_X = SCREEN_WIDTH / 2.f;
const float BALL_POS_Y = SCREEN_HEIGHT / 2.f;
const float BALL_VELOCITY = 500.f;
const float BALL_VELOCITY_INCREASE_FACTOR = 1.1f;
const float BALL_MAX_REFLECTION_ANGLE = 60.f;
const float BALL_MAX_REFLECTION_ANGLE_RAD = BALL_MAX_REFLECTION_ANGLE * (PI / 180.f);
#define BALL_COLOR RED

// draw scores settings
const float SCORES_TEXT_LEFT_POS_X = 30.f;
const float SCORES_TEXT_LEFT_POS_Y = SCREEN_HEIGHT - 50.f;
const float SCORES_TEXT_RIGHT_POS_X = SCREEN_WIDTH - 50.f;
const float SCORES_TEXT_RIGHT_POS_Y = SCREEN_HEIGHT - 50.f;
const int SCORES_TEXT_FONT_SIZE = 50;
#define SCORES_TEXT_COLOR WHITE

// dash line settings
const float DASH_LINE_HEIGHT = 20.f;
const float DASH_LINE_GAP_HEIGHT = 10.f;
const float DASH_LINE_CENTER_X = SCREEN_WIDTH / 2.f;
#define DASH_LINE_COLOR WHITE

typedef struct {
    Rectangle rect;
    float velocity;
    Color color;
} Paddle;

typedef struct {
    Vector2 pos;
    float radius;
    Vector2 velocity;
    bool active;
    Color color;
} Ball;

typedef enum {
    SCREEN_GAME,
    SCREEN_MENU,
    SCREEN_HELP
} GameScreen;

typedef struct {
    Paddle left_paddle;
    Paddle right_paddle;
    Ball ball;
    int left_player_score;
    int right_player_score;
    GameScreen screen;
} GameState;

void init_game(GameState *game);

void handle_game_input(GameState *game, float dt);
void handle_menu_input(GameState *game);
void handle_help_input(GameState *game);

void update_game(GameState *game, float dt);
void update_ball(GameState *game, float dt);
void handle_paddle_wall_collision(Paddle *paddle);
void handle_ball_wall_collision(GameState *game);
void handle_ball_paddle_collision(GameState *game);
void update_score(GameState *game);
void reset_ball(GameState *game);
void simple_handle_ball_paddle_collision(GameState *game);
void advanced_handle_ball_paddle_collision(GameState *game);
float get_ball_reflection_angle(Paddle *paddle, float ball_y);

void draw_game(const GameState *game);
void draw_scores(const GameState *game);
void draw_dash_line(void);
void draw_menu(void);
void draw_help(void);

int main(void) {
    InitWindow((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, WINDOW_LABEL);
    SetTargetFPS(FPS);
    HideCursor();

    GameState game;
    init_game(&game);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        switch (game.screen) {
            case SCREEN_MENU:
                handle_menu_input(&game);
                draw_menu();
                break;
            case SCREEN_GAME:
                handle_game_input(&game, dt);
                update_game(&game, dt);
                draw_game(&game);
                break;
            case SCREEN_HELP:
                handle_help_input(&game);
                draw_help();
                break;
            default:
                break;
        }
    }

    CloseWindow();
}

void init_game(GameState *game) {
    Paddle left_paddle = {
        .rect = {LEFT_PADDLE_POS_X, LEFT_PADDLE_POS_Y, PADDLE_WIDTH, PADDLE_HEIGHT},
        .velocity = PADDLE_VELOCITY,
        .color = PADDLE_COLOR
    };

    Paddle right_paddle = {
        .rect = {RIGHT_PADDLE_POS_X, RIGHT_PADDLE_POS_Y, PADDLE_WIDTH, PADDLE_HEIGHT},
        .velocity = PADDLE_VELOCITY,
        .color = PADDLE_COLOR
    };

    Ball ball = {
        .pos = {BALL_POS_X, BALL_POS_Y},
        .radius = BALL_RADIUS,
        .velocity = {BALL_VELOCITY, BALL_VELOCITY},
        .active = false,
        .color = BALL_COLOR
    };

    game->left_paddle = left_paddle;
    game->right_paddle = right_paddle;
    game->ball = ball;
    game->left_player_score = 0;
    game->right_player_score = 0;
    game->screen = SCREEN_MENU;
}

void handle_game_input(GameState *game, float dt) {
    if (IsKeyDown(KEY_W)) {
        game->left_paddle.rect.y -= game->left_paddle.velocity * dt;
    }
    if (IsKeyDown(KEY_S)) {
        game->left_paddle.rect.y += game->left_paddle.velocity * dt;
    }

    if (IsKeyDown(KEY_UP)) {
        game->right_paddle.rect.y -= game->right_paddle.velocity * dt;
    }
    if (IsKeyDown(KEY_DOWN)) {
        game->right_paddle.rect.y += game->right_paddle.velocity * dt;
    }

    if (IsKeyPressed(KEY_M)) {
        init_game(game);
        game->screen = SCREEN_MENU;
    }
}

void handle_menu_input(GameState *game) {
    if (IsKeyPressed(KEY_ENTER)) {
        game->screen = SCREEN_GAME;
    }
    if (IsKeyPressed(KEY_H)) {
        game->screen = SCREEN_HELP;
    }
}

void handle_help_input(GameState *game) {
    if (IsKeyPressed(KEY_ENTER)) {
        game->screen = SCREEN_MENU;
    }
}

void update_game(GameState *game, float dt) {
    handle_paddle_wall_collision(&game->left_paddle);
    handle_paddle_wall_collision(&game->right_paddle);

    if (IsKeyPressed(KEY_SPACE)) {
        game->ball.active = true;
    }

    if (game->ball.active) {
        update_ball(game, dt);
        handle_ball_wall_collision(game);
        handle_ball_paddle_collision(game);
        update_score(game);
    }
}

void update_ball(GameState *game, float dt) {
    game->ball.pos.x += game->ball.velocity.x * dt;
    game->ball.pos.y += game->ball.velocity.y * dt;
}

void handle_paddle_wall_collision(Paddle *paddle) {
    if (paddle->rect.y < 0) {
        paddle->rect.y = 0;
    }
    if (paddle->rect.y + paddle->rect.height > SCREEN_HEIGHT) {
        paddle->rect.y = SCREEN_HEIGHT - paddle->rect.height;
    }
}

void handle_ball_wall_collision(GameState *game) {
    if (game->ball.pos.y - game->ball.radius <= 0 || game->ball.pos.y + game->ball.radius >= SCREEN_HEIGHT) {
        game->ball.velocity.y *= -1.f;
    }
}

void handle_ball_paddle_collision(GameState *game) {
    // simple_handle_ball_paddle_collision(game);
    advanced_handle_ball_paddle_collision(game);
}

void update_score(GameState *game) {
    if (game->ball.pos.x + game->ball.radius < 0) {
        ++game->right_player_score;
        reset_ball(game);
    }

    if (game->ball.pos.x - game->ball.radius > SCREEN_WIDTH) {
        ++game->left_player_score;
        reset_ball(game);
    }
}

void reset_ball(GameState *game) {
    game->ball.pos = (Vector2) {BALL_POS_X, BALL_POS_Y};

    const float angle_offset = GetRandomValue(-45, 45) * (PI / 180.f);
    const float angle = GetRandomValue(0, 1) == 0 ? angle_offset : angle_offset + PI;
    game->ball.velocity = (Vector2){BALL_VELOCITY * cosf(angle), BALL_VELOCITY * sinf(angle)};

    game->ball.active = false;
}

void simple_handle_ball_paddle_collision(GameState *game) {
    if (
        CheckCollisionCircleRec(game->ball.pos, game->ball.radius, game->left_paddle.rect) &&
        game->ball.velocity.x < 0 /* moving to left paddle, otherwise sticking in paddle */
    ) {
        game->ball.velocity.x *= -1.f;
    }
    if (
        CheckCollisionCircleRec(game->ball.pos, game->ball.radius, game->right_paddle.rect) &&
        game->ball.velocity.x > 0 /* moving to right paddle, otherwise sticking in paddle */
    ) {
        game->ball.velocity.x *= -1.f;
    }
}

void advanced_handle_ball_paddle_collision(GameState *game) {
    float vel = sqrtf(powf(game->ball.velocity.x, 2) + powf(game->ball.velocity.y, 2));

    Paddle *paddles[2] = {&game->left_paddle, &game->right_paddle};

    for (int i = 0; i < 2; ++i) {
        Paddle *paddle = paddles[i];
        const bool is_left = i == 0;
        const bool is_collision = CheckCollisionCircleRec(game->ball.pos, game->ball.radius, paddle->rect);

        if (is_collision && ((is_left && game->ball.velocity.x < 0) || (!is_left && game->ball.velocity.x > 0))) {
            const float angle = get_ball_reflection_angle(paddle, game->ball.pos.y);
            const float new_angle = is_left ? angle : PI - angle;
            // update vel
            vel *= BALL_VELOCITY_INCREASE_FACTOR;
            game->ball.velocity = (Vector2) {vel * cosf(new_angle), vel * sinf(new_angle)};
        }
    }
}

float get_ball_reflection_angle(Paddle *paddle, float ball_y) {
    const float paddle_center_y = paddle->rect.y + paddle->rect.height / 2.f;
    const float delta_y = ball_y - paddle_center_y;
    const float norm = Clamp(delta_y / (paddle->rect.height / 2.f), -1.f, 1.f);
    return norm * BALL_MAX_REFLECTION_ANGLE_RAD;
}

void draw_game(const GameState *game) {
    BeginDrawing();

    ClearBackground(BG_COLOR);

    DrawFPS(FPS_POS_X, FPS_POS_Y);

    DrawRectangleRec(game->left_paddle.rect, game->left_paddle.color);
    DrawRectangleRec(game->right_paddle.rect, game->right_paddle.color);

    DrawCircleV(game->ball.pos, game->ball.radius, game->ball.color);

    draw_scores(game);
    draw_dash_line();

    EndDrawing();
}

void draw_scores(const GameState *game) {
    DrawText(
        TextFormat("%d", game->left_player_score),
        SCORES_TEXT_LEFT_POS_X, SCORES_TEXT_LEFT_POS_Y,
        SCORES_TEXT_FONT_SIZE,
        SCORES_TEXT_COLOR
    );

    DrawText(
        TextFormat("%d", game->right_player_score),
        SCORES_TEXT_RIGHT_POS_X, SCORES_TEXT_RIGHT_POS_Y,
        SCORES_TEXT_FONT_SIZE,
        SCORES_TEXT_COLOR
    );
}

void draw_dash_line(void) {
    for (float y = 0; y < SCREEN_HEIGHT; y += DASH_LINE_HEIGHT + DASH_LINE_GAP_HEIGHT) {
        const float CUR_DASH_HEIGHT = ((y + DASH_LINE_HEIGHT) > SCREEN_HEIGHT) ? (SCREEN_HEIGHT - y) : DASH_LINE_HEIGHT;
        DrawLine(DASH_LINE_CENTER_X, y, DASH_LINE_CENTER_X, y + CUR_DASH_HEIGHT, DASH_LINE_COLOR);
    }
}

void draw_menu(void) {
    BeginDrawing();
    ClearBackground(BG_COLOR);

    const char *title = "Ping Pong V2";
    const char *instruction1 = "Press ENTER to start game";
    const char *instruction2 = "Press H for Help";

    int titleWidth = MeasureText(title, 60);
    int instr1Width = MeasureText(instruction1, 40);
    int instr2Width = MeasureText(instruction2, 40);

    DrawText(title, SCREEN_WIDTH / 2 - titleWidth / 2, SCREEN_HEIGHT / 2 - 150, 60, WHITE);
    DrawText(instruction1, SCREEN_WIDTH / 2 - instr1Width / 2, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
    DrawText(instruction2, SCREEN_WIDTH / 2 - instr2Width / 2, SCREEN_HEIGHT / 2 + 10, 40, WHITE);

    EndDrawing();
}

void draw_help(void) {
    BeginDrawing();
    ClearBackground(BG_COLOR);

    const char *header = "Help";
    const char *controls = "Controls:\n"
                           "  W/S - Move left paddle\n"
                           "  UP/DOWN - Move right paddle\n"
                           "  SPACE - Serve the ball\n\n"
                           "Press ESC or BACKSPACE to return to menu";

    int headerWidth = MeasureText(header, 50);
    DrawText(header, SCREEN_WIDTH / 2 - headerWidth / 2, 100, 50, WHITE);
    DrawText(controls, SCREEN_WIDTH / 2 - 300, 200, 30, WHITE);

    EndDrawing();
}
