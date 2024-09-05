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
            double current_time = glfwGetTime();
            // Measure speed
            frameCount++;
            // If a second has passed.
            if ( current_time - previous_time >= 1.0 )
            {
                // Display the frame count here any way you want.
                std::cout << frameCount << std::endl;

                frameCount = 0;
                previous_time = current_time;
            }

            //std::cout << "rendering" << std::endl;
            for(const auto& scene : scenes)
            {
                window->frame_routine();
                scene->draw();
                window->cleanup_routine();
            }
        }
    }
}