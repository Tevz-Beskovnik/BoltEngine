#pragma once

#include <renderer_interface.hpp>
#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    class RendererVK : public RenderInterface
    {
        public:
            ~RendererVK() override { ; };

            void add_texture(const std::string &path) override;

            void add_shader(const std::string &path, shader_type type) override;

            void render() const override;
    };
}