#include <bolt.hpp>
#include <gui_layer.hpp>
#include <test_layer_two.hpp>
#include <test_camera.hpp>
#include <gui_render_layer.hpp>
#include <iostream>

using namespace bolt;

#define WIDTH 1600
#define HEIGHT 900

int main() // todo start handeling exceptions
{
    Application app;

    window_config w_conf = {
        .width = WIDTH,
        .height = HEIGHT,
        .title = "Title",
        .fullscreen = false
    };

    std::cout << "hello" << std::endl;

    RGB bg(65, 134, 244);

    std::cout << "hello" << std::endl;

    ref_ptr<Window> window = Window::create(w_conf);

    std::cout << "hello" << std::endl;

    window->set_background_color(&bg);

    app.set_window(window);

    app.add_layer(GuiLayer::create(window));

    app.add_layer(TestLayerTwo::create(window));

    app.add_layer(GuiRenderLayer::create(window));
    std::cout << "hello" << std::endl;

    //window->hide_cursor();

    std::cout << "hello" << std::endl;

    app.add_camera(TestCamera::create(WIDTH, HEIGHT));

    std::cout << "hello" << std::endl;

    app.run();

    window->close();

    return 0;
}