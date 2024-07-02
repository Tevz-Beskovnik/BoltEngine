//
// Created by Tevz on 26/05/2023.
//

#include <keyboard.hpp>

namespace bolt
{
    ManagedWindowPtr Keyboard::window = nullptr;

    void Keyboard::set_window(const ManagedWindowPtr window)
    {
        BOLT_LOG_INFO("Window set for keyboard");
        Keyboard::window = window;
    }

    [[nodiscard]] bool Keyboard::is_key_held(Key key)
    {
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
        int state = glfwGetKey(window, key);
        if(state == GLFW_PRESS)
            return true;
        else
            return false;
    }

    [[nodiscard]] bool Keyboard::is_key_toggled(Key key)
    {
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
        int state = glfwGetKey(window, key);
        if(state == GLFW_PRESS)
            return true;
        else
            return false;
    }

    [[nodiscard]] bool Keyboard::is_key_pressed(Key key)
    {
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    }
}