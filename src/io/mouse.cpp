//
// Created by Tevz on 30/05/2023.
//

#include <mouse.hpp>

namespace bolt
{
    ManagedWindowPtr Mouse::window = nullptr;

    void Mouse::set_window(ManagedWindowPtr window)
    {
        BOLT_LOG_INFO("Window set for keyboard");
        Mouse::window = window;
    }

    [[nodiscard]] bool Mouse::left_click()
    {

    }

    [[nodiscard]] vector_2 Mouse::read_pos()
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return {static_cast<float>(x), static_cast<float>(y)};
    }
}
