#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <util.hpp>
#include <window_interface.hpp>

namespace bolt
{
    class WindowVK : public WindowInterface
    {
        public:
            [[nodiscard]] WindowVK(uint16_t width, uint16_t height, const_str title);

            [[nodiscard]] static single_ptr<WindowVK> create(uint16_t width, uint16_t height, const_str title);

            void resize_window(uint16_t width, uint16_t height);

            void fullscreen();

            void windowed(uint16_t width, uint16_t height);

            void windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y);

            void frame_routine();

            void set_background_color(RGB* color) { background_color = color; };

            void set_active();

            [[nodiscard]] bool should_close();

            void close();
        
        private:
            RGB* background_color;
    };
}