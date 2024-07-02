#define BOLT_LOG_FILE "C:/Users/tevzb/OneDrive/Dokumenti/BoltEngine/log"

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

    RGB bg(65, 134, 244);

    ref_ptr<Window> window = Window::create(w_conf);

    window->set_background_color(&bg);

    app.set_window(window);

    //app.add_layer(GuiLayer::create(window));

    app.add_layer(TestLayerTwo::create(window));

    //app.add_layer(GuiRenderLayer::create(window));

    //window->hide_cursor();

    camera_2d_conf camera_config = {
        .position = vector_2({
            800.0f,
            450.0f
        }),
        .size = vector_2({
            1600,
            900
        })
    };

    app.add_camera(Camera2dTest::create(camera_config));

    std::cout << "hello" << std::endl;

    app.run();

    window->close();

    return 0;
}