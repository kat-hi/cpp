//
// Created by Katharina Sachs on 05.10.21.
//
#include "vec.h"
#include "generic_test.h"
#include <random>
#include <cmath>

using namespace std;
using namespace my;

vector<Vec<float, 3>> create_random_vector() {
    cout << "random vector:" << endl;

    random_device rd;
    mt19937 random(rd());
    uniform_real_distribution<> dist(0, 100);

    vector<Vec<float, 3>> stdvec;

    for (int vector = 0; vector < 10; vector++) {
        Vec<float, 3> pushvec;
        for (int vectorindex = 0; vectorindex < 3; vectorindex++) {
            pushvec[vectorindex] = float(dist(random));
        }
        stdvec.push_back(pushvec);
    };
    return stdvec;
};

vector<Vec<float, 3>> increase_stdvec_by_one(vector<Vec<float, 3>> stdvec) {
    auto add_one = [](Vec<float, 3> myvec) {
        Vec<float, 3> rhs(array<float, 3>({1.0f, 1.0f, 1.0f}));
        myvec = myvec + rhs;
        return myvec;
    };
    vector<Vec<float, 3>> res_vec;
    res_vec.resize(stdvec.size());
    transform(stdvec.begin(), stdvec.end(), res_vec.begin(), add_one);
    return res_vec;
}

vector<Vec<float, 3>> length_greater_90(vector<Vec<float, 3>> stdvec) {
    vector<Vec<float, 3>> length_greater_90;
    auto greater_to_be_erased = stable_partition(stdvec.begin(), stdvec.end(),
                                                 [](Vec<float, 3> vec) { return vec.length() >= 90; });

    stdvec.erase(greater_to_be_erased, stdvec.end());
    for (auto it = stdvec.begin(); it != greater_to_be_erased; ++it) {
        length_greater_90.push_back(*it);
    };
    return length_greater_90;
}

vector<Vec<float, 3>> length_smaller_90(vector<Vec<float, 3>> stdvec) {
    vector<Vec<float, 3>> length_smaller_90;
    auto smaller_to_be_erased = stable_partition(stdvec.begin(), stdvec.end(),
                                                 [](Vec<float, 3> vec) { return vec.length() < 90; });
    stdvec.erase(smaller_to_be_erased, stdvec.end());
    for (auto it = stdvec.begin(); it != smaller_to_be_erased; ++it) {
        length_smaller_90.push_back(*it);
    };
    return length_smaller_90;
}

void partitioning(const vector<Vec<float, 3>> &stdvec) {
    for (Vec<float, 3> n: stdvec) {
        printLength(n);
    };
    cout << "----------" << endl;

    auto smaller_than_90 = length_smaller_90(stdvec);
    cout << "< 90" << endl;
    for (Vec<float, 3> n: smaller_than_90) {
        printLength(n);
    };
    cout << "----------" << endl;

    cout << ">= 90" << endl;
    auto greater_90 = length_greater_90(stdvec);
    for (Vec<float, 3> n: greater_90) {
        printLength(n);
    };
    cout << "----------" << endl;

}

vector<Vec<float, 3>> sorting(vector<Vec<float, 3>>& stdvec) {
    cout << "sorted:" << endl;
    sort(stdvec.begin(), stdvec.end(), [](Vec<float, 3> vec_a, Vec<float, 3> vec_b) {
        return vec_a.length() < vec_b.length();
    });
    return stdvec;
}

void get_median(const vector<Vec<float, 3>> &stdvec) {
    for (Vec<float, 3> n: stdvec) {
        printLength(n);
    };
    cout << "----------" << endl;
    cout << "median:" << endl;
    auto a = stdvec[4];
    auto b = stdvec[5];
    double median = (a.length() + b.length()) / 2;
    cout << median << endl;
    cout << "----------" << endl;
}

void copying(vector<Vec<float, 3>> stdvec) {
    cout << "copy:" << endl;

    vector<Vec<float, 3>> to_vector;
    // we need a back inserter since the copy_if only copies the value and increases the iterator
    copy_if(stdvec.begin(), stdvec.end(), back_inserter(to_vector),
            [](Vec<float, 3> vec) { return vec.length() < 80; });
    for (Vec<float, 3> x: to_vector)
        printLength(x);
    cout << "----------" << endl;
};

void removing(vector<Vec<float, 3>> stdvec) {
    cout << "remove: 90 < length < 120:" << endl;

    auto to_be_erased = remove_if(stdvec.begin(), stdvec.end(),
                                  [](Vec<float, 3> vec) {
                                      if (vec.length() < 120 and vec.length() > 90) {
                                          return true;
                                      } else {
                                          return false;
                                      }
                                  });
    stdvec.erase(to_be_erased, stdvec.end());
    for (Vec<float, 3> x: stdvec)
        printLength(x);
    cout << "----------" << endl;
};

int main() {
//    TESTS:
    Vec<float, 3> float_vec(array<float, 3>({1, 2, 3}));
    test_generic_vec(float_vec);
    Vec<int, 10> int_vec(array<int, 10>({4, 5, 6, 7, 8, 9, 1, 2, 3, 4}));
    test_generic_vec(int_vec);
    Vec<double, 2> double_vec(array<double, 2>({4, 5}));
    test_generic_vec(double_vec);

//    PRINT:
//    printVec(double_vec);
//    printVec(int_vec);
//    printVec(float_vec);

// RANDOM STUFF
//    vector<Vec<float, 3>> stdvec = create_random_vector();
//    vector<Vec<float, 3>> stdvec_increased = increase_stdvec_by_one(stdvec);
//    partitioning(stdvec);
//    sorting(stdvec);
//    get_median(stdvec);
//    copying(stdvec);
//    removing(stdvec);
    return 0;
};