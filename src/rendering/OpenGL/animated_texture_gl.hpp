#pragma once

#include <texture_exception.hpp>
#include <common_texture.hpp>
#include <primitives.hpp>
#include <util.hpp>
#include <core.hpp>
#include <texture_gl.hpp>
#include <animation.hpp>

namespace bolt
{
    struct animated_texture_config_gl
    {
        texture_type_gl type;
        ref_ptr<Animation> animation;
    };

    class AnimatedTextureGL : public CommonTextureGL {
    public:
        explicit AnimatedTextureGL(animated_texture_config_gl config);

        virtual ~AnimatedTextureGL();

        [[nodiscard]] static ref_ptr<AnimatedTextureGL> create(animated_texture_config_gl config);

        void set_animation(ref_ptr<Animation> animation);

        void bind() override;

        void bind_uniform(uint32_t program) const override;

        void unbind() override;

    private:
        void setup_texture(uint32_t tex_id, uint8_t* tex_buffer);

        void set_animation_internal();

        void bind_current_frame();

        double frame_duration;
        uint32_t current_frame;
        double previous_time;

        int32_t binding;
        texture_type_gl type;
        uint32_t* textures;
        bool new_animation;

        ref_ptr<Animation> animation;
        ref_ptr<Animation> prev_animation;

        std::mutex use_lock;
    };
}
