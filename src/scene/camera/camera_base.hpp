#pragma once

#include <event.hpp>

namespace bolt {
    class CameraBase {
    public:
        CameraBase() = default;

        virtual void update() = 0;

        virtual void on_event(Event& e) = 0;

        virtual void set_event_trigger(event_trigger trigger) = 0;
    };
}
