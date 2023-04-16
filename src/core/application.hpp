#pragma once

#include <core.hpp>
#include <util.hpp>
#include <event.hpp>
#include <window_events.hpp>
#include <layer_interface.hpp>
#include <window.hpp>

namespace bolt
{
    class Application
    {
        public:
            Application();

            virtual ~Application() { ; }

            void add_layer(ref_ptr<LayerInterface> layer);

            void run() const;

            void on_event(Event& event);

            bool handleWindowClose(WindowCloseEvent& e);

        private:
            bool running;

            std::vector<ref_ptr<LayerInterface>> layers{};
    };
}
