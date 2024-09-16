#pragma once

#include <bolt.hpp>

class Player {
public:
    Player(bolt::vector_2 position);

    [[nodiscard]] static bolt::ref_ptr<Player> create(bolt::vector_2 position);

    [[nodiscard]] bolt::ref_ptr<bolt::RenderInterface> get_render_interface();

    void add_hitbox(const bolt::ref_ptr<bolt::Hitbox2D> box);

    void handle_keyboard_event(class bolt::KeyEvent &event);

    void compute(double delta_time);

protected:
    void update_player(double delta_time);

    void set_hitbox(bolt::vector_2 pos);

    static constexpr double MOVEMENT_MOD = 500;
    static constexpr double GRAVITATIONAL_ACCELERATION = 1000;
    static constexpr double MAX_SPEED = 1000;

    bolt::vector_2 position;
    bolt::vector_2 velocity;
    bolt::ref_ptr<bolt::RenderInterface> render_entity; // render entity
    std::mutex binding_lock;
    bolt::ref_ptr<bolt::Hitbox2D> player_hitbox;
    std::vector<bolt::ref_ptr<bolt::Hitbox2D>> other_hitboxes;

    // texture and sprite stuff
    bolt::ref_ptr<bolt::AnimatedTextureGL> sprite;
    bolt::ref_ptr<bolt::Animation> idle;
    bolt::ref_ptr<bolt::Animation> run;
    bool texture_rotation;

    bool grounded;
    bool a_held;
    bool d_held;
};
