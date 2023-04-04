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
        .shader_location = "",
        .type = shader_type::VERTEX_SHADER
    };

    shader_config_gl s_frag {
        .shader_location = "",
        .type = shader_type::FRAGMENT_SHADER
    };

    render_config_gl r_conf = {
        .shader_config = {s_vert, s_frag},
        .texture_config = {}
        .model =
        .shader_bindings =
        .instances =
        .draw_type =
        .offset =
    };

    RGB bg(128, 78, 90);

    single_ptr<Window> window = Window::create(&w_conf);

    window->set_cackground_color(&bg);

    while(window->is_window_open())
    {
        window->window_frame_routine();
    }

    window->close();
}