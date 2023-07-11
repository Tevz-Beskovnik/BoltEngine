#include <scene.hpp>

namespace bolt
{
    [[nodiscard]] const ref_ptr<RenderInterface>& Scene::get_object(uint32_t id)
    {
        return objects[id];
    }

    [[nodiscard]] uint32_t Scene::add_object(const ref_ptr<RenderInterface> &object)
    {
        objects.push_back(object);

        return objects.size() - 1;
    }

    void Scene::remove(uint32_t id)
    {
        objects[id] = nullptr;
    }

    void Scene::draw()
    {
        for (const auto &obj: objects)
        {
            if(obj == nullptr)
            {
                obj->render();
            }
        }
    }
}