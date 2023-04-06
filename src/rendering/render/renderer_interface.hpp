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

            virtual void add_texture(const std::string &path) = 0;

            virtual void set_viewport(vector_2 corner, vector_2 dimensions) = 0;

            virtual void render() const = 0;
    };
}