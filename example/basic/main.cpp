#include <bolt.hpp>
#include <test_layer.hpp>

using namespace bolt;

#define WIDTH 800
#define HEIGHT 600

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

    ref_ptr<Window> window = Window::create(&w_conf);

    window->set_background_color(&bg);

    Application app;

    app.add_layer(TestLayer::create(window));

    app.run();

    window->close();

    return 0;
}