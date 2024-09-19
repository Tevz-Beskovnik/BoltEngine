#include "primitives.hpp"
#include "util.hpp"
#include <algorithm>
#include <cmath>
#include <collision.hpp>
#include <cstdlib>
#include <limits>
#include <sstream>

namespace bolt
{
    collision_info check_collision(ref_ptr<Hitbox2D> target, ref_ptr<Hitbox2D> source, vector_2 velocity)
    {
        vector_2 entry_distance;
        vector_2 exit_distance;
        vector_2 entry_time;
        vector_2 exit_time;
        std::stringstream output; 

        if (velocity.x > 0)
        {
            entry_distance.x = target->position.x - (source->position.x + source->dimensions.x); 
            exit_distance.x = (target->position.x + target->dimensions.x) - source->position.x;
        }
        else
        {
            entry_distance.x = (target->position.x + target->dimensions.x) - source->position.x;
            exit_distance.x = target->position.x - (source->position.x + source->dimensions.x); 
        }
        
        if (velocity.y > 0)
        {
            entry_distance.y = target->position.y - (source->position.y + source->dimensions.y); 
            exit_distance.y = (target->position.y + target->dimensions.y) - source->position.y; 
        }
        else
        {
            entry_distance.y = (target->position.y + target->dimensions.y) - source->position.y;
            exit_distance.y = target->position.y - (source->position.y + source->dimensions.y);
        }

        if(velocity.x == 0.0f)
        {
            entry_time.x = -std::numeric_limits<double>::infinity();
            exit_time.x = std::numeric_limits<double>::infinity();
        }
        else
        {
            entry_time.x = entry_distance.x / velocity.x;
            exit_time.x = exit_distance.x / velocity.x;
        }

        if(velocity.y == 0.0f)
        {
            entry_time.y = -std::numeric_limits<double>::infinity();
            exit_time.y = std::numeric_limits<double>::infinity();
        }
        else 
        {
            entry_time.y = entry_distance.y / velocity.y;
            exit_time.y = exit_distance.y / velocity.y;
        }

        double entry_time_s = std::max(entry_time.x, entry_time.y);
        double exit_time_s = std::min(exit_time.x, exit_time.y);

        //std::cout << entry_time_s << " " << exit_time_s << " entr: " << entry_time.x <<  " " << entry_time.y << " ext: " << exit_time.x << " " << exit_time.y << std::endl;
 
        if (entry_time_s > exit_time_s)
        {
            return collision_info {
                .collision = false,
            }; 
        }
        else // collision
        {
            auto collision = collision_info {
                .collision = true,
                .collision_time = entry_time_s
            };

            if (entry_time.x > entry_time.y)
            { // entry time for y axis is smaller so collision was on the vertical edges
                collision.face = velocity.x > 0 ? CollisionFace::RIGHT : CollisionFace::LEFT;
                return collision;
            }
            else
            {
                collision.face = velocity.y > 0 ? CollisionFace::DOWN : CollisionFace::UP;
                return collision;    
            }
        }
    }

    ref_ptr<Hitbox2D> calculate_BBB(ref_ptr<Hitbox2D> bounding_box, vector_2 velocity)
    {
        vector_2 pos;
        vector_2 dims;
  
        if(velocity.x > 0)
            pos.x = bounding_box->position.x;
        else
            pos.x = bounding_box->position.x + velocity.x;
    
        if(velocity.y > 0)
            pos.y = bounding_box->position.y;
        else
            pos.y = bounding_box->position.y + velocity.y;

        dims.x = bounding_box->dimensions.x + abs(velocity.x); 
        dims.y = bounding_box->dimensions.y + abs(velocity.y); 

        return Hitbox2D::create(pos, dims);
    }

    bool intersects_BBB(ref_ptr<Hitbox2D> BBB, ref_ptr<Hitbox2D> target)
    {
        return target->position.x < BBB->position.x + BBB->dimensions.x &&
            target->position.x + target->dimensions.x > BBB->position.x &&
            target->position.y < BBB->position.y + BBB->dimensions.y &&
            target->position.y + target->dimensions.y > BBB->position.y;
    }
}
