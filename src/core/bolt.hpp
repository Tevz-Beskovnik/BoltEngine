#pragma once

// core includes
#include <core.hpp>
#include <colors.hpp>
#include <util.hpp>
#include <application.hpp>
#include <layer_interface.hpp>

// renderer includes
#include <window.hpp>
#include <renderer_gl.hpp>
#include <renderer_vk.hpp>
#include <camera_base.hpp>
#include <mesh_builder.hpp>
#include <model.hpp>
#include <model_interface.hpp> // for creating custom model interfaces
#include <setup_primitives.hpp> // primitive defs
#include <line.hpp>
#include <rectangle.hpp>

// event system includes
#include <event.hpp>
#include <window_events.hpp>
#include <application_events.hpp>
#include <camera_events.hpp>
#include <keyboard_events.hpp>
#include <keyboard.hpp>
#include <mouse.hpp>

// exceptions
#include <assertion_exception.hpp>
#include <renderer_exception.hpp>
#include <setup_exception.hpp>
#include <texture_exception.hpp>
#include <wrong_file_extension_exception.hpp>