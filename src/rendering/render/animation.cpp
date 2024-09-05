//
// Created by Tevz on 4. 9. 24.
//

#include <animation.hpp>

namespace bolt {
    Animation::Animation(std::vector<const_str> &frames, double duration, const_str name)
        : duration(duration), width(0), height(0), raw_frames(create_ref<std::vector<uint8_t *>>()), name(std::move(name)), file_extension("")
        {
        int32_t lWidth, lHeight;
        int32_t lBPP;
        uint8_t *buffer;

        BOLT_LOG_INFO("Loading animation: ")
        BOLT_LOG_INFO(name)

        std::filesystem::path file_path;
        for (const auto &frame: frames) {
            file_path = frame;
            stbi_set_flip_vertically_on_load(true);
            buffer = stbi_load(frame, &lWidth, &lHeight, &lBPP, 0);

            if (width == 0 && height == 0) {
                width = lWidth;
                height = lHeight;
                file_extension = file_path.extension();
            }

            if (lWidth != width || lHeight != height || file_path.extension() != file_extension)
                throw std::runtime_error("Width, height and file extension must match between all frames");

            raw_frames->push_back(buffer);
        }
    }

    [[nodiscard]] ref_ptr<Animation> Animation::create(std::vector<const_str> &frames, double duration, const_str name) {
        return create_ref<Animation>(frames, duration, name);
    }

    Animation::~Animation() {
        for (const auto &frame: *raw_frames.get()) {
            stbi_image_free(frame);
        }
    }

    void Animation::set_duration(double new_duration) {
        duration = new_duration;
    }

    double Animation::get_duration() const {
        return duration;
    }

    const_str Animation::get_name() const
    {
        return name;
    }

    std::string Animation::get_file_extension() const
    {
        return file_extension;
    }

    ref_ptr<std::vector<uint8_t*>> Animation::get_frames()
    {
        return raw_frames;
    }

    [[nodiscard]] int32_t Animation::get_width() const
    {
        return width;
    }

    [[nodiscard]] int32_t Animation::get_height() const
    {
        return height;
    }
}