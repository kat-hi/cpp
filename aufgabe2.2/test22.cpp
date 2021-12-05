//
// Created by Katharina Sachs on 30.11.21.
//

#include <iostream>
#include <cassert>
#include "my_vector.h"
#include "payload.h"
#include "stdio.h"

using namespace my;

void test_22() {
    using my::vector;

    string done = "\u2705";
    string arrow = "\u21E8";
    {
        cout << arrow + " constructor (size_t&, T&) ... ";
        {
            vector<Payload> v(2, Payload(1, 2, 3));
            assert(v.size() == 2);
            assert(v.capacity() == v.size());
            assert(v[0] == Payload(1, 2, 3));
            assert(v[1] == Payload(1, 2, 3));
        }
        printf("%24s", "");
        cout << done << endl;
    }
    {
        cout << arrow + " constructor (size_t&) ... ";
        {
            vector<Payload> v(3);
            assert(v.size() == 0);
            assert(v.capacity() == 3);
        }
        printf("%-28s", "");
        cout << done << endl;    }
    {
        cout << arrow + " constructor (vector<T>& rhs) copy ... ";
        {
            vector<Payload> v(vector<Payload>(2, Payload(1, 2, 3)));
            assert(v.size() == 2);
            assert(v.capacity() == 2);
            assert(v[0] == v[1]);
            assert(v[0] == Payload(1, 2, 3));
            assert(Payload::count() == 2);

        }
        printf("%16s", "");
        cout << done << endl;    }
    {
        cout << arrow + " constructor (vector<T>&& rhs) move ... ";
        {
            vector<Payload> l(1, Payload(1, 1, 1)); // one payload
            l = move(vector<Payload>(1, Payload(2, 2, 2))); // + one payload object

            assert(l[0] == Payload(2, 2, 2));
            assert(l.capacity() == 1);

            // payload correctly destroyed because moved.
            assert(Payload::count() == 1); // again one payload
        }
        printf("%15s", "");
        cout << done << endl;    }
    {
        cout << arrow + " push_back(), shrink_to_fit() ... ";
        {
            assert(Payload::count() == 0);

            vector<Payload> v(4);
            v.push_back(Payload(1, 1, 1));
            v.push_back(Payload(1, 1, 2));
            assert(Payload::count() == 2); // again one payload
            assert(v.capacity() == 4);
            assert(v.size() == 2);


            // fit capacity and size
            assert(v.size() != v.capacity());
            v.shrink_to_fit();
            assert(v.size() == v.capacity());
            assert(Payload::count() == 2);
        }
        printf("%21s", "");
        cout << done << endl;
    }

    {
        cout << arrow + " push back() if size > capacity ...";
        {
            assert(Payload::count() == 0);
            vector<Payload> v2(3);

            // memory without objects?
            assert(Payload::count() == 0);
            assert(v2.capacity() == 3);
            assert(v2.size() == 0);

            v2.push_back(Payload(1, 2, 3));
            v2.push_back(Payload(4, 5, 6));
            v2.push_back(Payload(7, 8, 9));
            assert(Payload::count() == 3);
            assert(v2.size() == v2.capacity());
\
            // add one more items than capacity exists
            v2.push_back(Payload(1, 1, 1));
            v2.push_back(Payload(2, 2, 2));
            assert(v2.size() == 5);
            assert(v2.capacity() == 6);
            assert(Payload::count() == 5);
        }
        printf("%-20s", "");
        cout << done << endl;
    }
    {
        cout << arrow + " pop_back(), payload destruction ...";
        {
            assert(Payload::count() == 0);
            vector<Payload> v(4);
            v.push_back(Payload(1, 1, 1));
            v.push_back(Payload(3, 3, 3));
            assert(Payload::count() == 2);
            assert(v.pop_back() == Payload(3, 3, 3));

            // payload count is expected to be reduced
            assert(Payload::count() == 1);
            assert(v.size() == 1);
        }
        printf("%19s", "");
        cout << done << endl;
    }
//    {
//        {
//            vector<Payload> v(4, Payload(1,1,1));
//            vector<Payload> l;
//            l = v;
//            l.push_back(Payload(1,2,3));
//            assert(l == v);
//        }
//    }
};