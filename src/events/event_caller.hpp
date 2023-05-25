#pragma once

#include <core.hpp>
#include <event.hpp>
#include <keyboard_events.hpp>
#include <window_events.hpp>

namespace bolt
{
    class EventCaller {
        public:
            explicit EventCaller(event_trigger trigger);

            void call_keyboard_event(int32_t key, int32_t scancode, int32_t action, int32_t mods) const;

            void call_window_resize_event(int width, int height) const;

            void call_window_close_event() const;

            void call_mouse_event() const;

        private:
            event_trigger trigger;
    };
}
