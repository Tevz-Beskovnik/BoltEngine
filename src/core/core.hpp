#pragma once

#ifndef PI
#define PI 3.14159265358979323846
#endif // PI

#define ENUM_TO_STRING(e) #e

// PRIMARY
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <source_location.hpp>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

// EXTERNAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.hpp>
#include <imgui_impl_opengl3.hpp>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h> // stb implementation