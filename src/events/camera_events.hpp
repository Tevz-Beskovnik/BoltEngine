#pragma once

#include <event.hpp>
#include <primitives.hpp>

namespace bolt
{
    class CameraUpdate : public Event
    {
        public:
            uint32_t id;

            explicit CameraUpdate(matrix_4 view_mat, uint32_t id)
                : view_mat(view_mat), id(id)
            {
                ;
            }

            SETUP_EVENT_TYPE(CameraUpdate)

            SETUP_EVENT_CATEGORY(CameraEvent)

            [[nodiscard]] matrix_4 get_view_matrix() const
            {
                return view_mat;
            }

        private:
            matrix_4 view_mat;
    };
}