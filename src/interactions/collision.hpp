#pragma once

#include "primitives.hpp"
#include <core.hpp>
#include <util.hpp>
#include <box_util.hpp>
#include <hitbox_2d.hpp>

namespace bolt
{
    enum class CollisionFace 
    {
        UP,
        DOWN,
        LEFT,
        RIGHT  
    };

    struct collision_info
    {
        bool collision;
        double collision_time;
        CollisionFace face;
    };

    ref_ptr<Hitbox2D> calculate_BBB(ref_ptr<Hitbox2D> bounding_box, vector_2 velocity);

    collision_info check_collision(ref_ptr<Hitbox2D> target, ref_ptr<Hitbox2D> source, vector_2 velocity); // TODO: make this generic

    bool intersects_BBB(ref_ptr<Hitbox2D> BBB, ref_ptr<Hitbox2D> target);
}
