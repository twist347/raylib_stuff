#include <stdbool.h>
#include <math.h>

#include "raylib.h"
#include "raymath.h"

// screen settings
const float SCREEN_WIDTH = 1920.f;
const float SCREEN_HEIGHT = 1080.f;
const float SW_HALF = SCREEN_WIDTH / 2.f;
const float SH_HALF = SCREEN_HEIGHT / 2.f;
const char *WINDOW_LABEL = "Ping Pong V2";
#define BG_COLOR BLACK

// fps settings
const int FPS_TEXT = 60;
const Vector2 FPS_POS = {10.f, 10.f,};

// paddles settings
const float PADDLE_WIDTH = 20.f;
const float PADDLE_HEIGHT = 200.f;
const Vector2 LEFT_PADDLE_POS = {20.f, SH_HALF - PADDLE_HEIGHT / 2.f};
const Vector2 RIGHT_PADDLE_POS = {SCREEN_WIDTH - 20.f - PADDLE_WIDTH, LEFT_PADDLE_POS.y};
const float PADDLE_VELOCITY = 500.f;
const float PADDLE_VELOCITY_SCALE = 1.05f;
#define PADDLE_COLOR WHITE

// ball settings
const float BALL_RADIUS = 15.f;
const Vector2 BALL_POS = {SW_HALF, SH_HALF};
const float BALL_VELOCITY = 500.f;
const float BALL_VELOCITY_SCALE = 1.1f;
const float BALL_MAX_REFLECTION_ANGLE = 60.f;
#define BALL_COLOR RED

// draw scores settings
const Vector2 SCORES_TEXT_LEFT_POS = {30.f, SCREEN_HEIGHT - 50.f};
const Vector2 SCORES_TEXT_RIGHT_POS = {SCREEN_WIDTH - 50.f, SCORES_TEXT_LEFT_POS.y};
const int SCORES_TEXT_FONT_SIZE = 50;
#define SCORES_TEXT_COLOR WHITE

// dash line settings
const float DASH_LINE_HEIGHT = 20.f;
const float DASH_LINE_GAP_HEIGHT = 10.f;
const float DASH_LINE_CENTER_X = SW_HALF;
#define DASH_LINE_COLOR WHITE

// menu settings
const int MENU_TEXT_TITLE_FONT_SIZE = 60;
const int MENU_TEXT_FONT_SIZE = 40;
#define MENU_TEXT_TITLE_COLOR RED
#define MENU_TEXT_COLOR WHITE

typedef struct {
    const char *text;
    int font_size;
    Color color;
    Vector2 pos;
    int width;
} MenuItem;

const char *MAIN_MENU_TEXTS[] = {
    "Ping Pong V2",
    "Press ENTER to start game",
    "Press H for Help"
};
MenuItem main_menu[sizeof(MAIN_MENU_TEXTS) / sizeof(MAIN_MENU_TEXTS[0])];

const char *HELP_MENU_TEXTS[] = {
    "Help",
    "Controls:",
    "  W/S - Move left paddle",
    "  UP/DOWN - Move right paddle",
    "  SPACE - Serve the ball",
    "  M - Return to menu (from game)",
    "  ESC - End the game",
    "Press ENTER to return to menu"
};
MenuItem help_menu[sizeof(HELP_MENU_TEXTS) / sizeof(HELP_MENU_TEXTS[0])];

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
void init_main_menu(void);
void init_help_menu(void);

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
void draw_main_menu(void);
void draw_help_menu(void);

int main(void) {
    InitWindow((int) SCREEN_WIDTH, (int) SCREEN_HEIGHT, WINDOW_LABEL);
    SetTargetFPS(FPS_TEXT);
    HideCursor();

    GameState game;
    init_game(&game);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        switch (game.screen) {
            case SCREEN_MENU:
                handle_menu_input(&game);
                draw_main_menu();
                break;
            case SCREEN_GAME:
                handle_game_input(&game, dt);
                update_game(&game, dt);
                draw_game(&game);
                break;
            case SCREEN_HELP:
                handle_help_input(&game);
                draw_help_menu();
                break;
            default:
                break;
        }
    }

    CloseWindow();
}

