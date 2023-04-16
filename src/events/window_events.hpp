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
}
