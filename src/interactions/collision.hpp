#pragma once

#include <core.hpp>
#include <util.hpp>
#include <box_util.hpp>
#include <hitbox_2d.hpp>

namespace bolt
{
    collision_info check_collision(ref_ptr<Hitbox2D> target, ref_ptr<Hitbox2D> source); // TODO: make this generic

    vector_2 get_resting_point_and_update_velcity(const ref_ptr<Hitbox2D> minkowski_hitbox, const ref_ptr<Hitbox2D> source, vector_2& movement);
}