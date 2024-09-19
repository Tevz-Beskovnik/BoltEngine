#pragma once

#include <bolt.hpp>

struct TextureSocket {
    int8_t left;
    int8_t right;
    int32_t tex_offset;
    bool tex_mirror;
};

class Platform {
public:
    Platform(bolt::vector_2 position, uint16_t width);

    ~Platform();

    [[nodiscard]] bolt::ref_ptr<bolt::Hitbox2D> get_hitbox();

    [[nodiscard]] static bolt::ref_ptr<Platform> create(bolt::vector_2 position, uint16_t width);

    [[nodiscard]] bolt::ref_ptr<bolt::RenderInterface> get_render_interface();

protected:
    void compute_offsets(uint16_t width);

    void compute_texture_offsets(uint16_t width);

    static std::vector<TextureSocket> texture_tiles;

    uint16_t width;
    bolt::vector_2 position;
    bolt::ref_ptr<bolt::TextureGL> sprite;
    bolt::ref_ptr<bolt::RenderInterface> render_entity;

    std::vector<float> offsets;
    std::vector<int32_t> texture_offsets;
    std::vector<bool> rotations;

    uint32_t* rotations_ptr;
};
