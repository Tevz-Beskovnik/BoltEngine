#include <font.hpp>

namespace bolt
{
    Font::Font(const font_config& config)
        : font_file(config.font_file_path.c_str()), font_image(config.font_picture_path.c_str()), scale(config.scale)
    {
        BOLT_LOG_INFO(std::string("Creating new font: ") + config.font_file_path)
        for(auto& character : charset)
            character.id = 0xff;

        read_character_file();
        calculate_UV();
    }

    [[nodiscard]] ref_ptr<Font> Font::create(const font_config& config)
    {
        return create_ref<Font>(config);
    }

    [[nodiscard]] uint16_t Font::get_line_width() const noexcept
    {
        return max_line_width;
    }

    void Font::set_line_width(int width) noexcept
    {
        max_line_width = width;
    }

    [[nodiscard]] float Font::get_scale() const noexcept
    {
        return scale;
    }

    void Font::set_scale(float scale) noexcept
    {
        this->scale = scale;
    }

    uint16_t Font::get_line_height() const
    {
        return line_height;
    }

    void Font::create_mesh(std::string text, std::vector<polygon>& mesh)
    {
        uint32_t line_width = 0; // current line width
        vector_2 cursorPos = {0.0f, 0.0f}; //cursor positon

        std::reverse(text.begin(), text.end());

        for(const auto& character : text)
        {
            char_info* current_character = charset + character;

            if (line_width + current_character->xadvance > max_line_width)
            {
                cursorPos.y -= static_cast<float>(line_height);
                line_width = 0;
            }

            vector_3 vert1 = { // bottom left
                    cursorPos.x + static_cast<float>(current_character->xoffset),
                    cursorPos.y,
                    0.0f
            };

            vector_3 vert2 = { // top left
                    cursorPos.x + static_cast<float>(current_character->xoffset),
                    cursorPos.y + 71.0f - static_cast<float>(current_character->yoffset),
                    0.0f
            };

            vector_3 vert3 = { // top right
                    cursorPos.x + static_cast<float>(current_character->xadvance),
                    cursorPos.y + 71.0f - static_cast<float>(current_character->yoffset),
                    0.0f
            };

            vector_3 vert4 = { // bottom right
                    cursorPos.x + static_cast<float>(current_character->xadvance),
                    cursorPos.y,
                    0.0f
            };

            vert1 *= scale;
            vert2 *= scale;
            vert3 *= scale;
            vert4 *= scale;

            mesh.push_back(polygon{
                { vert3, vert1, vert4 }, { current_character->UV[3], current_character->UV[0], current_character->UV[2] }, { 0.0f, 0.0f, 0.0f }
            });

            mesh.push_back(polygon{
                { vert3, vert2, vert1 }, { current_character->UV[3], current_character->UV[1], current_character->UV[0] }, { 0.0f, 0.0f, 0.0f }
            });
        }
    }

    [[nodiscard]] texture_config_gl Font::get_texture_config() const
    {
        return texture_config_gl{
            .type = TEXTURE_2D,
            .texture_location = font_image
        };
    }

    void Font::read_character_file()
    {
        std::ifstream f(font_file);
        if (!f.is_open())
            return;

        while (!f.eof())
        {
            char line[256];
            f.getline(line, 256);

            std::stringstream stream;
            stream << line;

            char c_;
            std::string s_;

            if (line[0] == 'c' && line[1] == 'o')
            {
                stream >> s_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> line_height;
                stream >> s_;
                stream >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> image_w; //width of the font sprite
                stream >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> image_h; //height of the font sprite
            }

            uint16_t id;

            if (line[0] == 'c' && line[1] == 'h' && line[4] != 's')
            {
                stream >> s_ >> c_ >> c_ >> c_ >> id;
                charset[id].id = id;
                stream >> c_ >> c_ >> charset[id].x;
                stream >> c_ >> c_ >> charset[id].y;
                stream >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].width;
                stream >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].height;
                stream >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].xoffset;
                stream >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].yoffset;
                stream >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].xadvance;
            }
        }
    }

    void Font::calculate_UV()
    {
        for(auto& character : charset)
        {
            if(character.id == 0xff) continue;
            
            character.UV[2] = { (float)character.x / (float)image_w, 1.0f - ((float)character.y + (float)character.height ) / (float)image_h }; // bottom left
            character.UV[3] = { (float)character.x / (float)image_w, 1.0f - (float)character.y / (float)image_w }; // top left
            character.UV[0] = { ((float)character.x + (float)character.width) / (float)image_w, 1.0f - ((float)character.y + (float)character.height) / (float)image_h }; // bottom right
            character.UV[1] = { ((float)character.x + (float)character.width) / (float)image_w, 1.0f - (float)character.y / (float)image_h}; // top right
        }
    }
}