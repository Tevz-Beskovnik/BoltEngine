#pragma once

#include <renderer_interface.hpp>
#include <core.hpp>
#include <util.hpp>
#include <common_texture.hpp>

namespace bolt
{
    class RendererVK : public RenderInterface
    {
        public:
            ~RendererVK() override { ; };

            void add_texture(const ref_ptr<CommonTextureGL> path) override;

            void render() const override;
    };
}