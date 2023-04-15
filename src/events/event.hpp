#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    #define SETUP_CLASS_TYPE(type) static EventType get_static_type() { return EventType::type; } \
                                virtual Event EventType get_type() const override { return get_static_type(); }

    #define SETUP_CLASS_CATEGORY(category) static EventCategory getStaticCategory() { return EventCategory::category }

    enum EventType
    {
        KeyUp,
        KeyPress,
        WindowResize,
        WindowMove
    };

    enum EventCategory
    {
        WindowEvent = 0b1,
        KeyEvent = 0b10
    };

    class Event
    {
        public:
            virtual ~Event();

            bool handled = false;

            [[nodiscard]] virtual EventType get_type() const = 0;
    };

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
                    event.handled |= func(static_cast<T>(event));
                    return true;
                }

                return false;
            }

        private:
            Event& event;
    };
}
