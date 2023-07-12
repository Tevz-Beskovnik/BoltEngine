#pragma once

#include <core.hpp>
#include <util.hpp>
#include <event.hpp>
#include <application_events.hpp>
#include <layer_interface.hpp>
#include <window.hpp>
#include <camera_base.hpp>

namespace bolt
{
    class Application // TODO ADD MULTIPLE WINDOWS AND A WAY TO SWITCH CONTEXT BETWEEN THEM
    {
        public:
            Application();

            explicit Application(const ref_ptr<Window>& window);

            void set_window(const ref_ptr<bolt::Window> &window);

            virtual ~Application() = default;

            void add_layer(ref_ptr<LayerInterface> layer);

            void add_camera(ref_ptr<CameraBase> camera);

            void run() const;

            void on_event(Event& event);

            bool handle_app_stop(StopAppEvent& e);

        private:
            bool running;

            ref_ptr<Window> window;

            std::vector<ref_ptr<LayerInterface>> layers{};

            std::vector<ref_ptr<CameraBase>> cameras{};
    };
}
