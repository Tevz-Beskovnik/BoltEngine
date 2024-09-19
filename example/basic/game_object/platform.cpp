#include <platform.hpp>

std::vector<TextureSocket> Platform::texture_tiles = {
    TextureSocket {
        .left = -1,
        .right = 1,
        .tex_offset = 0,
        .tex_mirror = false
    },
    TextureSocket {
        .left = 0,
        .right = 2,
        .tex_offset = 1,
        .tex_mirror = false
    },
    TextureSocket {
        .left = 1,
        .right = -1,
        .tex_offset = 0,
        .tex_mirror = true
    },
    TextureSocket {
        .left = -1,
        .right = -1,
        .tex_offset = 4,
        .tex_mirror = false
    }
};

Platform::Platform(bolt::vector_2 position, uint16_t width)
    :position(position), width(width)
{
    sprite = bolt::TextureGL::create({
        .type = bolt::TEXTURE_2D,
        .texture_location = "../example/textures/dino/Platform.png",
        .name = "Platform"
    });



    compute_texture_offsets(width);
    compute_offsets(width);

    bolt::ObjectCreator::set_uniform_binding_func([this](uint32_t program){
        auto uRotations = glGetUniformLocation(program, "uRotations");
        auto uOffsets = glGetUniformLocation(program, "uOffsets");
        auto uTextureOffsets = glGetUniformLocation(program, "uTextureOffsets");

        glUniform1uiv(uRotations, rotations.size(), rotations_ptr);
        glUniform1fv(uOffsets, offsets.size(), offsets.data());
        glUniform1iv(uTextureOffsets, texture_offsets.size(), texture_offsets.data());
    });

    render_entity = bolt::ObjectCreator::quad({(position.x / 1600) * 2 - 1, (position.y / 900) * 2 - 1, 0.0f}, {0.06f, 0.06f * (1600.0f/900.0f)}, "../example/shaders/dino/platform.frag", "../example/shaders/dino/platform.vert");
    render_entity->add_texture(sprite);
    render_entity->set_instances(width);
}

Platform::~Platform()
{
    delete rotations_ptr;
}

[[nodiscard]] bolt::ref_ptr<bolt::Hitbox2D> Platform::get_hitbox()
{
    return bolt::Hitbox2D::create(position, {static_cast<float>(width) * 48.0f, 48.0f});
}

[[nodiscard]] bolt::ref_ptr<Platform> Platform::create(bolt::vector_2 position, uint16_t width)
{
    return bolt::create_ref<Platform>(position, width);
}

[[nodiscard]] bolt::ref_ptr<bolt::RenderInterface> Platform::get_render_interface()
{
    return render_entity;
}

void Platform::compute_offsets(uint16_t width)
{
    for(uint16_t i = 0; i < width; i++)
    {
        offsets.push_back(static_cast<float>(i) * 0.06f);
    }
}

void Platform::compute_texture_offsets(uint16_t width)
{
    uint16_t counter = 0;
    while(counter < width)
    {
        if(width == 1) {
            texture_offsets.push_back(texture_tiles[3].tex_offset);
            rotations.push_back(texture_tiles[3].tex_mirror);
            break;
        }

        if(counter == 0)
        {
            texture_offsets.push_back(texture_tiles[0].tex_offset);
            rotations.push_back(texture_tiles[0].tex_mirror);
        }
        else if(counter < width - 1)
        {
            texture_offsets.push_back(texture_tiles[1].tex_offset);
            rotations.push_back(texture_tiles[1].tex_mirror);
        }
        else
        {
            texture_offsets.push_back(texture_tiles[2].tex_offset);
            rotations.push_back(texture_tiles[2].tex_mirror);
        }

        counter++;
    }

    rotations_ptr = new uint32_t[rotations.size()];

    for(size_t i = 0; i < rotations.size(); i++)
    {
        rotations_ptr[i] = rotations[i];
    }
}