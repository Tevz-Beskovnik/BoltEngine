/**
 * Window class initialises spacific library and creates window to be used for rendering
 * 
 * TODO: 
 *  - BACKGROUND COLORING
 *  - EVENT POLLING
 *  - SCREEN CLEARING
*/

#pragma once

#include <core.hpp>
#include <window_interface.hpp>
#include <window_gl.hpp>
#include <window_vk.hpp>
#include <window_events.hpp>
#include <event_caller.hpp>

namespace bolt
{
    struct window_config
    {
        render_framework framework;
        uint16_t width;
        uint16_t height;
        const_str title;
        bool fullscreen;
    };

    class Window
    {
        public:
            [[nodiscard]] explicit Window(window_config* config);

            ~Window();

            [[nodiscard]] static ref_ptr<Window> create(window_config* config);

            void set_window_dims(uint16_t width, uint16_t height);

            void window_windowed(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

            void window_windowed(uint16_t width, uint16_t height);

            void register_event_trigger(event_trigger trigger);

            void window_windowed();

            void window_fullscreen();

            void window_frame_routine();

            void window_cleanup_routine();

            void set_background_color(RGB* color);

            void get_size(uint16_t *width, uint16_t *height);

            void hide_cursor() const;

            [[nodiscard]] bool is_window_open() const;

            void close() const;

        private:
            EventCallerManagedPtr caller;

            event_trigger trigger;

            basic_str title;

            uint16_t width, height;

            single_ptr<WindowInterface> framework_window;
    };
}