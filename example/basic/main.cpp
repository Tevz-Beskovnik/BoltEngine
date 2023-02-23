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

    RGB bg(128, 78, 90);

    single_ptr<Window> window = Window::create(&w_conf);

    window->setBackgroundColor(&bg);

    while(window->isWindowOpen())
    {
        window->windowFrameRoutine();
    }

    window->close();
}