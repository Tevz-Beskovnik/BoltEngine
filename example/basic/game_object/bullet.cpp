#include <bullet.hpp>

bolt::ref_ptr<bolt::TextureGL> Bullet::texture = nullptr;

Bullet::Bullet()
    : position(0, 0), velocity(0, 0)
{
    ;
}

void Bullet::setup()
{
    if(texture == nullptr)
    {
        bolt::texture_config_gl texutre_config {
            .type = bolt::TEXTURE_2D,
            .texture_location = "../example/textures/dino/Platform.png",
            .name = "Platform"
        };
        texture = bolt::TextureGL::create(texutre_config);
    }
#ifndef NDEBUG
    else
    {
        using namespace bolt;
        BOLT_LOG_WARNING("Trying to initialize bullet texture twice");
        std::cout << "Initializing bullet texture twice" << std::endl;
    }
#endif
}
    
[[nodiscard]] bolt::ref_ptr<bolt::RenderInterface> get_render_interface()
{
    
}

void Bullet::init(bolt::vector_2 position, bolt::vector_2 velocity)
{
    position = std::move(position);
    velocity = std::move(velocity);
}

void Bullet::reset()
{
    position.x = 0;
    position.y = 0;
    velocity.x = 0;
    velocity.y = 0;
}
