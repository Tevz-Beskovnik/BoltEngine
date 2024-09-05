#include <scene.hpp>

namespace bolt
{
    uint16_t Scene::id_count = 0;

    Scene::Scene()
        :id(Scene::id_count), objects(), framebuffer(nullptr)
    {
        Scene::id_count++;
    }

    [[nodiscard]] const ref_ptr<RenderInterface>& Scene::get_object(uint32_t id)
    {
        return objects[id];
    }

    [[nodiscard]] uint32_t Scene::add_object(ref_ptr<RenderInterface> object)
    {
        BOLT_LOG_INFO("Creating object")
        std::cout << "Hello!" << std::endl;
        objects.push_back(object);

        BOLT_LOG_INFO("Size of scene: ")
        BOLT_LOG_INFO(std::to_string(objects.size() - 1))

        return objects.size() - 1;
    }

    void Scene::remove(uint32_t id)
    {
        BOLT_LOG_INFO("Erasing object at id")
        objects[id] = nullptr;
    }

    void Scene::set_framebuffer(ref_ptr<FrameBufferGL> framebuffer)
    {
        this->framebuffer = framebuffer;
    }

    void Scene::draw()
    {
        if (framebuffer != nullptr)
            framebuffer->bind();

        for (const auto &obj: objects)
        {
            if(obj != nullptr)
            {
                obj->render();
            }
        }

        if (framebuffer != nullptr)
            framebuffer->unbind();
    }

    uint16_t Scene::get_id()
    {
        return id;
    }
}