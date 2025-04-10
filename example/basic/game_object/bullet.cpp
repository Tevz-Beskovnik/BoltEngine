#include "texture_gl.hpp"
#include "util.hpp"
#include <bullet.hpp>

bolt::ref_ptr<bolt::TextureGL> Bullet::texture = nullptr;
bolt::ref_ptr<bolt::Scene> Bullet::scene = nullptr;

Bullet::Bullet()
    : position(0, 0), velocity(0, 0)
{
    ;
}

void Bullet::setup(bolt::ref_ptr<bolt::Scene> scene)
{
    bolt::texture_config_gl config = {
        .type = bolt::TEXTURE_2D,
        .texture_location = "../example/textures/color-frame-red.png",
        .name = "Bullet"
    };

    texture = bolt::TextureGL::create(config);
}
    
[[nodiscard]] bolt::ref_ptr<bolt::RenderInterface> Bullet::get_render_interface()
{
    return NULL;//bolt::create_ref<bolt::RenderInterface>();
}

void Bullet::init(bolt::vector_2 position, bolt::vector_2 velocity)
{
    position = position;
    velocity = velocity;
}

void Bullet::reset()
{
    position.x = 0;
    position.y = 0;
    velocity.x = 0;
    velocity.y = 0;
    scene_id = 0;
}

