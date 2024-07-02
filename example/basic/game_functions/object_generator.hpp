#pragma once

#include <bolt.hpp>

using namespace bolt;

ref_ptr<RenderInterface> generate_3d_grid();

void create_frames(std::vector<uint32_t>& object_frames, const std::vector<std::string>& frames, std::vector<rectangle>& collision_boxes, Scene& scene, float ar);

uint32_t create_full_frame(const std::string& texture, const rectangle& rect, Scene& scene);

uint32_t create_transparent_frame(const std::string& texture, const rectangle& rect, Scene& scene);