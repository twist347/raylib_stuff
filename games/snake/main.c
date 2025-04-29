#include "game.h"

#include "stdio.h"

int main() {
    game_t game;
    game_init(&game);

    while (!WindowShouldClose() && game.running) {
        const float dt = GetFrameTime();
        game_update(&game, dt);
        game_render(&game);
    }

    game_destroy(&game);
}