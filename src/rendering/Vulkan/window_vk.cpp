#include <window_vk.hpp>

namespace bolt
{
    [[nodiscard]] WindowVK::WindowVK(uint16_t width, uint16_t height, const_str title)
    {
        ;
    }

    [[nodiscard]] single_ptr<WindowVK> WindowVK::create(uint16_t width, uint16_t height, const_str title)
    {
        BOLT_MSG_DEBUG("Creating window")
        return create_single<WindowVK>(width, height, title);
    }

    void WindowVK::resize_window(uint16_t width, uint16_t height)
    {
        ;
    }

    void WindowVK::fullscreen()
    {
        ;
    }

    void WindowVK::windowed(uint16_t width, uint16_t height)
    {
        ;
    }

    void WindowVK::windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y)
    {
        ;
    }

    void WindowVK::frame_routine()
    {
        ;
    }

    void WindowVK::cleanup_routine()
    {
        ;
    }

    void WindowVK::set_active()
    {
        ;
    }

    [[nodiscard]] bool WindowVK::should_close()
    {
        return false;
    }

    void WindowVK::close()
    {
        ;
    }
}