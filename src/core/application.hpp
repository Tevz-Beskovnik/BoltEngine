#pragma once

#include <core.hpp>
#include <util.hpp>
#include <event.hpp>
#include <application_events.hpp>
#include <layer_interface.hpp>
#include <window.hpp>

namespace bolt
{
    class Application // TODO ADD MULTIPLE WINDOWS AND A WAY TO SWITCH CONTEXT BETWEEN THEM
    {
        public:
            Application();

            virtual ~Application() = default;

            void add_layer(ref_ptr<LayerInterface> layer);

            void run() const;

            void on_event(Event& event);

            bool handleAppStop(StopAppEvent& e);

        private:
            bool running;

            std::vector<ref_ptr<LayerInterface>> layers{};
    };
}
