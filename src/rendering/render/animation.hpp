#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    class Animation
    {
    public:
        Animation(std::vector<const_str>& frames, double duration);

        [[nodiscard]] static ref_ptr<Animation> create(std::vector<const_str>& frames, double duration);

        virtual ~Animation();

        void set_duration(double new_duration);

        double get_duration() const;

        [[nodiscard]] std::string get_file_extension() const;

        [[nodiscard]] ref_ptr<std::vector<uint8_t*>> get_frames();

        [[nodiscard]] int32_t get_width() const;

        [[nodiscard]] int32_t get_height() const;

    private:
        double duration;
        int32_t width, height;
        std::string file_extension;

        ref_ptr<std::vector<uint8_t*>> raw_frames;
    };
}
