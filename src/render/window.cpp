#include <window.hpp>

namespace bolt
{
    [[nodiscard]] Window::Window(window_config* config)
        : width(config->width), height(config->height), title((basic_str)config->title)
    {
        if(config->framework == OPEN_GL)
            framework_window = WindowGL::create(width, height, title);
        else if(config->framework == VULKAN)
            framework_window = WindowVK::create(width, height, title);

        if(config->fullscreen == true)
            framework_window->fullscreen();

        framework_window->setActive();
    }

    [[nodiscard]] single_ptr<Window> Window::create(window_config* config)
    {
        if(!validate_config(config))
            BOLT_ERROR("Window incorrectly configured!")

        return create_single<Window>(config);
    }

    [[nodiscard]] bool Window::validate_config(window_config* config)
    {
        return (strlen(config->title) != 0 && !(config->height == 0 || config->width == 0) && (config->framework == 0 || config->framework == 1));
    }

    void Window::set_window_dims(uint16_t new_width, uint16_t new_height)
    {
        width = new_width;
        height = new_height;

        framework_window->resizeWindow(width, height);
    }

    void Window::window_windowed(uint16_t x, uint16_t y, uint16_t new_width, uint16_t new_height)
    {
        width = new_width;
        height = new_height;

        framework_window->windowed(width, height, x, y);
    }

    void Window::window_windowed(uint16_t new_width, uint16_t new_height)
    {
        width = new_width;
        height = new_height;

        framework_window->windowed(width, height);
    }

    void Window::window_windowed()
    {
        framework_window->windowed(width, height);
    }

    void Window::window_fullscreen()
    {
        framework_window->fullscreen();
    }

    void Window::windowFrameRoutine()
    {
        framework_window->frameRoutine();
    }

    void Window::setBackgroundColor(RGB* color)
    {
        framework_window->setBackgroundColor(color);
    }

    void Window::get_size(uint16_t *set_width, uint16_t *set_height)
    {
        *set_width = width;
        *set_height = height;
    }

    [[nodiscard]] bool Window::isWindowOpen()
    {
        return framework_window->shouldClose();
    }

    void Window::close()
    {
        framework_window->close();
    }
}