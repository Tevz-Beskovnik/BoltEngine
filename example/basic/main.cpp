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

    RGB bg(0, 255, 0);

    single_ptr<Window> window = Window::create(&w_conf);

    window->set_background_color(&bg);

    while(window->is_window_open())
    {
        window->window_frame_routine();
    }

    window->close();
}