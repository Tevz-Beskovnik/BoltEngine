#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    struct vector_2
    {
        double x = 0.0f;
        double y = 0.0f;

        //vector addition
        inline vector_2 operator + (vector_2 const vec) const
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
        inline vector_2 operator - (vector_2 const &vec) const
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
        inline double operator | (vector_2 const &vec) const
        {
            return this->x*vec.x + this->y*vec.y;
        }

        // multiply by vector
        inline vector_2 operator * (double const &scalar) const
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

        inline vector_2 operator / (double const &scalar) const
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

        inline double length() const
        {
            return (double)sqrtl((*this) | (*this));
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
        double x = 0.0f;
        double y = 0.0f;
        double z = 0.0f;

        // vector addition
        inline vector_3 operator + (vector_3 const &vec) const
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
        inline vector_3 operator - (vector_3 const &vec) const
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
        inline vector_3 operator * (double const &scalar) const
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
        inline double operator | (vector_3 const &vec) const
        {
            return this->x*vec.x + this->y*vec.y + this->z*vec.z;
        }

        // vector cross product
        inline vector_3 operator % (vector_3 const &vec) const
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
        inline double length() const
        {
            return (double)sqrtl((*this) | (*this));
        }

        //normalized vector
        inline vector_3 normalize() const
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
            matrix_4 return_matrix;
            return_matrix.m[0][0] = this->m[0][0]; return_matrix.m[0][1] = this->m[1][0]; return_matrix.m[0][2] = this->m[2][0]; return_matrix.m[0][3] = 0.0f;
            return_matrix.m[1][0] = this->m[0][1]; return_matrix.m[1][1] = this->m[1][1]; return_matrix.m[1][2] = this->m[2][1]; return_matrix.m[1][3] = 0.0f;
            return_matrix.m[2][0] = this->m[0][2]; return_matrix.m[2][1] = this->m[1][2]; return_matrix.m[2][2] = this->m[2][2]; return_matrix.m[2][3] = 0.0f;
            return_matrix.m[3][0] = -(this->m[3][0] * return_matrix.m[0][0] + this->m[3][1] * return_matrix.m[1][0] + this->m[3][2] * return_matrix.m[2][0]);
            return_matrix.m[3][1] = -(this->m[3][0] * return_matrix.m[0][1] + this->m[3][1] * return_matrix.m[1][1] + this->m[3][2] * return_matrix.m[2][1]);
            return_matrix.m[3][2] = -(this->m[3][0] * return_matrix.m[0][2] + this->m[3][1] * return_matrix.m[1][2] + this->m[3][2] * return_matrix.m[2][2]);
            return_matrix.m[3][3] = 1.0f;
            return return_matrix;
        }

        inline matrix_4 operator * (matrix_4 mat) const // <-- generates compiler error if member variable is modified
        {
            matrix_4 matrix;
            for (int c = 0; c < 4; c++)
            {
                for (int r = 0; r < 4; r++)
                {
                    matrix.m[r][c] = this->m[r][0] * mat.m[0][c] + this->m[r][1] * mat.m[1][c] + this->m[r][2] * mat.m[2][c] + this->m[r][3] * mat.m[3][c];
                }
            }

            return matrix;
        }

        inline void operator *= (matrix_4 mat)
        {
            matrix_4 matrix = *this;
            for (int c = 0; c < 4; c++)
            {
                for (int r = 0; r < 4; r++)
                {
                    this->m[r][c] = matrix.m[r][0] * mat.m[0][c] + matrix.m[r][1] * mat.m[1][c] + matrix.m[r][2] * mat.m[2][c] + matrix.m[r][3] * mat.m[3][c];
                }
            }
        }
    };
}