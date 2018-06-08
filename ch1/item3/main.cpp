#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----case1: typical cases----- */
struct Widget {
};

struct Point {
    static int x, y;
};

bool f(const Widget &w) {
    cout << "decltype(w): " << type_id_with_cvr<decltype(w)>().pretty_name() << endl;
};

void demo1() {
    const int i = 0;
    cout << "decltype(i): " << type_id_with_cvr<decltype(i)>().pretty_name() << endl;
    cout << "decltype(f): " << type_id_with_cvr<decltype(f)>().pretty_name() << endl;
    cout << "decltype(Point::x): " << type_id_with_cvr<decltype(Point::x)>().pretty_name() << endl;
    Widget w;
    cout << "decltype(w): " << type_id_with_cvr<decltype(w)>().pretty_name() << endl;
    cout << "decltype(f(w)): " << type_id_with_cvr<decltype(f(w))>().pretty_name() << endl;
    vector<int> v{1, 2, 3};
    cout << "decltype(v): " << type_id_with_cvr<decltype(v)>().pretty_name() << endl;
    cout << "decltype(v[0]): " << type_id_with_cvr<decltype(v[0])>().pretty_name() << endl;
}

/* -----case2: decltype using in return param----- */
vector<string> makeString() {
    return {"hello", "hi", "ha", "hei", "hehe", "hiha"};
}

// c++11: works, but requires refinements
template<typename Container, typename Index>
auto authAndAccess11(Container &c, Index i) -> decltype(c[i]) {
    cout << "decltype(c[i]): " << type_id_with_cvr<decltype(c[i])>().pretty_name() << endl;
    return c[i];
};

// c++11: final C++11 version
template<typename Container, typename Index>
auto authAndAccess11_v2(Container &&c, Index i) -> decltype(std::forward<Container>(c)[i]) {
    cout << "decltype(c[i]): " << type_id_with_cvr<decltype(std::forward<Container>(c)[i])>().pretty_name() << endl;
    return std::forward<Container>(c)[i];
}

// c++14: not quite correct
template<typename Container, typename Index>
// C++14:
auto authAndAccess14(Container &c, Index i) {
    return c[i];
}

// c++14: works, but requires refinements
template<typename Container, typename Index>
// C++14:
decltype(auto) authAndAccess14_v2(Container &c, Index i) {
    return c[i];
}

// c++14: perfect
template<typename Container, typename Index>
decltype(auto) authAndAccess14_v3(Container &&c, Index i) {
    return std::forward<Container>(c)[i];
}


void demo2() {
    vector<int> vec = {3, 4, 45, 6, 7};
    auto res = authAndAccess11(vec, 2);
    auto s = authAndAccess11_v2(makeString(), 2);
    auto t1 = authAndAccess14(vec, 2);
    auto t2 = authAndAccess14_v2(vec, 2);
    auto t3 = authAndAccess14_v3(makeString(), 2);
}

/* -----case3: x or (x)----- */
void demo3() {
    auto x = 10;
    cout << "x: " << type_id_with_cvr<decltype(x)>() << endl;
    cout << "x: " << type_id_with_cvr<decltype((x))>() << endl;
}

int main() {
/* -----case1: typical cases----- */
    cout << "------demo1------" << endl;
    demo1();
    cout << "------demo2------" << endl;
    demo2();
/* -----case3: x or (x)----- */
    cout << "------demo3------" << endl;
    demo3();
}
