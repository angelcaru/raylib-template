#include "game.h"

#ifdef HOTRELOAD
    #define NOB_IMPLEMENTATION
#endif // HOTRELOAD
#define NOB_STRIP_PREFIX
#include "nob.h"

#include "raylib.h"
#define MACRO_VAR(name) _##name##__LINE__
#define BEGIN_END_NAMED(begin, end, i) for (int i = (begin, 0); i < 1; i++, end)
#define BEGIN_END(begin, end) BEGIN_END_NAMED(begin, end, MACRO_VAR(i))
#define Drawing() BEGIN_END(BeginDrawing(), EndDrawing())
#define Mode3D(camera) BEGIN_END(BeginMode3D(camera), EndMode3D())

struct Game {
    size_t size;

    // Put all of the state of your game here
};

Game *g;

void game_init(void) {
    g = malloc(sizeof(*g));
    memset(g, 0, sizeof(*g));
    g->size = sizeof(*g);
}

Game* game_pre_reload(void) {
    return g;
}
void game_post_reload(Game *new_g) {
    g = new_g;

    if (g->size > sizeof(*g)) {
        nob_log(INFO, "Migrating struct Game (%zu bytes -> %zu bytes)", g->size, sizeof(*g));
        g = realloc(g, sizeof(*g));
        memset((char*)g + g->size, 0, sizeof(*g) - g->size);
        g->size = sizeof(*g);
    }
}

void game_update(void) {
    Drawing() {
        ClearBackground(RED);
    }
}
