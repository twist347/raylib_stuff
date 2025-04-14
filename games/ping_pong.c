/*
 * use #define for colors because of -pedantic flag
 */

#include <stdbool.h>
#include <math.h>

#include "raylib.h"

// screen settings
const float SCREEN_WIDTH = 1920.f;
const float SCREEN_HEIGHT = 1080.f;
const int FPS = 60;
const char *WINDOW_LABEL = "Ping Pong";
#define BG_COLOR BLACK

// menu settings
const char *MENU_TITLE = "Ping Pong";
const char *MENU_INVITATION_TO_GAME_SECTION = "Press ENTER to start";
const char *MENU_INFO_SECTION = "Press I to read info";
const char *MENU_INFO_HEADER = "Info Screen";
const char *MENU_INFO_LINE1 = "Game info and hotkeys:";
const char *MENU_INFO_LINE2 = "- W/S and UP/DOWN for paddles";
const char *MENU_INFO_LINE3 = "- P to pause, N for a new game";
const char *MENU_INFO_LINE4 = "Press ENTER to return";
const int MENU_TITLE_FONT_SIZE = 100;
const int MENU_FONT_SIZE = 40;
const int PADDING = 50;
#define MENU_TITLE_COLOR RED
#define MENU_COLOR WHITE

// pause settings
const char *PAUSE_TEXT = "Pause";
const float PAUSE_FONT_SIZE = 80.f;

// paddle settings
const float PADDLE_SPEED = 20.f;
const float PADDLE_WIDTH = 20.f;
const float PADDLE_HEIGHT = 150.f;
#define PADDLE_COLOR WHITE

// ball settings
const float BALL_SIZE = 30.f;
const float BALL_SPEED = 10.f;
const float BALL_SPEED_PERCENT_INCREASE = 1.1f;
#define BALL_COLOR RED

// center circle settings
const float CENTER_CIRCLE_RADIUS = 20.0f;
#define CENTER_CIRCLE_COLOR WHITE

// dash line settings
const int DASH_HEIGHT = 20;
const int DASH_SPACING = 20;
const float DASH_LINE_THICKNESS = 5.f;
#define DASH_LINE_COLOR WHITE

typedef enum {
    MENU,
    GAME,
    MENU_INFO
} GameScreen;

typedef struct {
    Rectangle rect;
    float speed;
    int score;
    Color color;
} Paddle;

typedef struct {
    Rectangle rect;
    Vector2 speed;
    Color color;
} Ball;

typedef struct {
    Paddle left_player;
    Paddle right_player;
    Ball ball;
    bool pause;
    GameScreen screen;
} GameState;

void init_game(GameState *game);

void handle_input(GameState *game);
void handle_paddle_wall_collision(Paddle *paddle);
void handle_ball_wall_collision(GameState *game);
void handle_ball_paddle_collision(GameState *game);
void handle_menu_input(GameState *game);
void handle_info_input(GameState *game);

void update_game(GameState *game);
void update_score(GameState *game);
void reset_ball(GameState *game);
void new_game(GameState *game);

void draw_dash_line(void);
void draw_center_circle(void);
void draw_game(GameState *game);
void draw_menu(void);
void draw_info(void);

int main(void) {
    InitWindow((int) SCREEN_WIDTH, (int) SCREEN_HEIGHT, WINDOW_LABEL);
    SetTargetFPS(FPS);

    GameState game;
    init_game(&game);

    while (!WindowShouldClose()) {
        switch (game.screen) {
            case MENU:
                handle_menu_input(&game);
                draw_menu();
                break;
            case GAME:
                handle_input(&game);
                update_game(&game);
                draw_game(&game);
                break;
            case MENU_INFO:
                handle_info_input(&game);
                draw_info();
                break;
            default:
                break;
        }
    }

    CloseWindow();
}

void init_game(GameState *game) {
    Paddle left_player = {
            .rect = {50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT},
            .speed = PADDLE_SPEED,
            .score = 0,
            .color = PADDLE_COLOR
    };

    Paddle right_player = {
            .rect = {SCREEN_WIDTH - 50 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH,
                     PADDLE_HEIGHT},
            .speed = PADDLE_SPEED,
            .score = 0,
            .color = PADDLE_COLOR
    };

    Ball ball = {
            .rect = {SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE},
            .speed = {BALL_SPEED, BALL_SPEED},
            .color = BALL_COLOR
    };

    game->left_player = left_player;
    game->right_player = right_player;
    game->ball = ball;
    game->pause = false;
    game->screen = MENU;

    reset_ball(game);
}

