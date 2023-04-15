#pragma once

#include <core.hpp>
#include <util.hpp>
#include <event.hpp>
#include <layer_interface.hpp>

namespace bolt {
    class application
    {
        public:
            application();

            virtual ~application();

            void add_layer();

            void run();

            void on_event(Event& event);

        private:
            std::vector<ref_ptr<Layer>> layers;
    };
}
