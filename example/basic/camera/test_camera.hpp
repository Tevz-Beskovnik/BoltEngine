#pragma once

#include <bolt.hpp>

using namespace bolt;

class TestCamera : public CameraBase
{
    public:
        explicit TestCamera(uint16_t w, uint16_t h);

        ~TestCamera() override = default;

        [[nodiscard]] static ref_ptr<TestCamera> create(uint16_t w, uint16_t h);

        void update() override;
};