void handle_input(GameState *game) {
    if (IsKeyPressed(KEY_P)) {
        game->pause = !game->pause;
    }

    if (IsKeyPressed(KEY_N)) {
        new_game(game);
    }

    if (!game->pause) {
        // left player
        if (IsKeyDown(KEY_W)) {
            game->left_player.rect.y -= game->left_player.speed;
        }
        if (IsKeyDown(KEY_S)) {
            game->left_player.rect.y += game->left_player.speed;
        }

        // right player
        if (IsKeyDown(KEY_UP)) {
            game->right_player.rect.y -= game->right_player.speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            game->right_player.rect.y += game->right_player.speed;
        }
    }
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
    if (game->ball.rect.y <= 0 || game->ball.rect.y + game->ball.rect.height >= SCREEN_HEIGHT) {
        game->ball.speed.y = -game->ball.speed.y;
    }
}

void handle_ball_paddle_collision(GameState *game) {
    if (CheckCollisionCircleRec(
            (Vector2) {game->ball.rect.x + BALL_SIZE / 2, game->ball.rect.y + BALL_SIZE / 2},
            BALL_SIZE / 2,
            game->left_player.rect
    )) {
        game->ball.speed.x = -game->ball.speed.x;
        // get rid of weird stuff when ball stucks in paddle
        game->ball.rect.x = game->left_player.rect.x + game->left_player.rect.width;
        game->ball.speed.x *= BALL_SPEED_PERCENT_INCREASE;
        game->ball.speed.y *= BALL_SPEED_PERCENT_INCREASE;
    }
    if (CheckCollisionCircleRec(
            (Vector2) {game->ball.rect.x + BALL_SIZE / 2, game->ball.rect.y + BALL_SIZE / 2},
            BALL_SIZE / 2,
            game->right_player.rect
    )) {
        game->ball.speed.x = -game->ball.speed.x;
        // get rid of weird stuff when ball stucks in paddle
        game->ball.rect.x = game->right_player.rect.x - game->ball.rect.width;
        game->ball.speed.x *= BALL_SPEED_PERCENT_INCREASE;
        game->ball.speed.y *= BALL_SPEED_PERCENT_INCREASE;
    }
}

void handle_menu_input(GameState *game) {
    if (IsKeyPressed(KEY_ENTER)) {
        new_game(game);
        game->screen = GAME;
    }
    if (IsKeyPressed(KEY_I)) {
        game->screen = MENU_INFO;
    }
}

void handle_info_input(GameState *game) {
    if (IsKeyPressed(KEY_ENTER)) {
        game->screen = MENU;
    }
}

void update_game(GameState *game) {
    if (game->pause) {
        return;
    }

    handle_paddle_wall_collision(&game->left_player);
    handle_paddle_wall_collision(&game->right_player);

    game->ball.rect.x += game->ball.speed.x;
    game->ball.rect.y += game->ball.speed.y;

    handle_ball_wall_collision(game);
    handle_ball_paddle_collision(game);
    update_score(game);
}

void update_score(GameState *game) {
    if (game->ball.rect.x + game->ball.rect.width < 0) {
        ++game->right_player.score;
        reset_ball(game);
    }
    if (game->ball.rect.x > SCREEN_WIDTH) {
        ++game->left_player.score;
        reset_ball(game);
    }
}

void reset_ball(GameState *game) {
    game->ball.rect.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
    game->ball.rect.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;

    const float angle_offset = GetRandomValue(-45, 45) * (PI / 180.f);
    float angle;
    if (GetRandomValue(0, 1) == 0) {
        angle = angle_offset;
    } else {
        angle = PI + angle_offset;
    }

    game->ball.speed.x = BALL_SPEED * cosf(angle);
    game->ball.speed.y = BALL_SPEED * sinf(angle);
}

void new_game(GameState *game) {
    game->left_player.score = 0;
    game->right_player.score = 0;

    game->left_player.rect.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    game->right_player.rect.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

    reset_ball(game);
}

void draw_dash_line(void) {
    for (int y = 0; y < (int) SCREEN_HEIGHT; y += DASH_HEIGHT + DASH_SPACING) {
        DrawRectangle(
                SCREEN_WIDTH / 2 - DASH_LINE_THICKNESS / 2,
                y,
                DASH_LINE_THICKNESS,
                DASH_HEIGHT,
                DASH_LINE_COLOR
        );
    }
}

void draw_center_circle(void) {
    DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CENTER_CIRCLE_RADIUS, CENTER_CIRCLE_COLOR);
}

