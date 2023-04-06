#pragma once

#include <core.hpp>

#define BLACK_FG 30
#define BLACK_BG 40
#define RED_FG 31
#define RED_BG 41
#define GREEN_FG 32
#define GREEN_BG 42
#define YELLOW_FG 33
#define YELLOW_BG 43
#define BLUE_FG 34
#define BLUE_BG 44
#define MAGENTA_FG 35
#define MAGENTA_BG 45
#define CYAN_FG 36
#define CYAN_BG 46
#define WHITE_FG 37
#define WHITE_BG 47

#ifdef __APPLE__
#define COLOR(fg, bg) printf("\x1b[%d;%dm", fg, bg);
#elif __linux__
// TODO:
#elif _WIN64
#define COLOR(fg, bg) printf("\033[%d;%dm", fg, bg);
#endif

namespace bolt
{
    class RGB
    {
        public:
            uint8_t r;
            float r_dec;
            uint8_t g;
            float g_dec;
            uint8_t b;
            float b_dec;
            uint8_t a;
            float a_dec;

            RGB();

            RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0);

            void set_r(uint8_t);

            void set_g(uint8_t);

            void set_b(uint8_t);

            void invert();
    };
}