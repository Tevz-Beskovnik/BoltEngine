#pragma once

#include <core.hpp>
#include <util.hpp>
#include <primitives.hpp>
#include <box_util.hpp>

// Todo implement hitboxes for not only rectangles (currently i don't need polygons)
namespace bolt {
    class Hitbox2D;

    struct collision_info {
        bool collision;
        ref_ptr<Hitbox2D> minkowski_hitbox;
    };

    class Hitbox2D {
    public:
        Hitbox2D(float x, float y, float w, float h);

        Hitbox2D(vector_2 position, vector_2 dimensions);

        [[nodiscard]] static ref_ptr<Hitbox2D> create(float x, float y, float w, float h);

        [[nodiscard]] static ref_ptr<Hitbox2D> create(vector_2 position, vector_2 dimensions);

        void set_position(float x, float y);

        void set_dimensions(float w, float h);

        void set_position(vector_2 new_position);

        void set_dimensions(vector_2 new_dimensions);

        [[nodiscard]] ref_ptr<Hitbox2D> get_minkowski(const ref_ptr<Hitbox2D> intersected) const;

        vector_2 center;
        vector_2 position;
        vector_2 dimensions;

    protected:
        void calculate_center();
    };
};
