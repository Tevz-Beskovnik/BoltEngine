#pragma once

#include "primitives.hpp"
#include "scene.hpp"
#include "texture_gl.hpp"
#include "util.hpp"
#include <bolt.hpp>
#include <cstdint>

class Bullet
{
public:
    Bullet();

    static void setup(bolt::ref_ptr<bolt::Scene> scene);
    
    [[nodiscard]] bolt::ref_ptr<bolt::RenderInterface> get_render_interface();

    void init(bolt::vector_2 position, bolt::vector_2 velocity);

    void reset();

private:
    static bolt::ref_ptr<bolt::TextureGL> texture;
    static bolt::ref_ptr<bolt::Scene> scene;

    uint32_t scene_id;

    bolt::vector_2 position;
    bolt::vector_2 velocity;
};
