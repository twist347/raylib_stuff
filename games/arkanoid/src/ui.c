#include "ui.h"

void ui_render_pause(Vector2 screen_res) {
    static const char *pause_text = "PAUSED";
    static const int pause_text_font_size = 80;
    const Color pause_text_color = YELLOW;
    const int pause_text_width = MeasureText(pause_text, pause_text_font_size);
    const Vector2 pause_text_pos = {(screen_res.x - pause_text_width) / 2, screen_res.y / 2 - 100};

    static const char *resume_text = "Press [P] to resume";
    static const int resume_text_font_size = 50;
    const Color resume_text_color = WHITE;
    const int resume_text_width = MeasureText(resume_text, resume_text_font_size);
    const Vector2 resume_text_pos = {(screen_res.x - resume_text_width) / 2, screen_res.y / 2};

    DrawText(pause_text, pause_text_pos.x, pause_text_pos.y, pause_text_font_size, pause_text_color);
    DrawText(resume_text, resume_text_pos.x, resume_text_pos.y, resume_text_font_size, resume_text_color);
}

void ui_render_game_over(Vector2 screen_res) {
    static const char *game_over_text = "GAME OVER";
    static const int game_over_text_font_size = 80;
    const Color game_over_text_color = RED;
    const int game_over_text_width = MeasureText(game_over_text, game_over_text_font_size);
    const Vector2 game_over_text_pos = {(screen_res.x - game_over_text_width) / 2, screen_res.y / 2 - 100};

    static const char *restart_over_text = "Press [ENTER] to restart";
    static const int restart_text_font_size = 50;
    const Color restart_text_color = WHITE;
    const int restart_text_width = MeasureText(restart_over_text, restart_text_font_size);
    const Vector2 restart_text_pos = {(screen_res.x - restart_text_width) / 2, screen_res.y / 2};

    DrawText(game_over_text, game_over_text_pos.x, game_over_text_pos.y, game_over_text_font_size, game_over_text_color);
    DrawText(restart_over_text, restart_text_pos.x, restart_text_pos.y, restart_text_font_size, restart_text_color);
}
