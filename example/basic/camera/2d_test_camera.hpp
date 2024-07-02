#pragma once

#include <bolt.hpp>

using namespace bolt;

class Camera2dTest : public Camera2dBase {
    public:
        explicit Camera2dTest(const camera_2d_conf& config);

        [[nodiscard]] static ref_ptr<Camera2dTest> create(const camera_2d_conf& config);

        void on_event(Event& event) override;

        [[nodiscard]] bool handle_key_event(class KeyEvent& event);
};