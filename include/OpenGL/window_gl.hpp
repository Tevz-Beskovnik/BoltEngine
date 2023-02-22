/**
 * GLFW window implementation for opening window
 * 
 * TODO: add ability to decide to what monitor to open, other control over opening windows to diffrent monitors, ect...
 * 
 * TODO: add possiblity for opening in wondowed mode or opening to primary monitor (current opening to primary montior)
 * 
 * TODO: reserch resource share for windows
*/

#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <util.hpp>
#include <window_interface.hpp>

namespace bolt
{
    class WindowGL : public WindowInterface
    {
        public:
            [[nodiscard]] WindowGL(uint16_t width, uint16_t height, const_str title);

            [[nodiscard]] static single_ptr<WindowGL> create(uint16_t width, uint16_t height, const_str title);

            void resize_window(uint16_t width, uint16_t height);

            void fullscreen();

            void windowed(uint16_t width, uint16_t height);

            void windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y);

            void frame_routine();

            void set_background_color(RGB* color);

            void set_active();

            [[nodiscard]] bool should_close();

            void close();
        
        private:
            bool background_color_owned;
            RGB* background_color;

            GLFWwindow* window;
    };
}