#include <scene.hpp>

namespace bolt
{
    [[nodiscard]] const ref_ptr<RenderInterface>& Scene::get_object(uint32_t id)
    {
        return objects[id];
    }

    [[nodiscard]] uint32_t Scene::add_object(ref_ptr<RenderInterface> object)
    {
        BOLT_LOG_INFO("Creating object")
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

    void Scene::draw()
    {
        for (const auto &obj: objects)
        {
            if(obj != nullptr)
            {
                obj->render();
            }
        }
    }

    ref_ptr<Serializable> Scene::deserialize(std::string input)
    {

    }

    std::string Scene::serialize()
    {

    }
}