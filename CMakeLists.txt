cmake_minimum_required(VERSION 3.20.5)
project(BoltEngine VERSION 1.0)
# TODO localize all things to do with engine in a library!!! THIS SHOULD BE HIGH PRIORITY

# by setting this cmake exports the compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_APPLE_SILICON_PROCESSOR arm64) # comment out for linux builds

find_package(GLEW)
find_package(glfw3)
find_package(imgui)

set(MAIN_FILE_BASIC "example/basic/main.cpp")

file (GLOB_RECURSE BoltEngine_EXAMPLE_SOURCES_L1 CONFIGURE_DEPENDS "example/*.cpp")
file (GLOB_RECURSE BoltEngine_EXAMPLE_SOURCES_L2 CONFIGURE_DEPENDS "example/*/*.cpp")
file (GLOB_RECURSE BoltEngine_EXAMPLE_SOURCES_L3 CONFIGURE_DEPENDS "example/*/*/*.cpp")
file (GLOB_RECURSE BoltEngine_EXAMPLE_SOURCES_L4 CONFIGURE_DEPENDS "example/*/*/*/*.cpp")

file (GLOB_RECURSE BoltEngine_SOURCES_L1 CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE BoltEngine_SOURCES_L2 CONFIGURE_DEPENDS "src/*/*.cpp")
file (GLOB_RECURSE BoltEngine_SOURCES_L3 CONFIGURE_DEPENDS "src/*/*/*.cpp")
file (GLOB_RECURSE BoltEngine_SOURCES_L4 CONFIGURE_DEPENDS "src/*/*/*/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}"
        ${BoltEngine_SOURCES_L1} # Main sources
        ${BoltEngine_SOURCES_L2}
        ${BoltEngine_SOURCES_L3}
        ${BoltEngine_SOURCES_L4}
        ${BoltEngine_EXAMPLE_SOURCES_L1} # Example sources
        ${BoltEngine_EXAMPLE_SOURCES_L2}
        ${BoltEngine_EXAMPLE_SOURCES_L3}
        ${BoltEngine_EXAMPLE_SOURCES_L4}
        ${MAIN_FILE_BASIC}
)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC BOLT_DEBUG) # comment out for release build

set(BoltEngine_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} GLEW::GLEW glfw imgui::imgui)

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
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/example/basic/game_object
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/scene
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/primitives
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_impl
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/primitives/line
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/primitives/rectangle
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/primitives/triangle
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/example/basic/camera
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/example/basic/game_functions
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/scene/camera
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/interactions
        #PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
)
