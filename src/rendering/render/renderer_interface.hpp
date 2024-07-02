#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <model_interface.hpp>
#include <serializable.hpp>

namespace bolt
{
    class RenderInterface : public Serializable
    {
        public:
            virtual ~RenderInterface() { ; };

            virtual void add_texture(const std::string &path) = 0;

            virtual void add_model(const ref_ptr<ModelInterface>& model) = 0;

            virtual void add_binding_func(uniform_bindings func) = 0;

            virtual void set_viewport(vector_2 corner, vector_2 dimensions) = 0;

            virtual void render() const = 0;
    };
}