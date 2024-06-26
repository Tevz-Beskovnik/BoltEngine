#pragma once

#include <core.hpp>
#include <util.hpp>
#include <event.hpp>

namespace bolt
{
    class LayerInterface
    {
        public:
            virtual ~LayerInterface() { ; }

            virtual void frame() const = 0;

            virtual void bind_event_trigger(event_trigger t) = 0;

            virtual void on_event(Event& e) const = 0;
    };
}
