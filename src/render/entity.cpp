#include <entity.hpp>

namespace bolt {
    [[nodiscard]] bool Entity::is_renderable()
    {
        return renderable;
    }

    void Entity::set_renderer(ref_ptr<RenderInterface> renderer)
    {
        this->renderer = renderer;
    }

    void Entity::entity_cycle()
    {
        update_pre();

        if(renderable)
            renderer->render();

        update_after();
    }

    void Entity::render()
    {
        if(renderable)
            renderer->render();
    }
}