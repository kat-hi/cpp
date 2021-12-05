#include "vec3f.h"

using namespace my;

Vec3f::Vec3f(float x, float y, float z)
        : n_({x, y, z}) {
};

void Vec3f::set_x(float x) {
    n_[0] = x;
}

void Vec3f::set_y(float y) {
    n_[1] = y;
}

void Vec3f::set_z(float z) {
    n_[2] = z;
}

float Vec3f::operator[](int index) const {
    return n_[index];
};

float &Vec3f::operator[](int index) {
    return n_[index];
};

bool Vec3f::operator==(Vec3f v) const {
    if (n_[0] == v[0] && n_[1] == v[1] && n_[2] == v[2]) {
        return true;
    } else {
        return false;
    }
}

bool Vec3f::operator!=(Vec3f v) const {
    if (n_[0] == v[0] && n_[1] == v[1] && n_[2] == v[2]) {
        return false;
    } else {
        return true;
    }
}

Vec3f &Vec3f::operator+=(const Vec3f &v) {
    n_[0] += v[0];
    n_[1] += v[1];
    n_[2] += v[2];
    return *this;
}

Vec3f Vec3f::operator+(Vec3f v)  const {
    Vec3f tmp(*this);
    tmp += v;
    return tmp;
}

Vec3f Vec3f::operator-() const {
    float a = -n_[0];
    float b = -n_[1];
    float c = -n_[2];
    return {a,b,c};
}
