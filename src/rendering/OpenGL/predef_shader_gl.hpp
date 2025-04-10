#pragma once

#include <shader_gl.hpp>
#include <sys/fcntl.h>
#include <util.hpp>
#include <core.hpp>
#include <cstddef>

#define __CHECK_SHADER_DEF(vert_var, frag_var, vert_loc, frag_loc) \
    if(vert_var == nullptr) vert_var = ShaderGL::create({ \
        .shader_location = vert_loc, \
        .type = GL_VERTEX_SHADER \
    }); \
    if(frag_var == nullptr) frag_var = ShaderGL::create({ \
        .shader_location = frag_loc, \
        .type = GL_FRAGMENT_SHADER \
    }); \
    return { vert_var, frag_var }

#define __CLEAN_VAR(var) if(var != nullptr) var = nullptr


namespace bolt
{
    class Shaders
    {
    public:
        static inline void clean()
        {
            __CLEAN_VAR(texture_vert);
            __CLEAN_VAR(indexed_texture_vert);
            __CLEAN_VAR(texture_frag);
        }
        
        static inline std::vector<ref_ptr<ShaderGL>> get_texture_shaders()
        {
            __CHECK_SHADER_DEF(texture_vert, texture_frag, "shaders/texture_pos.vert", "shaders/texture_pos.frag");
        }

        static inline std::vector<ref_ptr<ShaderGL>> get_indexed_texture_shaders()
        {
            __CHECK_SHADER_DEF(indexed_texture_vert, texture_frag, "shaders/ind_texture_pos.vert", "shaders/texture_pos.frag");
        }

    private:
        Shaders() {}
        
        // shaders
        static ref_ptr<ShaderGL> texture_vert;
        static ref_ptr<ShaderGL> indexed_texture_vert;
        static ref_ptr<ShaderGL> texture_frag;
    };
}
