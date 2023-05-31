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
#include <window_events.hpp>
#include <event_caller.hpp>
#include <core.hpp>
#include <colors.hpp>
#include <util.hpp>
#include <keyboard_events.hpp>
#include <setup_exception.hpp>
#include <keyboard.hpp>
#include <mouse.hpp>

namespace bolt
{
    struct window_config
    {
        uint16_t width;
        uint16_t height;
        const_str title;
        bool fullscreen;
    };

    class Window
    {
        public:
            explicit Window(const window_config& config);

            ~Window();

            [[nodiscard]] static ref_ptr<Window> create(const window_config& config);

            void resize_window(uint16_t width, uint16_t height);

            void fullscreen();

            void windowed(uint16_t width, uint16_t height);

            void windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y);

            void frame_routine();

            void register_event_trigger(event_trigger trigger);

            void get_size(uint16_t *width, uint16_t *height) const;

            void cleanup_routine();

            void set_background_color(RGB* color);

            void hide_cursor() const;

            [[nodiscard]] bool is_window_open() const;

            void close();

        private:
            bool background_color_owned;
            RGB* background_color;

            event_trigger trigger;

            basic_str title;

            uint16_t width, height;

            EventCaller* caller;

            GLFWwindow* window;

            void set_active();

            void set_event_caller();
    };
}