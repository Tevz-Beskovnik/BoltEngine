//
// Created by Tevz on 25/05/2023.
//

#include <event_caller.hpp>

namespace bolt
{
    EventCaller::EventCaller(event_trigger trigger)
        : trigger(trigger)
    {
        ;
    }

    void EventCaller::call_keyboard_event(int32_t key, int32_t scancode, int32_t action, int32_t mods) const
    {
        class KeyEvent event;
        event.key = key;
        event.scancode = scancode;
        event.action = action;
        event.mods = mods;

        trigger(event);
    }

    void EventCaller::call_window_resize_event(int width, int height) const
    {
        WindowResizeEvent event;
        event.width = width;
        event.height = height;

        trigger(event);
    }

    void EventCaller::call_window_close_event() const
    {
        WindowCloseEvent event;

        trigger(event);
    }

    void EventCaller::call_mouse_event() const
    {
        ;
    }
}