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
        return line_width;
    }

    void Font::set_line_width(int width) noexcept
    {
        line_width = width;
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

    void Font::set_line_height(uint16_t lineHeight)
    {
        line_height = lineHeight;
    }

    [[nodiscard]] std::vector<polygon> Font::create_mesh(const std::string& text)
    {

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

            std::stringstream s;
            s << line;

            char c_;
            std::string s_;

            if (line[0] == 'c' && line[1] == 'o')
            {
                s >> s_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> line_height;
                s >> s_;
                s >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> image_w; //width of the font sprite
                s >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> image_h; //height of the font sprite
            }

            uint16_t id;

            if (line[0] == 'c' && line[1] == 'h' && line[4] != 's')
            {
                s >> s_ >> c_ >> c_ >> c_ >> id;
                charset[id].id = id;
                s >> c_ >> c_ >> charset[id].x;
                s >> c_ >> c_ >> charset[id].y;
                s >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].width;
                s >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].height;
                s >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].xoffset;
                s >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].yoffset;
                s >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> c_ >> charset[id].xadvance;
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