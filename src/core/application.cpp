//
// Created by Tevz on 15/04/2023.
//

#include <application.hpp>

namespace bolt
{
    Application::Application()
        :running(true)
    {
        ;
    }

    void Application::add_layer(ref_ptr<LayerInterface> layer)
    {
        layers.push_back(layer);
    }

    void Application::run() const
    {
        while(running)
            for(const auto& layer : layers) layer->frame();
    }

    bool Application::handleWindowClose(WindowCloseEvent& e)
    {
        running = false;

        return true;
    }

    void Application::on_event(Event& event)
    {
        BOLT_MSG_DEBUG("Dispatching event:")

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(CAST_EVENT_FUNCTION(Application::handleWindowClose));

        for(const auto& layer : layers)
        {
            if(event.handled) break;

            layer->on_event(event);
        }
    }
}