void init_game(GameState *game) {
    Paddle left_paddle = {
        .rect = {LEFT_PADDLE_POS.x, LEFT_PADDLE_POS.y, PADDLE_WIDTH, PADDLE_HEIGHT},
        .velocity = PADDLE_VELOCITY,
        .color = PADDLE_COLOR
    };

    Paddle right_paddle = {
        .rect = {RIGHT_PADDLE_POS.x, RIGHT_PADDLE_POS.y, PADDLE_WIDTH, PADDLE_HEIGHT},
        .velocity = PADDLE_VELOCITY,
        .color = PADDLE_COLOR
    };

    Ball ball = {
        .pos = BALL_POS,
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

    init_main_menu();
    init_help_menu();
}

void init_main_menu(void) {
    // precompute main menu items
    const int count = sizeof(main_menu) / sizeof(main_menu[0]);
    for (int i = 0; i < count; ++i) {
        main_menu[i].text = MAIN_MENU_TEXTS[i];
        if (i == 0) {
            // title
            main_menu[i].font_size = MENU_TEXT_TITLE_FONT_SIZE;
            main_menu[i].color = MENU_TEXT_TITLE_COLOR;
            main_menu[i].width = MeasureText(main_menu[i].text, main_menu[i].font_size);
            main_menu[i].pos = (Vector2){SW_HALF - main_menu[i].width / 2, SH_HALF - 150};
        } else {
            // menu options
            main_menu[i].font_size = MENU_TEXT_FONT_SIZE;
            main_menu[i].color = MENU_TEXT_COLOR;
            main_menu[i].width = MeasureText(main_menu[i].text, main_menu[i].font_size);
            const float y_offset = (i == 1 ? SH_HALF - 50 : SH_HALF + 10);
            main_menu[i].pos = (Vector2){SW_HALF - main_menu[i].width / 2, y_offset};
        }
    }
}

void init_help_menu(void) {
    // precompute help menu items
    const int count = sizeof(help_menu) / sizeof(help_menu[0]);
    for (int i = 0; i < count; ++i) {
        help_menu[i].text = HELP_MENU_TEXTS[i];
        if (i == 0) {
            // title
            help_menu[i].font_size = MENU_TEXT_TITLE_FONT_SIZE;
            help_menu[i].color = MENU_TEXT_TITLE_COLOR;
            help_menu[i].width = MeasureText(help_menu[i].text, help_menu[i].font_size);
            help_menu[i].pos = (Vector2){SW_HALF - help_menu[i].width / 2, SH_HALF - 350};
        } else {
            // help lines
            help_menu[i].font_size = MENU_TEXT_FONT_SIZE;
            help_menu[i].color = MENU_TEXT_COLOR;
            help_menu[i].width = MeasureText(help_menu[i].text, help_menu[i].font_size);
            help_menu[i].pos = (Vector2){SW_HALF - 300, SH_HALF - 250 + (i - 1) * (MENU_TEXT_FONT_SIZE + 10)};
        }
    }
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
    game->ball.pos = BALL_POS;

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

        // clamp reflection angle and increase ball and paddle velocity after collision
        if (is_collision && ((is_left && game->ball.velocity.x < 0) || (!is_left && game->ball.velocity.x > 0))) {
            const float angle = get_ball_reflection_angle(paddle, game->ball.pos.y);
            const float new_angle = is_left ? angle : PI - angle;
            vel *= BALL_VELOCITY_SCALE;
            game->ball.velocity = (Vector2){vel * cosf(new_angle), vel * sinf(new_angle)};
            game->left_paddle.velocity *= PADDLE_VELOCITY_SCALE;
            game->right_paddle.velocity *= PADDLE_VELOCITY_SCALE;
        }
    }
}

float get_ball_reflection_angle(Paddle *paddle, float ball_y) {
    static const float BALL_MAX_REFLECTION_ANGLE_RAD = BALL_MAX_REFLECTION_ANGLE * (PI / 180.f);
    const float paddle_center_y = paddle->rect.y + paddle->rect.height / 2.f;
    const float delta_y = ball_y - paddle_center_y;
    const float norm = Clamp(delta_y / (paddle->rect.height / 2.f), -1.f, 1.f);
    return norm * BALL_MAX_REFLECTION_ANGLE_RAD;
}

void draw_game(const GameState *game) {
    BeginDrawing();

    ClearBackground(BG_COLOR);

    DrawFPS(FPS_POS.x, FPS_POS.y);

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
        SCORES_TEXT_LEFT_POS.x, SCORES_TEXT_LEFT_POS.y,
        SCORES_TEXT_FONT_SIZE,
        SCORES_TEXT_COLOR
    );

    DrawText(
        TextFormat("%d", game->right_player_score),
        SCORES_TEXT_RIGHT_POS.x, SCORES_TEXT_RIGHT_POS.y,
        SCORES_TEXT_FONT_SIZE,
        SCORES_TEXT_COLOR
    );
}

void draw_dash_line(void) {
    for (float y = 0; y < SCREEN_HEIGHT; y += DASH_LINE_HEIGHT + DASH_LINE_GAP_HEIGHT) {
        const float CUR_DASH_HEIGHT = (y + DASH_LINE_HEIGHT) > SCREEN_HEIGHT ? (SCREEN_HEIGHT - y) : DASH_LINE_HEIGHT;
        DrawLine(
            DASH_LINE_CENTER_X, y,
            DASH_LINE_CENTER_X, y + CUR_DASH_HEIGHT,
            DASH_LINE_COLOR
        );
    }
}

void draw_main_menu(void) {
    static const int count = sizeof(main_menu) / sizeof(main_menu[0]);

    BeginDrawing();

    ClearBackground(BG_COLOR);

    for (int i = 0; i < count; ++i) {
        DrawText(
            main_menu[i].text,
            main_menu[i].pos.x,
            main_menu[i].pos.y,
            main_menu[i].font_size,
            main_menu[i].color
        );
    }
    EndDrawing();
}

void draw_help_menu(void) {
    static const int count = sizeof(help_menu) / sizeof(help_menu[0]);

    BeginDrawing();

    ClearBackground(BG_COLOR);

    for (int i = 0; i < count; ++i) {
        DrawText(
            help_menu[i].text,
            help_menu[i].pos.x,
            help_menu[i].pos.y,
            help_menu[i].font_size,
            help_menu[i].color
        );
    }

    EndDrawing();
}
