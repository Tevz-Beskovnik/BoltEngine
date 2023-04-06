#include <bolt.hpp>

using namespace bolt;

#define WIDTH 800
#define HEIGHT 600

RGB color(189, 240, 180);

void binding_func(uint32_t program)
{
    int uColor = glGetUniformLocation(program, "uColor");

    color.set_r(color.r+1);
    color.set_g(color.g+1);
    color.set_b(color.b+1);

    glUniform3f(uColor, color.r_dec, color.g_dec, color.b_dec);
}

int main()
{
    window_config w_conf = {
        .framework = OPEN_GL,
        .width = WIDTH,
        .height = HEIGHT,
        .title = "Title",
        .fullscreen = false
    };

    RGB bg(65, 134, 244);

    single_ptr<Window> window = Window::create(&w_conf);

    window->set_background_color(&bg);

    shader_config_gl s_vert {
        .shader_location = "/Users/tevz/Documents/programing/BoltEngine/example/shaders/vert.glsl",
        .type = GL_VERTEX_SHADER
    };

    shader_config_gl s_frag {
        .shader_location = "/Users/tevz/Documents/programing/BoltEngine/example/shaders/frag.glsl",
        .type = GL_FRAGMENT_SHADER
    };

    render_config_gl r_conf = {
        .shader_config = {s_vert, s_frag},
        .texture_config = {},
        .model = MeshBuilder::make_quad({-0.6f, -0.6f}, {0.5f, 0.5f})->add_model(MeshBuilder::make_quad({0.1f, 0.1f}, {0.5f, 0.5f})),//MeshBuilder::make_triangle(0.5f, -0.5f, -0.5f, -0.5f, 0.0f, 0.5f),
        .shader_bindings = binding_func,
        .instances = 1,
        .draw_type = GL_TRIANGLES,
        .offset = 0
    };

    ref_ptr<RendererGL> renderer = RendererGL::create(r_conf);

    while(window->is_window_open())
    {
        window->window_frame_routine();

        renderer->render();

        window->window_cleanup_routine();
    }

    window->close();
}