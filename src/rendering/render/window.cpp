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

        if(config->fullscreen)
            framework_window->fullscreen();

        framework_window->set_active();
    }

    [[nodiscard]] ref_ptr<Window> Window::create(window_config* config)
    {
        ASSERT_NE(strlen(config->title), 0, "Title cannot be null len");
        ASSERT(!(config->height == 0 || config->width == 0), "Width and height cannot be 0");
        ASSERT((config->framework == 0 || config->framework == 1), "Invalid window framework selected");

        return create_ref<Window>(config);
    }

    void Window::set_window_dims(uint16_t new_width, uint16_t new_height)
    {
        width = new_width;
        height = new_height;

        framework_window->resize_window(width, height);
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

    void Window::register_event_trigger(event_trigger trigger)
    {
        this->trigger = trigger;
    }

    void Window::window_windowed()
    {
        framework_window->windowed(width, height);
    }

    void Window::window_fullscreen()
    {
        framework_window->fullscreen();
    }

    void Window::window_frame_routine()
    {
        framework_window->frame_routine();
    }

    void Window::window_cleanup_routine()
    {
        if(!is_window_open() && trigger != nullptr) // TODO make sure to add a away to register a callback to glfw directly
        {
            WindowCloseEvent event;

            trigger(event);
        }

        framework_window->cleanup_routine();
    }

    void Window::set_background_color(RGB* color)
    {
        framework_window->set_background_color(color);
    }

    void Window::get_size(uint16_t *set_width, uint16_t *set_height)
    {
        *set_width = width;
        *set_height = height;
    }

    [[nodiscard]] bool Window::is_window_open() const
    {
        return framework_window->should_close();
    }

    void Window::close() const
    {
        framework_window->close();
    }
}