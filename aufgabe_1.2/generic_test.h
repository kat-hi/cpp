//
// Created by Katharina Sachs on 23.10.21.
//
using namespace my;
using namespace std;

#include <iostream>
#include <cassert>
#include "vec.h"
#include <random>

#pragma once

template<typename T, int N>
void test_generic_vec(Vec<T, N> testvector) {

    random_device rd;
    mt19937 random(rd());
    uniform_real_distribution<> dist(20, 30);

    cout << "======================" << endl;
    cout << "     Testing Vec    " << endl;
    cout << "======================" << endl;

    {
        // do not tolerate any memory overhead
        cout << "  sizeof(Vec) == 3 bytes: ";
        assert(sizeof(testvector) == N * sizeof(T));
        cout << "passed." << endl;
    }

    {
        cout << "  constructor & index operator: ";
        Vec<T, N> b(testvector);
        for(int index = 0; index < N; index++) {
            assert(testvector[index] == b[index]);
        }
        cout << "passed." << endl;
    }

    {
        cout << "  read-only access to const object: ";
        const Vec<T, N> a(testvector);
        // the next line will throw a compiler error if there is no proper "operator[] const"
        assert(testvector[1] == a[1]);
        cout << "passed." << endl;
    }

    {
        cout << "  write access to a non-const object: ";
        Vec<T, N> a(testvector);
        a[1] = 4;
        for(int index = 0; index < N; index++) {
            if(index == 1)
                assert(a[index] == 4);
            else
                assert(a[index] == testvector[index]);
        }
        cout << "passed." << endl;
    }

    {
        cout << "  comparison: ";
        Vec<T, N> a(testvector);
        Vec<T, N> b(testvector);

        Vec<T,N> c;
        Vec<T,N> d;

        for (int index = 0; index < N; index++) {
            c[index] = T(dist(random));
        }
        for (int index = 0; index < N; index++) {
            d[index] = T(dist(random));
        }

        assert(a == b);
        assert(a == a);
        assert(a != c);
        assert(b != d);
        assert(!(a != b));
        cout << "passed." << endl;
    }

    {
        // should work out of the box when using std container (!)
        cout << "  assignment: ";
        Vec<T, N> a(testvector);
        cout << a[0] << " "; // to make sure these values are not optimized away!
        Vec<T,N> b;
        for (int index = 0; index < 3; index++) {
            b[index] = T(dist(random));
        }

        a = b;
        for(int index = 0; index < N; index++) {
            assert(a[index] == b[index]);
        }

        cout << "passed." << endl;
    }

    {
        cout << "  addition: ";

        Vec<T, N> a(testvector);
        Vec<T, N> b;
        for (int index = 0; index < N; index++) {
            b[index] = T(dist(random));
        }

        auto expected_result = testvector + b;
        a += b;
        assert(a == expected_result);

        Vec<T, N> oncie;
        for(int index = 0; index < N; index++) {
            oncie[index] = 1;
        };
        auto expected_result_next = testvector + b + oncie;
        auto c = a + oncie;
        assert(c == expected_result_next);

        Vec<float, 3> one;
        Vec<float, 3> four;

        for (int index = 0; index < N; index++) {
            b[index] = T(dist(random));
        }

        one += (one + one + one);
        assert(one == four);

        Vec<T, N> x(testvector);
        Vec<T, N> y;
        Vec<T, N> z;
        for (int index = 0; index < N; index++) {
            y[index] = T(dist(random));
        }
        for (int index = 0; index < N; index++) {
            z[index] = T(dist(random));
        }
        Vec<T,N> expected_result_new = x + y + z;
        Vec<T,N> expected_result_y = y + z;

        x += y += z;
        assert(y == expected_result_y);
        assert(x == expected_result_new);
        cout << "passed." << endl;
    }
    {
        cout << "  unary minus: ";
        Vec<T, N> a(testvector);
        Vec<T, N> b((-testvector));
        assert(-a == b);
        cout << "passed." << endl;
    }

    {
        cout << "  dot product: ";

        Vec<T, N> a(testvector);
        double expected_dot = 0;
        for(int index = 0; index < N; index++) {
            expected_dot = expected_dot + (a[index] * a[index]);
        };
        assert((dot(a, a) == expected_dot));
        cout << "passed." << endl;
    }

    {
        //      these tests will not compile if you forgot to declare
        //      some methods const
        cout << "  constness: ";

        const Vec<T, N> a(testvector);
        assert(a[1] == testvector[1]);
        assert(a == a);
        assert(!(a != a));
        assert(a + a == (testvector+testvector));
        assert(-a == (Vec<T, N> (-testvector)));
        double expected_dot = 0;
        for(int index = 0; index < N; index++) {
            expected_dot = expected_dot + (a[index] * a[index]);
        };
        assert((dot(a, a) == expected_dot));
        cout << "passed." << endl;
    }
    cout << "  Vec length: ";
    Vec<T, N> a(testvector);
    assert(a.length() == testvector.length());
    cout << "passed" << endl;


    cout << "all Vec tests passed." << endl << endl;

};

