#pragma once

#include <event.hpp>
#include <primitives.hpp>

namespace bolt
{
    class CameraUpdate : public Event
    {
        public:
            matrix_4 view_mat;

            SETUP_EVENT_TYPE(CameraUpdate)

            SETUP_EVENT_CATEGORY(CameraEvent)
    };
}