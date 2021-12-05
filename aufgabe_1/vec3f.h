//
// Created by Katharina Sachs on 05.10.21.
//

#ifndef AUFGABE_1_VEC3F_H
#define AUFGABE_1_VEC3F_H

#include <array>

namespace my {
    class Vec3f {
    public:
        Vec3f(float x = 0, float y = 0, float z = 0);

        float get_x() const;

        float get_y() const;

        float get_z() const;

        void set_x(float x);

        void set_y(float y);

        void set_z(float z);

        float operator[](int) const;

        float &operator[](int);

        bool operator==(Vec3f) const;

        bool operator!=(Vec3f) const;

        Vec3f &operator+=(const Vec3f&);

        Vec3f operator+(Vec3f) const;

        Vec3f operator-() const;

    private:
        std::array<float, 3> n_;
    };

    inline float Vec3f::get_x() const { return n_[0]; };

    inline float Vec3f::get_y() const { return n_[1]; };

    inline float Vec3f::get_z() const { return n_[2]; };

    inline float dot(const Vec3f v1, const Vec3f v2) {
        float x = v1[0] * v2[0];
        float y = v1[1] * v2[1];
        float z = v1[2] * v2[2];
        float dot = x + y + z;
        return dot;
    }
}

#endif //AUFGABE_1_VEC3F_H
