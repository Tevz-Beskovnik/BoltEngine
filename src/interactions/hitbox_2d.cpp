//
// Created by Tevz on 9. 9. 24.
//

#include <hitbox_2d.hpp>

namespace bolt
{
    Hitbox2D::Hitbox2D(float x, float y, float w, float h)
        : position({x, y}), dimensions(vector_2{w,h})
    {
        calculate_center();
    }

    Hitbox2D::Hitbox2D(vector_2 position, vector_2 dimensions)
        : position(position), dimensions(dimensions)
    {
        calculate_center();
    }

    [[nodiscard]] ref_ptr<Hitbox2D> Hitbox2D::create(float x, float y, float w, float h)
    {
        return create_ref<Hitbox2D>(x, y, w, h);
    }

    [[nodiscard]] ref_ptr<Hitbox2D> Hitbox2D::create(vector_2 position, vector_2 dimensions)
    {
        return create_ref<Hitbox2D>(position, dimensions);
    }

    void Hitbox2D::set_position(float x, float y)
    {
        position = {x, y};
        calculate_center();
    }

    void Hitbox2D::set_dimensions(float w, float h)
    {
        dimensions = {w, h};
        calculate_center();
    }

    void Hitbox2D::set_position(vector_2 new_position)
    {
        position = new_position;
        calculate_center();
    }

    void Hitbox2D::set_dimensions(vector_2 new_dimensions)
    {
        dimensions = new_dimensions;
        calculate_center();
    }

    void Hitbox2D::calculate_center()
    {
        center = { position.x + (dimensions.x / 2.0f), position.y + (dimensions.y / 2.0f)};
    }

    [[nodiscard]] ref_ptr<Hitbox2D> Hitbox2D::get_minkowski(const ref_ptr<Hitbox2D> intersected) const
    {
        vector_2 new_position = this->position - (intersected->dimensions / 2.0f);
        vector_2 new_dimensions = this->dimensions + intersected->dimensions;

        return Hitbox2D::create(
            new_position,
            new_dimensions
            );
    }
}
