#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

#include "raylib.h"

#define MACRO_VAR(name) _##name##__LINE__
#define BEGIN_END_NAMED(begin, end, i) for (int i = (begin, 0); i < 1; i++, end)
#define BEGIN_END(begin, end) BEGIN_END_NAMED(begin, end, MACRO_VAR(i))
#define Drawing() BEGIN_END(BeginDrawing(), EndDrawing())
#define Mode3D(camera) BEGIN_END(BeginMode3D(camera), EndMode3D())

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif // PLATFORM_WEB

typedef struct {} Game;

void game_init(Game *game) {
    memset(game, 0, sizeof(*game));
}

void game_update(Game *game) {
    UNUSED(game);
    Drawing() {
        ClearBackground(RED);
    }
}

int main(void) {
    InitWindow(640, 480, "My Raylib App");

    static Game game;
    game_init(&game);

#ifdef PLATFORM_WEB
    emscripten_set_main_loop_arg((em_arg_callback_func)game_update, &game, 0, true);
#else
    while (!WindowShouldClose()) game_update(&game);
#endif // PLATFORM_WEB

    CloseWindow();
    return 0;
}
