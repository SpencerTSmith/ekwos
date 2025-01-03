#include "core/arena.h"
#include "core/common.h"
#include "render/render_pipeline.h"
#include "window.h"

bool g_running = true;

void process_input(Window window) {
    glfwPollEvents();

    if (glfwGetKey(window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.handle, true);
}

int main(int argc, char **argv) {
    Arena arena = arena_create(1024 * 100);

    Window window = window_create("yo", 800, 600);
    render_context_init(&arena, &window.rctx, window.handle);

    Pipeline_Config config =
        default_pipeline_config(swap_width(&window.rctx), swap_height(&window.rctx));
    Render_Pipeline pipeline =
        render_pipeline_create(&arena, &window.rctx, "./src/shaders/vert.vert.spv",
                               "./src/shaders/frag.frag.spv", &config);

    while (!window_should_close(window)) {
        process_input(window);
        render_frame(&window.rctx, &pipeline);
    }

    render_pipeline_free(&window.rctx, &pipeline);
    render_context_free(&window.rctx);
    window_free(&window);

    arena_free(&arena);
    return EXT_SUCCESS;
}
