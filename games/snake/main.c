#include "game.h"

int main() {
    game_t game;
    game_init(&game);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();
        game_update(&game, dt);
        game_render(&game);
    }

    game_destroy(&game);
}