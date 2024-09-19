#include <renderer.hpp>

namespace bolt
{
    static double previous_time = 0;
    static uint32_t frameCount = 0;

    Renderer::Renderer(const ref_ptr<Window> window)
        :Thread(ThreadPriority::NORMAL), window(window)
    {
        ;
    }

    void Renderer::add_scene(const ref_ptr<Scene> scene)
    {
        for(const auto& scene_ptr : scenes)
        {
            if(scene->get_id() == scene_ptr->get_id())
                return;
        }

        scenes.push_back(scene);
    }

    void Renderer::set_window(const ref_ptr<bolt::Window> window)
    {
        this->window = window;
    }

    void Renderer::execute()
    {
        window->set_active();

        while(window->is_window_open())
        {
            for(const auto& scene : scenes)
            {
                window->frame_routine();
                scene->draw();
                window->cleanup_routine();
            }
        }
    }
}