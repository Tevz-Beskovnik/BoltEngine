#pragma once

#include <core.hpp>
#include <event.hpp>
#include <keyboard_events.hpp>
#include <window_events.hpp>
#include <mouse_events.hpp>

namespace bolt
{
    class EventCaller {
        public:
            explicit EventCaller(event_trigger trigger);

            void call_keyboard_event(int32_t key, int32_t scancode, int32_t action, int32_t mods) const;

            void call_window_resize_event(int width, int height) const;

            void call_window_close_event() const;

            void call_mouse_event(int button, int action, int mods) const;

            void call_mouse_position_event(double x_pos, double y_pos) const;

        private:
            event_trigger trigger;
    };
}
