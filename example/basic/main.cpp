#include <bolt.hpp>
#include <test_layer_two.hpp>
#include <2d_test_camera.hpp>
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

    //app.add_layer(GuiLayer::create(window));

    app.add_layer(TestLayerTwo::create(window));

    //app.add_layer(GuiRenderLayer::create(window));
    std::cout << "hello" << std::endl;

    //window->hide_cursor();

    std::cout << "hello" << std::endl;

    camera_2d_conf camera_config = {
        .position = vector_2({
                                 0.0f,
                                 0.0f
                             }),
        .size = vector_2({
                             800,
                             600
                         })
    };

    app.add_camera(Camera2dTest::create(camera_config));

    std::cout << "hello" << std::endl;

    app.run();

    window->close();

    return 0;
}