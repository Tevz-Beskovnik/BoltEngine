#pragma once

#include <core.hpp>
#include <util.hpp>
#include <event.hpp>
#include <scene.hpp>

namespace bolt
{
    class LayerInterface
    {
        public:
            explicit LayerInterface(ref_ptr<Scene> scene)
                : scene(scene)
            {
                ;
            }

            LayerInterface()
                : scene(create_ref<Scene>(Scene()))
            {
                ;
            }

            virtual ~LayerInterface() { ; }

            virtual void frame() = 0;

            virtual void bind_event_trigger(event_trigger t) = 0;

            virtual void on_event(Event& e) const = 0;

            ref_ptr<Scene> get_scene()
            {
                return scene;
            }

        protected:
            ref_ptr<Scene> scene;
    };
}
