#pragma once

// core includes
#include <core.hpp>
#include <colors.hpp>
#include <util.hpp>
#include <application.hpp>
#include <layer_interface.hpp>

// renderer includes
#include <window.hpp>
#include <object_creator.hpp>
#include <renderer_gl.hpp>
#include <renderer_vk.hpp>
#include "camera/camera_3d_base.hpp"
#include "camera/camera_2d_base.hpp"
#include <mesh_builder.hpp>
#include <model.hpp>
#include <line_model.hpp>
#include <texture_gl.hpp>
#include <animated_texture_gl.hpp>
#include <animation.hpp>
#include <model_interface.hpp> // for creating custom model_from_file interfaces
#include <setup_primitives.hpp> // primitive defs
#include <line.hpp>
#include <rectangle.hpp>
#include <triangle.hpp>

// event system includes
#include <event.hpp>
#include <window_events.hpp>
#include <application_events.hpp>
#include <camera_events.hpp>
#include <keyboard_events.hpp>
#include <mouse_events.hpp>
#include <keyboard.hpp> // TODO throw out old input modes
#include <mouse.hpp>

// exceptions
#include <assertion_exception.hpp>
#include <renderer_exception.hpp>
#include <setup_exception.hpp>
#include <texture_exception.hpp>
#include <wrong_file_extension_exception.hpp>

// interactions
#include <box_util.hpp>
#include <collision.hpp>
#include <hitbox_2d.hpp>