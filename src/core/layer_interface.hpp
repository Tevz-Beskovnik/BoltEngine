#pragma once

#include <core.hpp>
#include <util.hpp>
#include <event.hpp>

namespace bolt
{
    class Layer
    {
        public:
            Layer();

            virtual ~Layer();

            virtual void frame() const = 0;

            virtual void on_event(Event& e) const = 0;
    };
}
