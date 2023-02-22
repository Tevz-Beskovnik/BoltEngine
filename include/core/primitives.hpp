#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    struct vector_2
    {
        double x;
        double y;

        //vector addition
        inline vector_2 operator + (vector_2 const vec)
        {
            return {
                this->x + vec.x,
                this->y + vec.y
            };
        }

        // vector addition
        inline void operator += (vector_2 const &vec)
        {
            this->y += vec.y;
            this->x += vec.x;
        }

        // vector subtraction
        inline vector_2 operator - (vector_2 const &vec)
        {
            vector_2 res;
            res.x = this->y - vec.y;
            res.y = this->x - vec.x;
            return res;
        }

        // vector subtraction
        inline vector_2 operator -= (vector_2 const &vec)
        {
            this->x -= vec.x;
            this->y -= vec.y;
        }

        // vector doproduct
        inline double operator | (vector_2 const &vec)
        {
            return this->x*vec.x + this->y*vec.y;
        }

        // multiply by vector
        inline vector_2 operator * (double const &scalar)
        {
            return {
                this->x * scalar,
                this->y * scalar
            };
        }

        inline void operator *= (double const &scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
        }

        inline vector_2 operator / (double const &scalar)
        {
            return {
                this->x / scalar,
                this->y / scalar
            };
        }

        inline void operator /= (double const &scalar)
        {
            this->x /= scalar;
            this->y /= scalar;
        }

        inline double length()
        {
            return sqrtl((*this) | (*this));
        }

        inline vector_2 normalize()
        {
            double l = this->length();
            bool lf = l != 0, lt = l == 0;
            return {
                ((this->x / l) * lf + this->x * lt),
                ((this->y / l) * lf + this->y * lt)
            };
        }
    };

    struct vector_3
    {
        double x;
        double y;
        double z;

        // vector addition
        inline vector_3 operator + (vector_3 const &vec)
        {
            return {
                this->x + vec.x,
                this->y + vec.y,
                this->z + vec.z
            };
        }

        // vector addition
        inline void operator += (vector_3 const &vec)
        {
            this->x += vec.x;
            this->y += vec.y;
            this->z += vec.z;
        }

        // vector subtraction
        inline vector_3 operator - (vector_3 const &vec)
        {
            return {
                this->x - vec.x,
                this->y - vec.y,
                this->z - vec.z
            };
        }

        // vector subtraction
        inline void operator -= (vector_3 const &vec)
        {
            this->x -= vec.x;
            this->y -= vec.y;
            this->z -= vec.z;
        }

        // vector multiply by scalar
        inline vector_3 operator * (double const &scalar)
        {
            return {
                this->x * scalar,
                this->y * scalar,
                this->z * scalar
            };
        }

        // vector multiply by scalar
        inline void operator *= (double const &scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
        }

        // vector dot product
        inline double operator | (vector_3 const &vec)
        {
            return this->x*vec.x + this->y*vec.y + this->z*vec.z;
        }

        // vector cross product
        inline vector_3 operator % (vector_3 const &vec)
        {
            return {
                (this->y * vec.z - this->z * vec.y),
		        (this->z * vec.x - this->x * vec.z),
		        (this->x * vec.y - this->y * vec.x)
            };
        }

        // vector cross product
        inline void operator %= (vector_3 const &vec)
        {
            this->x = this->y * vec.z - this->z * vec.y;
            this->y = this->z * vec.x - this->x * vec.z;
            this->z = this->x * vec.y - this->y * vec.x;
        }

        // calculate vector length
        inline double length()
        {
            return sqrtl((*this) | (*this));
        }

        //normalized vector
        inline vector_3 normalize() 
        {
            double l = this->length();
            bool lf = l != 0, lt = l == 0;
            return {
                ((this->x / l) * lf + this->x * lt),
                ((this->y / l) * lf + this->y * lt),
                ((this->z / l) * lf + this->z * lt)
            };
        }
    };
    
    struct matrix_3
    {
        double m[3][3] {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
    };

    struct matrix_4
    {
        double m[4][4] {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        // translation matrix
        static matrix_4 translation(vector_3 const &vec)
        {
            return {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                vec.x, vec.y, vec.z, 1.0f
            };
        }

        static matrix_4 rotation_x(double deg)
        {
            return {
                1.0f, 0.0f, 0.0f, 0.0f,
		        0.0f, cos(deg), -sin(deg), 0.0f,
		        0.0f, sin(deg), cos(deg), 0.0f,
		        0.0f, 0.0f, 0.0f, 1.0f
            };
        }

        static matrix_4 rotation_y(double deg)
        {
            return {
                cos(deg), 0.0f, sin(deg), 0.0f,
		        0.0f, 1.0f, 0.0f, 0.0f,
		        -sin(deg), 0.0f, cos(deg), 0.0f,
		        0.0f, 0.0f, 0.0f, 1.0f
            };
        }

        static matrix_4 rotation_z(double deg)
        {
            return {
	        	cos(deg), -sin(deg), 0.0f, 0.0f, 
	        	sin(deg), cos(deg), 0.0f, 0.0f,
	        	0.0f, 0.0f, 1.0f, 0.0f,
	        	0.0f, 0.0f, 0.0f, 1.0f
	        };
        }

        inline matrix_4 quick_inverse()
        {
            
        }
    };
}