#include "screen.h"

// TODO: what if screen res will change?


void screen_pause_init(
    pause_screen_t *screen,
    Vector2 screen_res,
    const char **titles,
    int *font_sizes,
    Color *text_colors
) {
    screen->pause_item.text = titles[0];
    screen->pause_item.text_font_size = font_sizes[0];
    screen->pause_item.text_width = MeasureText(screen->pause_item.text, screen->pause_item.text_font_size);
    screen->pause_item.text_pos = (Vector2){
        (screen_res.x - screen->pause_item.text_width) / 2.f,
        screen_res.y / 2.f - 40.f
    };
    screen->pause_item.text_color = text_colors[0];

    screen->resume_item.text = titles[1];
    screen->resume_item.text_font_size = font_sizes[1];
    screen->resume_item.text_width = MeasureText(screen->pause_item.text, screen->pause_item.text_font_size);
    screen->resume_item.text_pos = (Vector2){
        (screen_res.x - screen->resume_item.text_width) / 2.f,
        screen_res.y / 2.f + 40.f
    };
    screen->resume_item.text_color = text_colors[1];
}

void screen_pause_render(const pause_screen_t *screen) {
    DrawText(
        screen->pause_item.text,
        screen->pause_item.text_pos.x,
        screen->pause_item.text_pos.y,
        screen->pause_item.text_font_size,
        screen->pause_item.text_color
    );

    DrawText(
        screen->resume_item.text,
        screen->resume_item.text_pos.x,
        screen->resume_item.text_pos.y,
        screen->resume_item.text_font_size,
        screen->resume_item.text_color
    );
}

void screen_game_over_init(
    game_over_screen_t *screen,
    Vector2 screen_res,
    const char **titles,
    int *font_sizes,
    Color *text_colors
) {
    screen->game_over_item.text = titles[0];
    screen->game_over_item.text_font_size = font_sizes[0];
    screen->game_over_item.text_width = MeasureText(screen->game_over_item.text, screen->game_over_item.text_font_size);
    screen->game_over_item.text_pos = (Vector2){
        (screen_res.x - screen->game_over_item.text_width) / 2.f,
        screen_res.y / 2 - 180.f
    };
    screen->game_over_item.text_color = text_colors[0];

    screen->score_item.text = titles[1];
    screen->score_item.text_font_size = font_sizes[1];
    screen->score_item.text_width = MeasureText(screen->score_item.text, screen->score_item.text_font_size);
    screen->score_item.text_pos = (Vector2){
        (screen_res.x - screen->score_item.text_width) / 2.f,
        screen_res.y / 2.f
    };
    screen->score_item.text_color = text_colors[1];

    screen->restart_item.text = titles[2];
    screen->restart_item.text_font_size = font_sizes[2];
    screen->restart_item.text_width = MeasureText(screen->restart_item.text, screen->restart_item.text_font_size);
    screen->restart_item.text_pos = (Vector2){
        (screen_res.x - screen->restart_item.text_width) / 2.f,
        screen_res.y / 2 + 100.f
    };
    screen->restart_item.text_color = text_colors[2];

    screen->exit_item.text = titles[3];
    screen->exit_item.text_font_size = font_sizes[3];
    screen->exit_item.text_width = MeasureText(screen->exit_item.text, screen->exit_item.text_font_size);
    screen->exit_item.text_pos = (Vector2){
        (screen_res.x - screen->exit_item.text_width) / 2.f,
        screen_res.y / 2 + 2 * 100.f
    };
    screen->exit_item.text_color = text_colors[3];
}

void screen_game_over_render(const game_over_screen_t *screen, int final_score) {
    DrawText(
        screen->game_over_item.text,
        screen->game_over_item.text_pos.x, screen->game_over_item.text_pos.y,
        screen->game_over_item.text_font_size,
        screen->game_over_item.text_color
    );
    DrawText(
        screen->score_item.text,
        screen->score_item.text_pos.x, screen->score_item.text_pos.y,
        screen->score_item.text_font_size,
        screen->score_item.text_color
    );
    DrawText(
        screen->restart_item.text,
        screen->restart_item.text_pos.x, screen->restart_item.text_pos.y,
        screen->restart_item.text_font_size,
        screen->restart_item.text_color
    );
    DrawText(
        screen->exit_item.text,
        screen->exit_item.text_pos.x, screen->exit_item.text_pos.y,
        screen->exit_item.text_font_size,
        screen->exit_item.text_color
    );
}
