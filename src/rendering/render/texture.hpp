#pragma once
#include "animated_texture_gl.hpp"
#include "primitives.hpp"
#include "renderer_interface.hpp"
#include "texture_gl.hpp"
#include "util.hpp"
#include <core.hpp>
#include <vector>

namespace bolt
{
    class Texture
    {
    public:
        Texture(const_str name, const_str path, vector_2 pos, vector_2 dimensions);

        static ref_ptr<Texture> create(const_str name, const_str path, vector_2 pos, vector_2 dimentions);

        ref_ptr<RenderInterface> get_renderer() const;

        vector_2 position;
        vector_2 dimensions;

    private:
        void binding_func(uint32_t program);

        TextureGL texture;

        ref_ptr<RenderInterface> renderer;
    };

    class AnimatedTexture
    {
    public:
        AnimatedTexture(const_str name, std::vector<const_str> paths, vector_2 pos, vector_2 dimensions);

        static ref_ptr<Texture> create(const_str name, const_str path, vector_2 pos, vector_2 dimensions);

        ref_ptr<RenderInterface> get_renderer() const;

        vector_2 position;
        vector_2 dimensions;
    
    private:
        AnimatedTextureGL texture;

        ref_ptr<RenderInterface> renderer;
    };
}
