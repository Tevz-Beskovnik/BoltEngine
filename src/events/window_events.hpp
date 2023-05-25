#pragma once

#include <event.hpp>
#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    class WindowCloseEvent : public Event
    {
        public:
            SETUP_EVENT_TYPE(WindowClose)

            SETUP_EVENT_CATEGORY(WindowEvent)
    };

    class WindowResizeEvent : public Event
    {
        public:
            uint32_t width;
            uint32_t height;

            SETUP_EVENT_TYPE(WindowResize)

            SETUP_EVENT_CATEGORY(WindowEvent)
    };
}
