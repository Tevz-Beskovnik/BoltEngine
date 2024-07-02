#pragma once

#include <event.hpp>
#include <core.hpp>
#include <primitives.hpp>
#include <util.hpp>

namespace bolt
{
    enum MouseButton
    {
        RIGHT_BUTTON = GLFW_MOUSE_BUTTON_RIGHT,
        MIDDLE_BUTTON = GLFW_MOUSE_BUTTON_MIDDLE,
        LEFT_BUTTON = GLFW_MOUSE_BUTTON_LEFT,
        BUTTON_1 = GLFW_MOUSE_BUTTON_1,
        BUTTON_2 = GLFW_MOUSE_BUTTON_2,
        BUTTON_3 = GLFW_MOUSE_BUTTON_3,
        BUTTON_4 = GLFW_MOUSE_BUTTON_4,
        BUTTON_5 = GLFW_MOUSE_BUTTON_5,
        BUTTON_6 = GLFW_MOUSE_BUTTON_7,
        BUTTON_8 = GLFW_MOUSE_BUTTON_8,
        NONE = INT32_MAX
    };

    class MouseClickEvent : public Event
    {
        public:
            int button;
            int action;
            int mods;

            SETUP_EVENT_TYPE(MouseClick)

            SETUP_EVENT_CATEGORY(MouseEvent)
    };

    class MouseMoveEvent : public Event
    {
        public:
            vector_2 pos;

            SETUP_EVENT_TYPE(MouseMove)

            SETUP_EVENT_CATEGORY(MouseEvent)
    };
}