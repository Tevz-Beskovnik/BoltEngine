#pragma once

#include <bolt.hpp>

using namespace bolt;

[[nodiscard]] bool intersects_rect(vector_2 pos, rectangle rect);

[[nodiscard]] uint32_t intersects_rects(vector_2 pos, const std::vector<rectangle>& rects);