#pragma once

#include <core.hpp>
#include <util.hpp>

namespace bolt
{
    struct vector_2
    {
        double x = 0;
        double y = 0;

        //vector addition
        [[nodiscard]] inline vector_2 operator + (vector_2 const vec) const
        {
            return vector_2 {
                .x = this->x + vec.x,
                .y = this->y + vec.y
            };
        }

        // vector addition
        inline void operator += (vector_2 const &vec)
        {
            this->y += vec.y;
            this->x += vec.x;
        }

        // vector subtraction
        [[nodiscard]] inline vector_2 operator - (vector_2 const &vec) const
        {
            vector_2 res;
            res.x = this->x - vec.x;
            res.y = this->y - vec.y;
            return res;
        }

        // vector subtraction
        inline void operator -= (vector_2 const &vec)
        {
            this->x -= vec.x;
            this->y -= vec.y;
        }

        // vector doproduct
        [[nodiscard]] inline float operator | (vector_2 const &vec) const
        {
            return this->x*vec.x + this->y*vec.y;
        }

        // multiply by vector
        [[nodiscard]] inline vector_2 operator * (double const &scalar) const
        {
            return vector_2 {
                .x = this->x * scalar,
                .y = this->y * scalar
            };
        }

        inline void operator *= (float const &scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
        }

        [[nodiscard]] inline vector_2 operator / (double const &scalar) const
        {
            return vector_2 {
                .x = this->x / scalar,
                .y = this->y / scalar
            };
        }

        inline void operator /= (double const &scalar)
        {
            this->x /= scalar;
            this->y /= scalar;
        }

        [[nodiscard]] inline double length() const
        {
            return (double)sqrtl((*this) | (*this));
        }

        [[nodiscard]] inline vector_2 normalize() const
        {
            double l = this->length();
            bool lf = l != 0, lt = l == 0;
            return vector_2 {
                .x = ((this->x / static_cast<double>(l)) * static_cast<double>(lf) + this->x * static_cast<double>(lt)),
                .y = ((this->y / static_cast<double>(l)) * static_cast<double>(lf) + this->y * static_cast<double>(lt))
            };
        }

        [[nodiscard]] inline std::string to_string() const
        {
            return std::to_string(x) + " " + std::to_string(y);
        }
    };

    struct vector_3
    {
        double x = 0.0f;
        double y = 0.0f;
        double z = 0.0f;

        // vector addition
        [[nodiscard]] inline vector_3 operator + (vector_3 const &vec) const
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
        [[nodiscard]] inline vector_3 operator - (vector_3 const &vec) const
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
        [[nodiscard]] inline vector_3 operator * (float const &scalar) const
        {
            return {
                this->x * scalar,
                this->y * scalar,
                this->z * scalar
            };
        }

        // vector multiply by scalar
        inline void operator *= (float const &scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
        }

        // vector dot product
        [[nodiscard]] inline float operator | (vector_3 const &vec) const
        {
            return this->x*vec.x + this->y*vec.y + this->z*vec.z;
        }

        // vector cross product
        [[nodiscard]] inline vector_3 operator % (vector_3 const &vec) const
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
        [[nodiscard]] inline float length() const
        {
            return (float)sqrtl((*this) | (*this));
        }

        //normalized vector
        [[nodiscard]] inline vector_3 normalize() const
        {
            float l = this->length();
            bool lf = l != 0, lt = l == 0;
            return {
                ((this->x / l) * lf + this->x * lt),
                ((this->y / l) * lf + this->y * lt),
                ((this->z / l) * lf + this->z * lt)
            };
        }

        [[nodiscard]] inline std::string to_string() const
        {
            return std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
        }
    };
    
    struct matrix_3
    {
        float m[3][3] {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        matrix_3& operator=(const matrix_3& othr)
        {
            if(&othr == this) return *this;

            for(uint8_t i = 0; i < 3; i++)
                for(uint8_t j = 0; j < 3; j++)
                    m[i][j] = othr.m[i][j];

            return *this;
        }
    };

