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

            void resize_window(uint16_t width, uint16_t height) override;

            void fullscreen() override;

            void windowed(uint16_t width, uint16_t height) override;

            void windowed(uint16_t width, uint16_t height, uint16_t x, uint16_t y) override;

            void frame_routine() override;

            void cleanup_routine() override;

            void set_background_color(RGB* color) override { background_color = color; };

            void set_active() override;

            [[nodiscard]] bool should_close() override;

            void close() override;
        
        private:
            RGB* background_color{};
    };
}