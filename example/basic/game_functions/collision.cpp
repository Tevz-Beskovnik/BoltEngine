#include <collision.hpp>

[[nodiscard]] inline bool intersects_rect(vector_2 pos, rectangle rect)
{
    return (pos.x >= rect.pos.x && pos.y >= rect.pos.y && pos.x <= rect.pos.x + rect.dims.x && pos.y <= rect.pos.y + rect.dims.y);
}

[[nodiscard]] inline uint32_t intersects_rects(vector_2 pos, std::vector<rectangle> rects)
{
    for(uint32_t i = 0; i < rects.size(); i++)
    {
        if(intersects_rect(pos, rects[i]))
        {
            return i;
        }
    }
}