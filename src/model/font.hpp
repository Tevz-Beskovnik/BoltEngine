#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <texture_gl.hpp>
#include <model.hpp>

namespace bolt
{
    struct font_config
    {
        std::string font_file_path;
        std::string font_picture_path;
        float scale;
    };

    struct char_info
    {
        uint16_t id; //char id TODO: have to find what the ids of chars are
        uint32_t x; //location of start of char (topleft of the char)
        uint32_t y;
        uint32_t width; //width and height of the char
        uint32_t height;
        uint32_t xoffset; //how much to offset the char on both axis
        uint32_t yoffset;
        uint32_t xadvance; //how much to move forward to the next position to palce the character
        vector_2 UV[4]; //UVs for the letter
    };

    class Font
    {
        public:
            explicit Font(const font_config& config);

            [[nodiscard]] static ref_ptr<Font> create(const font_config& config);

            [[nodiscard]] uint16_t get_line_width() const noexcept;

            void set_line_width(int width) noexcept;

            [[nodiscard]] float get_scale() const noexcept;

            void set_scale(float scale) noexcept;

            [[nodiscard]] uint16_t get_line_height() const;

            void create_mesh(std::string text, std::vector<polygon>& mesh);

            [[nodiscard]] texture_config_gl get_texture_config() const;

        private:
            const_str font_file;
            const_str font_image;
            uint16_t image_w;
            uint16_t image_h;

            uint16_t max_line_width;
            uint16_t line_height;

            float scale;

            char_info charset[256];

            void read_character_file();

            void calculate_UV();
    };
}