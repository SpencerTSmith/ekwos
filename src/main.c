#include "core/arena.h"
#include "core/common.h"
#include "render/render_model.h"
#include "render/render_pipeline.h"
#include "window.h"

bool g_running = true;

void process_input(Window window) {
    glfwPollEvents();

    if (glfwGetKey(window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.handle, true);
}

typedef struct Game Game;
struct Game {
    Window window;
    Render_Context rctx;
};

int main(int argc, char **argv) {
    Arena arena = arena_create(1024 * 100);

    Game game = {0};
    game.window = window_create("yo", 800, 600);
    render_context_init(&arena, &game.rctx, game.window.handle);

    Pipeline_Config config =
        default_pipeline_config(swap_width(&game.rctx), swap_height(&game.rctx));
    Render_Pipeline pipeline = render_pipeline_create(&arena, &game.rctx, "shaders/vert.vert.spv",
                                                      "shaders/frag.frag.spv", &config);
    Vertex verts[] = {
        {.position = {.x = 0.0f, .y = -0.5f}},
        {.position = {.x = 0.5f, .y = 0.5f}},
        {.position = {.x = -0.5f, .y = 0.5f}},
    };
    u32 verts_count = 3;
    Render_Model model = {0};
    render_model_init(&game.rctx, &model, verts, verts_count);

    while (!window_should_close(game.window)) {
        process_input(game.window);
        render_begin_frame(&game.rctx);
        render_pipeline_bind(&game.rctx, &pipeline);
        render_model_bind(&game.rctx, &model);
        render_model_draw(&game.rctx, &model);
        render_end_frame(&game.rctx);
    }

    vkDeviceWaitIdle(game.rctx.logical);
    render_model_free(&game.rctx, &model);
    render_pipeline_free(&game.rctx, &pipeline);
    render_context_free(&game.rctx);
    window_free(&game.window);

    arena_free(&arena);
    return EXT_SUCCESS;
}
