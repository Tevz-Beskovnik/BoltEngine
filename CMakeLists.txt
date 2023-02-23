cmake_minimum_required(VERSION 3.20.5)
project(BoltEngine VERSION 1.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_APPLE_SILICON_PROCESSOR arm64) # comment out for linux builds

file (GLOB_RECURSE BoltEngine_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}" ${BoltEngine_SOURCES} "example/basic/main.cpp")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC BOLT_DEBUG) # comment out for release build

target_link_libraries("${CMAKE_PROJECT_NAME}" CONAN_PKG::glfw CONAN_PKG::glew)

set(BoltEngine_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories("${CMAKE_PROJECT_NAME}"
    PUBLIC BoltEngine_HEADERS 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/render
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/Vulkan
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/OpenGL
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/model
    #PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/scene
    #PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
)