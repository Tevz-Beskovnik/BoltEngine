#pragma once

#include <util.hpp>
#include <event.hpp>

namespace bolt
{
    class StopAppEvent : public Event
    {
        public:
            SETUP_EVENT_TYPE(AppStop)

            SETUP_EVENT_CATEGORY(AppEvent)
    };
}