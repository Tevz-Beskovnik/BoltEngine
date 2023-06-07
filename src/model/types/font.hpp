#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>

namespace bolt
{
    struct font_config
    {
        std::string fontFilePath;
        std::string fontPicturePath;
        int windowHeight;
        int windowWidth;
        float scale;
    };

    class Font
    {
        public:
            Font(const font_config& config);

            [[nodiscard]] ref_ptr<Font> create(const font_config& config);

            void setLineWidth(int width);

            void setScale(float scale);

        private:
            vector_2 resolution;

    };
}