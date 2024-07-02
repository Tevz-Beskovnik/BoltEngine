#pragma once

#include <core.hpp>
#include <event.hpp>

namespace bolt
{
    class KeyEvent : public Event
    {
        public:
            int32_t key;
            int32_t scancode;
            int32_t action;
            int32_t mods;

            SETUP_EVENT_TYPE(KeyPress)

            SETUP_EVENT_CATEGORY(KeyEvent)
    };
}