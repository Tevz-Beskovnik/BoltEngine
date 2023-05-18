//
// Created by Tevz on 15/04/2023.
//

#include <application.hpp>

namespace bolt
{
    Application::Application()
        :running(true)
    {
        LogUtil::initLogs();
    }

    void Application::add_layer(ref_ptr<LayerInterface> layer)
    {
        layers.push_back(layer);

        layer->bind_event_trigger(CAST_MEMBER_FUNCTION(Application::on_event));
    }

    void Application::run() const
    {
        while(running)
            for(const auto& layer : layers) layer->frame();
    }

    void Application::on_event(Event& event)
    {
        BOLT_MSG_DEBUG("Dispatching event:")

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<StopAppEvent>(CAST_MEMBER_FUNCTION(Application::handle_app_stop));

        for(const auto& layer : layers)
        {
            if(event.handled) break;

            layer->on_event(event);
        }
    }

    bool Application::handle_app_stop(StopAppEvent& e)
    {
        BOLT_MSG_DEBUG("Application is shutting down")

        running = false;
        return true;
    }
}
