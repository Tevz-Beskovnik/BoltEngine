#pragma once

#include <core.hpp>
#include <util.hpp>
#include <event.hpp>
#include <scene.hpp>
#include <serializable.hpp>

namespace bolt
{
    class LayerInterface : public Serializable
    {
        public:
            virtual ~LayerInterface() { ; }

            virtual void frame() = 0;

            virtual void bind_event_trigger(event_trigger t) = 0;

            virtual void on_event(Event& e) const = 0;

        protected:
            Scene scene;
    };
}
