#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt 
{
    class WindowInterface
    {
        public:
            virtual void resizeWindow(uint16_t width, uint16_t height) { ; };

            virtual void fullscreen() { ; };

            virtual void windowed(uint16_t width, uint16_t height) { ; };

            virtual void windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y) { ; };

            virtual void frameRoutine() { ; };

            virtual void setBackgroundColor(RGB* color) { ; };

            virtual void setActive() { ; };

            virtual bool shouldClose() { return false; };

            virtual void close() { ; };
    };
}