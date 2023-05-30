/**
 * GLFW window implementation for opening window
 * 
 * TODO: add ability to decide to what monitor to open, other control over opening windows to diffrent monitors, ect...
 * 
 * TODO: add possiblity for opening in wondowed mode or opening to primary monitor (current opening to primary montior)
 * 
 * TODO: reserch resource share for windows
 *
 * TODO: THROW AWAY THE WINDOW INTERFACE AND USE THIS AS DEFAULT VULKAN USES FUCKING GLFW
*/

#pragma once

#include <core.hpp>
#include <colors.hpp>
#include <util.hpp>
#include <window_interface.hpp>
#include <keyboard_events.hpp>
#include <setup_exception.hpp>
#include <keyboard.hpp>
#include <mouse.hpp>

namespace bolt
{
    class WindowGL : public WindowInterface
    {
        public:
            [[nodiscard]] WindowGL(uint16_t width, uint16_t height, const_str title);

            [[nodiscard]] static single_ptr<WindowGL> create(uint16_t width, uint16_t height, const_str title);

            void resize_window(uint16_t width, uint16_t height) override;

            void fullscreen() override;

            void windowed(uint16_t width, uint16_t height) override;

            void windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y) override;

            void frame_routine() override;

            void set_event_caller(EventCallerManagedPtr caller) override;

            void cleanup_routine() override;

            void set_background_color(RGB* color) override;

            void hide_cursor() const override;

            void set_active() override;

            [[nodiscard]] bool should_close() override;

            void close() override;
        
        private:
            bool background_color_owned;
            RGB* background_color;

            EventCallerManagedPtr caller;

            GLFWwindow* window;
    };
}