    struct matrix_4
    {
        float m[4][4] {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        // translation matrix
        [[nodiscard]] static matrix_4 translation(vector_3 const &vec)
        {
            return {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                static_cast<float>(vec.x), static_cast<float>(vec.y), static_cast<float>(vec.z), 1.0f
            };
        }

        [[nodiscard]] static matrix_4 rotation_x(float deg)
        {
            return {
                1.0f, 0.0f, 0.0f, 0.0f,
		        0.0f, cos(deg), -sin(deg), 0.0f,
		        0.0f, sin(deg), cos(deg), 0.0f,
		        0.0f, 0.0f, 0.0f, 1.0f
            };
        }

        [[nodiscard]] static matrix_4 rotation_y(float deg)
        {
            return {
                cos(deg), 0.0f, sin(deg), 0.0f,
		        0.0f, 1.0f, 0.0f, 0.0f,
		        -sin(deg), 0.0f, cos(deg), 0.0f,
		        0.0f, 0.0f, 0.0f, 1.0f
            };
        }

        [[nodiscard]] static matrix_4 rotation_z(float deg)
        {
            return {
	        	cos(deg), -sin(deg), 0.0f, 0.0f, 
	        	sin(deg), cos(deg), 0.0f, 0.0f,
	        	0.0f, 0.0f, 1.0f, 0.0f,
	        	0.0f, 0.0f, 0.0f, 1.0f
	        };
        }

        [[nodiscard]] static matrix_4 point_at_matrix(const vector_3& pos, const vector_3& target, const vector_3& up)
        {
            vector_3 target_temp = target - pos;
            vector_3 new_forward = target_temp.normalize();
            vector_3 a = new_forward * (up | new_forward);
            vector_3 up_temp = up - a;
            vector_3 new_up = up_temp.normalize();
            vector_3 new_right = new_up % new_forward;

            matrix_4 return_matrix;
            return_matrix.m[0][0] = new_right.x; return_matrix.m[0][1] = new_right.y; return_matrix.m[0][2] = new_right.z; return_matrix.m[0][3] = 0.0f;
            return_matrix.m[1][0] = new_up.x; return_matrix.m[1][1] = new_up.y; return_matrix.m[1][2] = new_up.z; return_matrix.m[1][3] = 0.0f;
            return_matrix.m[2][0] = new_forward.x;	return_matrix.m[2][1] = new_forward.y;	return_matrix.m[2][2] = new_forward.z;	return_matrix.m[2][3] = 0.0f;
            return_matrix.m[3][0] = pos.x;			return_matrix.m[3][1] = pos.y;			return_matrix.m[3][2] = pos.z;			return_matrix.m[3][3] = 1.0f;
            return return_matrix;
        }

        [[nodiscard]] static matrix_4 view_matrix(const matrix_4& projection_matrix, const vector_3& pos, const vector_3& target, const vector_3& up, const vector_3& rotations)
        {
            matrix_4 camera_rotation_x = matrix_4::rotation_x(rotations.x);
            matrix_4 camera_rotation_y = matrix_4::rotation_y(rotations.y);
            matrix_4 camera_rotation_z = matrix_4::rotation_z(rotations.z);
            matrix_4 multiplied_rotations = (camera_rotation_x * camera_rotation_y * camera_rotation_z) * matrix_4::point_at_matrix(pos, target, up);

            matrix_4 view = multiplied_rotations.quick_inverse();

            return view * projection_matrix;
        }

        [[nodiscard]] inline matrix_4 quick_inverse()
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

        [[nodiscard]] inline matrix_4 operator * (matrix_4 mat) const // <-- generates compiler error if member variable is modified
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

        [[nodiscard]] inline vector_3 operator* (vector_3 vec) const
        {
            // Now set some simple names for the vec
            float x = vec.x;
            float y = vec.y;
            float z = vec.z;

            // Multiply the vec against each part of the 1st column, then add together
            float resX = (x * this->m[0][0]) + (y * this->m[1][0]) + (z * this->m[2][0]) + (this->m[3][0]);

            // Multiply the vec against each part of the 2nd column, then add together
            float resY = (x * this->m[0][1]) + (y * this->m[1][1]) + (z * this->m[2][1]) + (this->m[3][1]);

            // Multiply the vec against each part of the 3rd column, then add together
            float resZ = (x * this->m[0][2]) + (y * this->m[1][2]) + (z * this->m[2][2]) + (this->m[3][2]);

            // Multiply the vec against each part of the 4th column, then add together
            float resW = (x * this->m[0][3]) + (y * this->m[1][3]) + (z * this->m[2][3]) + (this->m[3][3]);

            if (resW != 0) {
                resX /= resW; resY /= resW; resZ /= resW;
            }

            return{
                resX, resY, resZ
            };
        }

        matrix_4& operator=(const matrix_4& othr)
        {
            if(&othr == this) return *this;

            for(uint8_t i = 0; i < 4; i++)
                for(uint8_t j = 0; j < 4; j++)
                    m[i][j] = othr.m[i][j];

            return *this;
        }

        [[nodiscard]] bool operator!=(const matrix_4& othr)
        {
            return m[0][0] != othr.m[0][0] || m[0][1] != othr.m[0][1] || m[0][2] != othr.m[0][2] || m[0][3] != othr.m[0][3] ||
                    m[1][0] != othr.m[1][0] || m[1][1] != othr.m[1][1] || m[1][2] != othr.m[1][2] || m[1][3] != othr.m[1][3] ||
                    m[2][0] != othr.m[2][0] || m[2][1] != othr.m[2][1] || m[2][2] != othr.m[2][2] || m[2][3] != othr.m[2][3] ||
                    m[3][0] != othr.m[3][0] || m[3][1] != othr.m[3][1] || m[3][2] != othr.m[3][2] || m[3][3] != othr.m[3][3];
        }

        [[nodiscard]] std::string to_string() const
        {
            std::string out = "[" + std::to_string(m[0][0]) + " " + std::to_string(m[0][1]) + " " + std::to_string(m[0][2]) + " " + std::to_string(m[0][3]) + "\n" +
                std::to_string(m[1][0]) + " " + std::to_string(m[1][1]) + " " + std::to_string(m[1][2]) + " " + std::to_string(m[1][3]) + "\n" +
                std::to_string(m[2][0]) + " " + std::to_string(m[2][1]) + " " + std::to_string(m[2][2]) + " " + std::to_string(m[2][3]) + "\n" +
                std::to_string(m[3][0]) + " " + std::to_string(m[3][1]) + " " + std::to_string(m[3][2]) + " " + std::to_string(m[3][3]) + "]";

            return out;
        }
    };

    struct polygon
    {
        vector_3 vert[3];
        vector_2 UV[3];
        vector_3 normal;

        void print() const
        {
            for(uint8_t i = 0; i < 3; i++)
            {
                std::cout << "Vert: " << vert[i].to_string() << " UV: " << UV[i].to_string() << std::endl;
            }
            std::cout << "Normal: " << normal.to_string() << std::endl;
        }
    };
}
