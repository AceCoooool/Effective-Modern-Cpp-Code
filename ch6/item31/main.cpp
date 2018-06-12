#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <chrono>
#include <set>
#include <memory>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: reference lambda----- */
template<typename C>
void workWithContainer(const C &container) {
    auto divisor = 5;
    if (all_of(begin(container), end(container), [&](const auto &value) { return value % divisor == 0; })) {
        cout << "OK!!! it's great" << endl;
    } else {
        cout << "Bad!!! it's not pass" << endl;
    }
}

void demo1() {
    vector<int> v1{5, 10, 15, 20};
    workWithContainer(v1);
    vector<int> v2{1, 4, 3, 6, 9};
    workWithContainer(v2);
}

/* -----demo2: value lambda----- */
void demo2() {
    auto divisor = 5;
    auto f1 = [=](int value) { return value % divisor == 0; };
    cout << "f1(10): " << f1(10) << endl;
    cout << "f1(1): " << f1(1) << endl;
}

/* -----demo3: generalized lambda----- */
void demo3() {
    auto divisor = 5;
    auto f2 = [divisor = divisor](int value) { return value % divisor == 0; };
    cout << "f2(10): " << f2(10) << endl;
    cout << "f2(1): " << f2(1) << endl;
}


int main() {
/* -----demo1: reference lambda----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: value lambda----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: generalized lambda----- */
    cout << "--------demo3--------" << endl;
    demo3();
}

