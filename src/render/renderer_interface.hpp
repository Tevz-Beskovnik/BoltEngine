#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <model_interface.hpp>

namespace bolt
{
    class RenderInterface
    {
        public:
            virtual ~RenderInterface() { ; };

            virtual void set_model(ref_ptr<ModelInterface> mesh) = 0;

            virtual void add_texture(const std::string &path) = 0;

            virtual void add_shader(const std::string &path, shader_type type) = 0;

            virtual void render() const = 0;
    };
}