void draw_game(GameState *game) {
    BeginDrawing();

    ClearBackground(BG_COLOR);

    DrawFPS(10, 10);
    draw_dash_line();
    draw_center_circle();

    DrawRectangleRec(game->left_player.rect, game->left_player.color);
    DrawRectangleRec(game->right_player.rect, game->right_player.color);

    DrawCircle(
            game->ball.rect.x + BALL_SIZE / 2,
            game->ball.rect.y + BALL_SIZE / 2,
            BALL_SIZE / 2, game->ball.color
    );

    DrawText(TextFormat("%d", game->left_player.score), 20, SCREEN_HEIGHT - 50, 50, WHITE);
    DrawText(TextFormat("%d", game->right_player.score), SCREEN_WIDTH - 40, SCREEN_HEIGHT - 50, 50, WHITE);

    if (game->pause) {
        const float pause_text_width = MeasureText(PAUSE_TEXT, PAUSE_FONT_SIZE);
        DrawText(
                PAUSE_TEXT, SCREEN_WIDTH / 2 - pause_text_width / 2,
                SCREEN_HEIGHT / 2 - PAUSE_FONT_SIZE / 2,
                PAUSE_FONT_SIZE,
                WHITE
        );
    }

    EndDrawing();
}

void draw_menu(void) {
    const float title_width = MeasureText(MENU_TITLE, MENU_TITLE_FONT_SIZE);
    const float inv_width = MeasureText(MENU_INVITATION_TO_GAME_SECTION, MENU_FONT_SIZE);
    const float info_width = MeasureText(MENU_INFO_SECTION, MENU_FONT_SIZE);

    const float total_text_height = MENU_TITLE_FONT_SIZE + MENU_FONT_SIZE + MENU_FONT_SIZE + (2 * PADDING);

    const float start_y = SCREEN_HEIGHT / 2 - total_text_height / 2;

    BeginDrawing();

    ClearBackground(BG_COLOR);

    DrawText(MENU_TITLE, SCREEN_WIDTH / 2 - title_width / 2, start_y, MENU_TITLE_FONT_SIZE, MENU_TITLE_COLOR);

    int inv_y = start_y + MENU_TITLE_FONT_SIZE + 2 * PADDING;
    DrawText(MENU_INVITATION_TO_GAME_SECTION, SCREEN_WIDTH / 2 - inv_width / 2, inv_y, MENU_FONT_SIZE, MENU_COLOR);

    int info_y = inv_y + MENU_FONT_SIZE + PADDING;
    DrawText(MENU_INFO_SECTION, SCREEN_WIDTH / 2 - info_width / 2, info_y, MENU_FONT_SIZE, MENU_COLOR);

    EndDrawing();
}

void draw_info(void) {
    const float header_width = MeasureText(MENU_INFO_HEADER, MENU_TITLE_FONT_SIZE);
    const float line1_width = MeasureText(MENU_INFO_LINE1, MENU_FONT_SIZE);
    const float line2_width = MeasureText(MENU_INFO_LINE2, MENU_FONT_SIZE);
    const float line3_width = MeasureText(MENU_INFO_LINE3, MENU_FONT_SIZE);
    const float line4_width = MeasureText(MENU_INFO_LINE4, MENU_FONT_SIZE);

    float total_text_height = MENU_TITLE_FONT_SIZE + (4 * MENU_FONT_SIZE) + (4 * PADDING);

    float start_y = SCREEN_HEIGHT / 2 - total_text_height / 2;

    BeginDrawing();

    ClearBackground(BG_COLOR);

    DrawText(MENU_INFO_HEADER, SCREEN_WIDTH / 2 - header_width / 2, start_y, MENU_TITLE_FONT_SIZE, MENU_TITLE_COLOR);

    int current_y = start_y + MENU_TITLE_FONT_SIZE + PADDING;
    DrawText(MENU_INFO_LINE1, SCREEN_WIDTH / 2 - line1_width / 2, current_y, MENU_FONT_SIZE, MENU_COLOR);

    current_y += MENU_FONT_SIZE + PADDING;
    DrawText(MENU_INFO_LINE2, SCREEN_WIDTH / 2 - line2_width / 2, current_y, MENU_FONT_SIZE, MENU_COLOR);

    current_y += MENU_FONT_SIZE + PADDING;
    DrawText(MENU_INFO_LINE3, SCREEN_WIDTH / 2 - line3_width / 2, current_y, MENU_FONT_SIZE, MENU_COLOR);

    current_y += MENU_FONT_SIZE + PADDING;
    DrawText(MENU_INFO_LINE4, SCREEN_WIDTH / 2 - line4_width / 2, current_y, MENU_FONT_SIZE, MENU_COLOR);

    EndDrawing();
}
