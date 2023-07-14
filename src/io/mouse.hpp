#pragma once

#include <core.hpp>
#include <primitives.hpp>
#include <util.hpp>

namespace bolt
{
    class Mouse
    {
        public:
            Mouse() = delete;

            static void set_window(ManagedWindowPtr window);

            [[nodiscard]] static bool left_click();

            [[nodiscard]] static vector_2 read_pos();
        private:
            static ManagedWindowPtr window;
    };
}