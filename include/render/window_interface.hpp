#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt 
{
    class WindowInterface
    {
        public:
            virtual void resize_window(uint16_t width, uint16_t height) { ; };

            virtual void fullscreen() { ; };

            virtual void windowed(uint16_t width, uint16_t height) { ; };

            virtual void windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y) { ; };

            virtual void frame_routine() { ; };

            virtual void set_background_color(RGB* color) { ; };

            virtual void set_active() { ; };

            virtual bool should_close() { return false; };

            virtual void close() { ; };
    };
}