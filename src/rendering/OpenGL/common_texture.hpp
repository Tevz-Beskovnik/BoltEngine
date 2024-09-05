#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>

namespace bolt {
    class CommonTextureGL
    {
    public:
        virtual void bind() = 0;

        virtual void bind_uniform(uint32_t program) const = 0;

        virtual void unbind() = 0;

    protected:
        static uint32_t activeTexture;
    };
}
