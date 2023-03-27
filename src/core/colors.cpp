#include "colors.hpp"

namespace bolt
{
    RGB::RGB()
        :r(0), g(0), b(0), a(0), r_dec(0), g_dec(0), b_dec(0), a_dec(0)
    {
        ;
    }

    RGB::RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        :r(r), g(g), b(b), a(a), r_dec((float)r/255.0f), g_dec((float)g/255.0f), b_dec((float)b/255.0f), a_dec((float)a/255.0f)
    {
        ;
    }

    void RGB::invert()
    {
        this->r = 0xFF - this->r;
        this->g = 0xFF - this->g;
        this->b = 0xFF - this->b;
        this->r_dec = 1.0f - this->r_dec;
        this->g_dec = 1.0f - this->g_dec;
        this->b_dec = 1.0f - this->b_dec;
    }
}