#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

#include "raylib.h"

#include "game.h"

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif // PLATFORM_WEB

#define X(name, ...) name##_t name;
GAME_FUNCS
#undef X

#ifdef HOTRELOAD
#include <dlfcn.h>
void *libgame = NULL;
#endif // HOTRELOAD

bool load_libgame(void) {
#ifdef HOTRELOAD

    if (libgame != NULL) dlclose(libgame);

    libgame = dlopen("./build/libgame.so", RTLD_NOW);
    if (libgame == NULL) {
        nob_log(ERROR, "Could not load libgame: %s", dlerror());
        return false;
    }

    #define X(name, ...)  \
        name = dlsym(libgame, #name); \
        if (name == NULL) { \
            nob_log(ERROR, "Could not load symbol %s: %s", #name, dlerror()); \
            return false; \
        }
    GAME_FUNCS
    #undef X

#endif // HOTRELOAD
    return true;
}

int main(void) {
    InitWindow(640, 480, "My Raylib App");

    if (!load_libgame()) return 1;

    game_init();

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(game_update, 0, true);
#else
    while (!WindowShouldClose()) {
#ifdef HOTRELOAD
        if (IsKeyPressed(KEY_F5)) {
            Game *game = game_pre_reload();
            load_libgame();
            game_post_reload(game);
        }
#endif // HOTRELOAD
        game_update();
    }
#endif // PLATFORM_WEB

    CloseWindow();
    return 0;
}
