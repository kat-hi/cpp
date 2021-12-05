//
// Created by Katharina Sachs on 05.10.21.
//

#include "test11.h"
#include "vec3f.h"
#include <iostream>
#include <cassert>
using namespace std;
using namespace my;

void mytest_Vec3f(Vec3f vec, std::array<float, 3> excpected_array) {
    assert(vec.get_x()==excpected_array[0]);
    assert(vec.get_y()==excpected_array[1]);
    assert(vec.get_z()==excpected_array[2]);
}

int main() {
    Vec3f v(7, 5, 3);
    mytest_Vec3f(v, {7,5,3});
    cout << v.get_x() << endl;
    cout << sizeof(v) << endl;
    test_Vec3f();
    return 0;
};