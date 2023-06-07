cmake_minimum_required(VERSION 3.20.5)
project(BoltEngine VERSION 1.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_APPLE_SILICON_PROCESSOR arm64) # comment out for linux builds

file (GLOB_RECURSE BoltEngine_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

set (
        BoltEngine_HEADER_FILES
        src/rendering/OpenGL/shader_gl.cpp
        src/rendering/Vulkan/shader_vk.cpp
        src/rendering/OpenGL/texture_gl.cpp
        src/rendering/OpenGL/renderer_gl.cpp
        src/rendering/Vulkan/renderer_vk.cpp
        src/rendering/OpenGL/vertex_gl.cpp
        src/rendering/OpenGL/buffer_gl.cpp
        src/rendering/OpenGL/index_buffer_gl.cpp
        src/rendering/OpenGL/frame_buffer_gl.cpp
        src/core/application.cpp
        example/basic/layers/test_layer.cpp
        src/scene/camera_base.cpp
        src/core/log.cpp
        src/exceptions/renderer_exception.cpp
        src/exceptions/wrong_file_extension_exception.cpp
        src/exceptions/setup_exception.cpp
        src/exceptions/assertion_exception.cpp
        src/exceptions/log_exception.cpp
        src/events/event_caller.cpp
        src/io/keyboard.cpp
        example/basic/camera/test_camera.cpp
        src/imgui_impl/imgui_impl_glfw.cpp
        src/imgui_impl/imgui_impl_opengl3.cpp
        src/io/mouse.cpp
        src/model/types/font.cpp)

add_executable("${CMAKE_PROJECT_NAME}" ${BoltEngine_SOURCES} "example/basic/main.cpp" ${BoltEngine_HEADER_FILES})

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC BOLT_DEBUG) # comment out for release build

target_link_libraries("${CMAKE_PROJECT_NAME}" CONAN_PKG::glfw CONAN_PKG::glew CONAN_PKG::imgui)

set(BoltEngine_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories(
        "${CMAKE_PROJECT_NAME}"
        PUBLIC BoltEngine_HEADERS
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/core
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/render
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Vulkan
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/OpenGL
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/model
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/io
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/model/types
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/events
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/example/basic/layers
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/scene
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/primitives
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_impl
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/primitives/line
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/example/basic/camera
        #PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
)