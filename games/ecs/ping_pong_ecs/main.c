#include "game.h"

int main(void) {
    game_t *game = game_create();
    game_init(game);

    while (game->running) {
        const float dt = GetFrameTime();
        game_update(game, dt);
        game_render(game);
    }

    game_destroy(game);
    return 0;
}
