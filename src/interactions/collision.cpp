#include <collision.hpp>

namespace bolt
{
    collision_info check_collision(ref_ptr<Hitbox2D> target, ref_ptr<Hitbox2D> source)
    {
        auto minkowski_hitbox = target->get_minkowski(source);
        /*std::cout << "center: " << source->center.x <<  " " << source->center.y << " minow: "
            << minkowski_hitbox->position.x << " " << minkowski_hitbox->position.y << " dim: " << minkowski_hitbox->dimensions.x + minkowski_hitbox->position.x
            << " " << minkowski_hitbox->dimensions.y + minkowski_hitbox->position.y << std::endl;*/
        return collision_info{
            .collision = minkowski_hitbox->position.x < source->center.x &&
                         minkowski_hitbox->position.y < source->center.y &&
                         minkowski_hitbox->position.y + minkowski_hitbox->dimensions.y > source->center.y &&
                         minkowski_hitbox->position.x + minkowski_hitbox->dimensions.x > source->center.x,
            .minkowski_hitbox = minkowski_hitbox
        };
    }

    vector_2 calculate_intersection(vector_2 r1, vector_2 n, vector_2 r0, vector_2 s)
    {
        double a1 = n.y;
        double b1 = -n.x;
        double c1 = n.y*r1.x - r1.y*n.x;

        double a2 = s.y;
        double b2 = -s.x;
        double c2 = s.y*r0.x - r0.y*s.x;

        std::cout << "Dir vectors n: " << n.x << " " << n.y << " s: " << s.x << " " << s.y << std::endl;
        std::cout << "Point: " << r1.x << " " << r1.y << std::endl;

        auto devisor = (a1 * b2 - b1 * a2);
        float x = ((c1 * b2 - b1 * c2) / devisor); // r0 is the collision source;
        /*if(devisor != 0)
        {
            x =
            std::cout << "devisor ne 0" << std::endl;
        }
        else
        {
            x = r0.x;
            std::cout << "devisor eq 0" << std::endl;
        }*/
        auto y = (float)((c1 * a2 - a1 * c2) / devisor);

        std::cout << "New point: " << x << " " << y << std::endl;

        return { x, y };
    }

    vector_2 get_resting_point_and_update_velcity(const ref_ptr<Hitbox2D> minkowski_hitbox, const ref_ptr<Hitbox2D> source, vector_2& movement)
    {
        vector_2 overlap;
        vector_2 dir;
        vector_2 point;
        vector_2 normal_dir = movement.normalize();
        std::cout << "normal dir: " << normal_dir.x << " " << normal_dir.y << std::endl;
        float mult;

        float left = abs(source->center.x - minkowski_hitbox->position.x);
        float right = abs(minkowski_hitbox->position.x + minkowski_hitbox->dimensions.x - source->center.x);
        float bottom = abs(source->center.y - minkowski_hitbox->position.y);
        float top = abs(minkowski_hitbox->position.y + minkowski_hitbox->dimensions.y - source->center.y);
        overlap.x = std::min(left, right);
        overlap.y = std::min(bottom, top);

        if (abs(overlap.y) < abs(overlap.x))
        {
            dir = {1, 0};
            if (top < bottom)
            {
                std::cout << "top";
                mult = overlap.y / normal_dir.y;
            }
            else
            {
                std::cout << "bottom";
                mult = overlap.y / normal_dir.y;
            }
        } else {
            dir = { 0 , 1};
            if (right < left)
            {
                std::cout << "right";
                mult = overlap.x / normal_dir.x;
            }
            else
            {
                std::cout << "left";
                mult = overlap.x / normal_dir.x;
            }
        }

        /*if (
            minkowski_hitbox->position.x < source->center.x &&
            minkowski_hitbox->position.x + minkowski_hitbox->dimensions.x > source->center.x
            )
        {
            dir = { 1, 0};
            if (minkowski_hitbox->position.y < source->center.y)
                // collision was ontop
                point = {minkowski_hitbox->position.x, minkowski_hitbox->position.y + minkowski_hitbox->dimensions.y};
            else
                // collision was on the bottom
                point = {minkowski_hitbox->position.x, minkowski_hitbox->position.y};
        }
        else {
            dir = { 0, 1};
            if (minkowski_hitbox->position.x < source->center.x)
                // on right
                point = {minkowski_hitbox->position.x + minkowski_hitbox->dimensions.x, minkowski_hitbox->position.y};
            else
                // on left
                point = {minkowski_hitbox->position.x, minkowski_hitbox->position.y};
        }*/

        std::cout << mult << std::endl;
        vector_2 new_pos = (source->center + normal_dir * mult) - (source->dimensions / 2.0f);
        //vector_2 out = calculate_intersection(point, dir, source->center, movement) - (source->dimensions / 2.0f);

        movement.x *= dir.x;
        movement.y *= dir.y;

        std::cout << new_pos.x << " " << new_pos.y << std::endl;

        return new_pos  ;
    }
}