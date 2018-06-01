#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: constexpr variable----- */
void demo1() {
    // Note: error
//    int sz;
//    constexpr auto arraySize1 = sz;
//    array<int, sz> data1;
    constexpr auto arraySize2 = 10;
    array<int, arraySize2> data2;
    cout << arraySize2 << endl;
    cout << "array size: " << data2.size() << endl;
}

/* -----demo2: constexpr function----- */
// C++11
constexpr int pow1(int base, int exp) noexcept {
    return (exp == 0 ? 1 : base * pow1(base, exp - 1));
}

// C++14
constexpr int pow2(int base, int exp) noexcept {
    auto result = 1;
    for (int i = 0; i < exp; ++i)
        result *= base;
    return result;
}

void demo2() {
    constexpr auto numConds = 5;
    array<int, pow1(3, numConds)> results;
    cout << results.size() << endl;
    array<int, pow2(3, numConds)> results2;
    cout << results2.size() << endl;
    int i = 5;
    auto num = pow1(3, i);
    cout << num << endl;
}

/* -----demo3: constexpr class function----- */
// C++11
class Point {
public:
    constexpr Point(double xval = 0, double yval = 0) noexcept : x(xval), y(yval) {}

    constexpr double xValue() const noexcept { return x; }

    constexpr double yValue() const noexcept { return y; }

    // only support by C++14
    constexpr void setX(double newX) noexcept { x = newX; }

    constexpr void setY(double newY) noexcept { y = newY; }

private:
    double x, y;
};

constexpr Point midpoint(const Point &p1, const Point &p2) noexcept {
    return {(p1.xValue() + p2.xValue()) / 2, (p1.yValue() + p2.yValue()) / 2};
}

// for c++14
constexpr Point reflection(const Point &p) noexcept {
    Point result;
    result.setX(-p.xValue());
    result.setY(-p.yValue());
    return result;
}

void demo3() {
    constexpr Point p1(9.4, 27.7);
    constexpr Point p2(28.8, 5.3);
    constexpr auto mid = midpoint(p1, p2);
    cout << mid.xValue() << ", " << mid.yValue() << endl;
    constexpr auto reflectMid = reflection(mid);
    cout << reflectMid.xValue() << ", " << reflectMid.yValue() << endl;
}


int main() {
/* -----demo1: constexpr variable----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: without override----- */
    cout << "--------demo2--------" << endl;
    demo2();
    cout << "--------demo3--------" << endl;
    demo3();

}
