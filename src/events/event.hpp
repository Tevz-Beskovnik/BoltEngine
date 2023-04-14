#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    enum EventType
    {

    };

    enum EventCategory
    {

    };

    class Event
    {
        public:
            virtual ~Event();

            bool handled = false;

            [[nodiscard]] virtual EventType getType() const = 0;
            [[nodiscard]] virtual EventCategory getCategory() const = 0;

            [[nodiscard]] bool isInCategory(EventCategory category) const
            {
                return getCategory() & category;
            }

            [[nodiscard]] bool isType(EventType type) const
            {

            }
    };

    class EventDispatcher
    {

    };
}
