#include <bolt.hpp>

using namespace bolt;

int main()
{
    window_config w_conf = {
        .framework = OPEN_GL,
        .width = 800,
        .height = 600,
        .title = "Title",
        .fullscreen = false
    };

    shader_config_gl s_vert {
        .shader_location = "/Users/tevz/Documents/programing/BoltEngine/example/shaders/vert.glsl",
        .type = shader_type::VERTEX_SHADER
    };

    shader_config_gl s_frag {
        .shader_location = "/Users/tevz/Documents/programing/BoltEngine/example/shaders/frag.glsl",
        .type = shader_type::FRAGMENT_SHADER
    };

    render_config_gl r_conf = {
        .shader_config = {s_vert, s_frag},
        .texture_config = {},
        .model = MeshBuilder::make_quad({-0.5, -0.5}, {1.0f, 1.0f}),
        .shader_bindings = nullptr,
        .instances = 1,
        .draw_type = GL_STATIC_DRAW,
        .offset = 0
    };

    RGB bg(128, 78, 90);

    single_ptr<Window> window = Window::create(&w_conf);

    window->set_cackground_color(&bg);

    ref_ptr<RendererGL> renderer = RendererGL::create(r_conf);

    while(window->is_window_open())
    {
        window->window_frame_routine();

        renderer->render();
    }

    window->close();
}