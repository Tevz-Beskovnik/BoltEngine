#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    #define SETUP_EVENT_TYPE(type) static EventType get_static_type() { return EventType::type; } \
                                    virtual EventType get_type() const override { return get_static_type(); }

    #define SETUP_EVENT_CATEGORY(category) static EventCategory getStaticCategory() { return EventCategory::category; }

    enum EventType
    {
        KeyUp,
        KeyPress,
        AppStop,
        MouseClick,
        MouseMove,
        WindowClose,
        WindowResize,
        WindowMove
    };

    enum EventCategory
    {
        WindowEvent = 0b1,
        KeyEvent = 0b10,
        AppEvent = 0b100
    };

    class Event
    {
        public:
            Event() { ; }

            virtual ~Event() = default;

            bool handled = false;

            [[nodiscard]] virtual EventType get_type() const = 0;
    };

    typedef std::function<void(Event&)> event_trigger;

    class EventDispatcher
    {
        public:
            explicit EventDispatcher(Event& event)
                : event(event)
            {
                ;
            }

            template<typename T, typename F>
            bool dispatch(const F& func)
            {
                if(event.get_type() == T::get_static_type())
                {
                    event.handled |= func(static_cast<T&>(event));
                    return true;
                }

                return false;
            }

        private:
            Event& event;
    };
}
