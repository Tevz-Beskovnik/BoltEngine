#pragma once

#include <primitives.hpp>
#include <util.hpp>
#include <core.hpp>

namespace bolt
{
    class TextureGL
    {
        public:
            TextureGL();

            [[nodiscard]] static ref_ptr<TextureGL> create();

            void bind() const;

            static void unbind();

        private:
            uint32_t texture;

            uint64_t width, height;
    };
}