//
// Created by Tevz on 5. 9. 24.
//

#include <player.hpp>

Player::Player(bolt::vector_2 position)
    :position(position), velocity({0, 0}), grounded(false)
{
    std::vector<bolt::const_str> idle_frames = {
        "../example/textures/dino/DinoIdle1.png",
        "../example/textures/dino/DinoIdle2.png",
        "../example/textures/dino/DinoIdle3.png",
        "../example/textures/dino/DinoIdle4.png"
    };

    std::vector<bolt::const_str> run_frames = {
        "../example/textures/dino/DinoRun1.png",
        "../example/textures/dino/DinoRun2.png",
        "../example/textures/dino/DinoRun3.png",
        "../example/textures/dino/DinoRun4.png",
        "../example/textures/dino/DinoRun5.png",
        "../example/textures/dino/DinoRun6.png"
    };

    idle = bolt::Animation::create(idle_frames, 0.4);
    run = bolt::Animation::create(run_frames, 0.6);
    sprite = bolt::AnimatedTextureGL::create({
        .type = bolt::TEXTURE_2D,
        .animation = idle,
        .name = "Dino"
    });

    bolt::ObjectCreator::set_uniform_binding_func([this](int32_t program) {

        static bolt::vector_2 translationVector = {0.0f, 0.0f};
        auto uTranslationVec = glGetUniformLocation(program, "uTranslation");
        auto uRotation = glGetUniformLocation(program, "uRotation");

        binding_lock.lock();
        translationVector.x = (this->position.x/1600)*2-1;
        translationVector.y = (this->position.y/900)*2-1;

        glUniform1ui(uRotation, (uint32_t)texture_rotation);
        binding_lock.unlock();
        glUniform2f(uTranslationVec, translationVector.x, translationVector.y);
    });

    player_hitbox = bolt::Hitbox2D::create(
        { position.x + 16.0f, position.y + 12.0f},
        { 60.0f, 68.0f}
    );

    render_entity = bolt::ObjectCreator::quad({0.0f, 0.0f, 0.0f}, {0.12f, 0.12f * (1600.0f/900.0f)}, "../example/shaders/dino/dino.frag", "../example/shaders/dino/dino.vert");

    render_entity->add_texture(sprite);
}

[[nodiscard]] bolt::ref_ptr<Player> Player::create(bolt::vector_2 position)
{
    return bolt::create_ref<Player>(position);
}

[[nodiscard]] bolt::ref_ptr<bolt::RenderInterface> Player::get_render_interface()
{
    return render_entity;
}

void Player::handle_keyboard_event(class bolt::KeyEvent &event)
{
    switch(event.key) {
        case bolt::Key::A:
        {
            if(event.action == GLFW_PRESS) {
                if(!d_held)
                {
                    sprite->set_animation(run);
                    binding_lock.lock();
                    texture_rotation = true;
                    binding_lock.unlock();
                }
                else
                    sprite->set_animation(idle);
                a_held = true;
            } else if(event.action == GLFW_RELEASE) {
                if(d_held)
                {
                    sprite->set_animation(run);
                    binding_lock.lock();
                    texture_rotation = false;
                    binding_lock.unlock();
                }
                else
                    sprite->set_animation(idle);
                a_held = false;
            }
            break;
        }
        case bolt::Key::D:
        {
            if(event.action == GLFW_PRESS) {
                if(!a_held)
                {
                    sprite->set_animation(run);
                    binding_lock.lock();
                    texture_rotation = false;
                    binding_lock.unlock();
                }
                else
                    sprite->set_animation(idle);
                d_held = true;
            } else if(event.action == GLFW_RELEASE) {
                if(a_held)
                {
                    sprite->set_animation(run);
                    binding_lock.lock();
                    texture_rotation = true;
                    binding_lock.unlock();
                }
                else
                    sprite->set_animation(idle);
                d_held = false;
            }
            break;
        }
        case bolt::Key::Space:
        {
            if (grounded)
            {
                velocity.y = 500.0f;
                grounded = false;
            }
        }
    }
}

void Player::add_hitbox(const bolt::ref_ptr<bolt::Hitbox2D> box)
{
    other_hitboxes.push_back(box);
}

void Player::compute(double delta_time)
{
    update_player(delta_time);
}

void Player::update_player(double delta_time)
{
    velocity.x = (-1.0f * a_held + d_held) * MOVEMENT_MOD;
    velocity.y -= GRAVITATIONAL_ACCELERATION * delta_time;
    //std::cout << position.x << " " << position.y << " Velo: " << velocity.x << " " << velocity.y << std::endl;

    if(velocity.length() > MAX_SPEED)
        velocity = velocity.normalize() * MAX_SPEED;

    bolt::vector_2 pos_delta = velocity * delta_time;
    bolt::vector_2 next_pos = position + pos_delta;
    position = next_pos;
    set_hitbox(position);

    for(const auto& box : other_hitboxes)
    {
        bolt::collision_info coll_info = bolt::check_collision(box, player_hitbox);
        if(coll_info.collision)
        {
            std::cout << "collision detected: " <<  player_hitbox->center.x << " " << player_hitbox->center.y << std::endl;;
            position = bolt::get_resting_point_and_update_velcity(coll_info.minkowski_hitbox, player_hitbox, velocity) - bolt::vector_2{16.0f, 12.0f};
            if (velocity.y == 0)
                grounded = true;
            set_hitbox(position);
        }
    }
}

void Player::set_hitbox(bolt::vector_2 pos)
{
    player_hitbox->set_position(pos + bolt::vector_2{16.0f, 12.0f});
}