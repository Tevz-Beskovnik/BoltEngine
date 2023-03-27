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

            virtual void setModel(ref_ptr<ModelInterface> mesh) = 0;

            virtual void addTexture(const std::string &path) = 0;

            virtual void addShader(const std::string &path, shader_type type) = 0;

            virtual void render() const = 0;
    };
}