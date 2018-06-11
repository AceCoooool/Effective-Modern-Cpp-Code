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

/* -----demo1: braced initializers----- */
void f(const vector<int> &v) {
    cout << "call void (vector<int>&)" << endl;
}

template<typename ...Ts>
void fwd(Ts &&... params) {
    f(forward<Ts>(params)...);
}

void demo1() {
    f({1, 2, 3});
    // Note: error
//    fwd({1, 2, 3});
    auto il = {1, 2, 3};
    fwd(il);
}

/* -----demo2: static const member----- */
class Widget {
public:
    static const size_t MinVals = 28;
};

void f1(size_t val) {
    cout << "call void (size_t)" << endl;
}

template<typename ...Ts>
void fwd1(Ts &&... params) {
    f1(forward<Ts>(params)...);
}

// necessary for perfect forward
const size_t Widget::MinVals;

void demo2() {
    f1(Widget::MinVals);
    // Note: error --- if without definition
//    fwd1(Widget::MinVals);
    fwd1(Widget::MinVals);
}

/* -----demo3: overloaded func names and template name----- */
void f3(int (*pf)(int)) {
    cout << "call void (int (*)(int))" << endl;
}

int processVal(int value) {
    cout << "process(int)" << endl;
    return 0;
}

int processVal(int value, int priority) {
    cout << "process(int, int)" << endl;
    return 0;
}

template<typename T>
T workOnVal(T param) {
    return param;
}

template<typename ...Ts>
void fwd3(Ts &&... params) {
    f3(forward<Ts>(params)...);
}

void demo3() {
    f3(processVal);
    // Note: error
//    fwd3(processVal);
    using FuncType = int (*)(int);
    FuncType processPtr = processVal;
    fwd3(processPtr);
    // Note: error
//    fwd3(workOnVal);
    fwd3(static_cast<FuncType>(workOnVal));
}

/* -----demo4: bit field----- */
struct IPv4 {
    uint32_t version:4, IHL:4, DSCP:6, ECN:2, totalLength:16;
};

void f4(size_t sz) {
    cout << "call void (size_t)" << endl;
}

template<typename ...Ts>
void fwd4(Ts &&... params) {
    f4(forward<Ts>(params)...);
}

void demo4() {
    IPv4 h;
    f4(h.totalLength);
    // Note: error
//    fwd4(h.totalLength);
    auto length = static_cast<uint16_t >(h.totalLength);
    fwd4(length);
}

int main() {
/* -----demo1: braced initializers----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: static const member----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: overloaded func names and template name----- */
    cout << "--------demo3--------" << endl;
    demo3();
/* -----demo4: bit field----- */
    cout << "--------demo4--------" << endl;
    demo4();
}

