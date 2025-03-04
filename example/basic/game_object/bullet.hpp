#pragma once

#include "primitives.hpp"
#include <bolt.hpp>

class Bullet
{
public:
    Bullet();

    static void setup();
    
    [[nodiscard]] bolt::ref_ptr<bolt::RenderInterface> get_render_interface();

    void init(bolt::vector_2 position, bolt::vector_2 velocity);

    void reset();

private:
    static bolt::ref_ptr<bolt::TextureGL> texture;
    bolt::ref_ptr<bolt::RenderInterface> render_entity; // render entity

    bolt::vector_2 position;
    bolt::vector_2 velocity;
};
