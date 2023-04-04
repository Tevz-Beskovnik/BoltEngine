#pragma once

#include <core.hpp>
#include <primitives.hpp>
#include <util.hpp>
#include <renderer_interface.hpp>
#include <renderer_gl.hpp>
#include <renderer_vk.hpp>

namespace bolt
{
    class Entity
    {
        public:
            [[nodiscard]] bool is_renderable();

            void set_renderer(ref_ptr<RenderInterface> renderer);

            virtual void update_pre() const = 0;

            virtual void update_after() const = 0;

            void entity_cycle();

            void render();

        protected:
            bool renderable;
            ref_ptr<RenderInterface> renderer;

    };
}