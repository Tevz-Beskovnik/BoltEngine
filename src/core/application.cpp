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

        // setup imgui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    }

    void Application::add_layer(ref_ptr<LayerInterface> layer)
    {
        layers.push_back(layer);

        layer->bind_event_trigger(CAST_MEMBER_FUNCTION(Application::on_event));
    }

    void Application::add_camera(ref_ptr<CameraBase> camera)
    {
        cameras.push_back(camera);

        camera->set_event_trigger(CAST_MEMBER_FUNCTION(Application::on_event));
    }

    void Application::run() const
    {
        while(running)
        {
            for(const auto& layer : layers) layer->frame();
            for(const auto& camera : cameras) camera->update();
        }
    }

    void Application::on_event(Event& event)
    {
        BOLT_LOG_INFO("Dispatching event:")

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<StopAppEvent>(CAST_MEMBER_FUNCTION(Application::handle_app_stop));

        for(const auto& layer : layers)
        {
            if(event.handled) break;

            layer->on_event(event);
        }

        for(const auto& camera : cameras)
        {
            if(event.handled) break;

            camera->on_event(event);
        }
    }

    bool Application::handle_app_stop(StopAppEvent& e)
    {
        BOLT_LOG_INFO("Application is shutting down")

        running = false;
        return true;
    }
}
