#include "game.h"

int main(void) {
    game_t *game = game_create();
    game_load_resources(game);
    game_init(game);

    while (game->running) {
        const float dt = GetFrameTime();
        game_update(game, dt);
        game_render(game);
    }

    game_unload_resources(game);
    game_destroy(game);
    return 0;
}
