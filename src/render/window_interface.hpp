#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt 
{
    class WindowInterface
    {
        public:
            virtual ~WindowInterface() { ; };

            virtual void resize_window(uint16_t width, uint16_t height) = 0;

            virtual void fullscreen() = 0;

            virtual void windowed(uint16_t width, uint16_t height) = 0;

            virtual void windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y) = 0;

            virtual void frame_routine() = 0;

            virtual void set_background_color(RGB* color) = 0;

            virtual void set_active() = 0;

            virtual bool should_close() = 0;

            virtual void close() = 0;
    };
}