//
// Created by Katharina Sachs on 05.10.21.
//

#ifndef AUFGABE_1_VEC3F_H
#define AUFGABE_1_VEC3F_H

#include <iostream>
#include <cmath>
#include <array>

using namespace std;

namespace my {
    template<typename T, int N>
    class Vec {
    public:
        Vec(std::array<T, N> v = std::array<T, N>()) : n_(v) {};

        std::array<T, N> get_array() const {
            return n_;
        }
//        friend Vec<T,N> operator+(Vec<T,N> const lhs, Vec<T,N> const rhs){
//            T result = lhs + rhs;
//            return result;
//        };

        T operator[](int) const;

        T &operator[](int);

        bool operator==(Vec<T, N>) const;

        bool operator!=(Vec<T, N>) const;

        Vec<T, N>& operator+=(const Vec<T, N>& v);

        Vec<T, N> operator+(const Vec<T, N>& v) const;

        Vec<T, N> operator-() const;

        double length() const {
            double result = 0;
            for (T n: n_)
                result = result + pow(n, 2);
            double endresult = sqrt(result);
            return endresult;
        };


    private:
        std::array<T, N> n_;
    };

    template<typename T, int N>
    T dot(const Vec<T, N> v1, const Vec<T, N> v2) {
        array<T, N> v1_array = v1.get_array();
        array<T, N> v2_array = v2.get_array();
        array<T, N> results;
        float dot = 0;

        auto mul = [](float a, float b) { return a * b; };
        std::transform(v1_array.begin(), v1_array.end(), v2_array.begin(), results.begin(), mul);
        for (float result: results)
            dot = dot + result;
        return dot;
    };

    template<typename T, int N>
    inline T Vec<T, N>::operator[](int index) const {
        return n_[index];
    };

    template<typename T, int N>
    inline T& Vec<T, N>::operator[](int index) {
        return n_[index];
    };

    template<typename T, int N>
    inline bool Vec<T, N>::operator==(Vec<T, N> v) const {
        array<T, N> v_array = v.get_array();
        return std::equal(v_array.begin(), v_array.end(), n_.begin());
    }

    template<typename T, int N>
    inline bool Vec<T, N>::operator!=(Vec<T, N> v) const {
        array<T, N> v_array = v.get_array();
        return !std::equal(v_array.begin(), v_array.end(), n_.begin());
    }

    template<typename T, int N>
    inline Vec<T, N>& Vec<T, N>::operator+=(const Vec<T, N>& rhs) {
        for(int index = 0; index < N; index++) {
            n_[index] += rhs[index];
        };
        return *this;
    }

    template<typename T, int N>
    inline Vec<T, N> Vec<T, N>::operator+(const Vec<T, N>& rhs) const {
        Vec<T, N> tmp(*this);
        tmp += rhs;
        return tmp;
    }

    template<typename T, int N>
    inline Vec<T, N> Vec<T, N>::operator-() const {
        auto minus = [](float a) { return -a; };

        array<T, N> res_array;
        std::transform(n_.begin(), n_.end(), res_array.begin(), minus);
        return Vec<T, N>(res_array);
    }

    template<typename T, int N>
    void printVec(const Vec<T,N>& vec) {
        for (T n: vec.get_array())
            cout << n << " ";
        cout << endl << string("vector length: ") << vec.length() << endl;
    }
    template<typename T, int N>
    void printLength(const Vec<T,N>& vec) {
        cout << vec.length() << endl;
    }

}

#endif //AUFGABE_1_VEC3F_H
