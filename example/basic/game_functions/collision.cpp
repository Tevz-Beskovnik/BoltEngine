#include <collision.hpp>

[[nodiscard]] bool intersects_rect(vector_2 pos, rectangle rect)
{
    return (pos.x >= rect.pos.x && pos.y >= rect.pos.y && pos.x <= rect.pos.x + rect.dims.x && pos.y <= rect.pos.y + rect.dims.y);
}

[[nodiscard]] int32_t intersects_rects(vector_2 pos, const std::vector<rectangle>& rects)
{
    std::cout << "Testing rects: " << pos.x << " " << pos.y << std::endl;
    for(int32_t i = 0; i < rects.size(); i++)
    {
        std::cout << rects[i].pos.x << " " << rects[i].pos.y << std::endl;
        if(intersects_rect(pos, rects[i]))
        {
            std::cout << "Found rect" << std::endl;
            return i;
        }
    }

    return -1;
}