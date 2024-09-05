#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    class Animation
    {
    public:
        Animation(std::vector<const_str>& frames, double duration, const_str name);

        [[nodiscard]] static ref_ptr<Animation> create(std::vector<const_str>& frames, double duration, const_str name);

        virtual ~Animation();

        void set_duration(double new_duration);

        double get_duration() const;

        [[nodiscard]] const_str get_name() const;

        [[nodiscard]] std::string get_file_extension() const;

        [[nodiscard]] ref_ptr<std::vector<uint8_t*>> get_frames();

        [[nodiscard]] int32_t get_width() const;

        [[nodiscard]] int32_t get_height() const;

    private:
        const_str name;
        double duration;
        int32_t width, height;
        std::string file_extension;

        ref_ptr<std::vector<uint8_t*>> raw_frames;
    };
}
