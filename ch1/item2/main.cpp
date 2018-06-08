#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----case 1&3----- */
void demo1() {
    auto x = 27;
    const auto cx = x;
    const auto &rx = x;
    cout << "x: " << type_id_with_cvr<decltype(x)>().pretty_name() << endl;
    cout << "cx: " << type_id_with_cvr<decltype(cx)>().pretty_name() << endl;
    cout << "rx: " << type_id_with_cvr<decltype(rx)>().pretty_name() << endl;
}

/* -----case 2----- */
void demo2() {
    auto x = 27;
    const auto cx = x;
    const auto &rx = x;

    auto &&uref1 = x;
    auto &&uref2 = cx;
    auto &&uref3 = 27;
    cout << "uref1: " << type_id_with_cvr<decltype(uref1)>().pretty_name() << endl;
    cout << "uref2: " << type_id_with_cvr<decltype(uref2)>().pretty_name() << endl;
    cout << "uref3: " << type_id_with_cvr<decltype(uref3)>().pretty_name() << endl;
}

/* -----array & functions----- */
void someFunc(int, double) {}

void demo3() {
    const char name[] = "R. N. Briggs";
    auto arr1 = name;  // Note: compound array initializer is expected
    cout << "arr1: " << type_id_with_cvr<decltype(arr1)>().pretty_name() << endl;
    auto &arr2 = name;
    cout << "arr2: " << type_id_with_cvr<decltype(arr2)>().pretty_name() << endl;

    auto func1 = someFunc;
    cout << "fun1: " << type_id_with_cvr<decltype(func1)>().pretty_name() << endl;
    auto &func2 = someFunc;
    cout << "fun2: " << type_id_with_cvr<decltype(func2)>().pretty_name() << endl;
}

/* -----initializer_list----- */
template<typename T>
void f(std::initializer_list<T> initList) {
    cout << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "initList: " << type_id_with_cvr<decltype(initList)>().pretty_name() << endl;
}

void demo4() {
    auto x1 = 27;
    auto x2(27);
    auto x3 = {27};
    auto x4{27};   // Note: different with "book"
    cout << "x1: " << type_id_with_cvr<decltype(x1)>().pretty_name() << endl;
    cout << "x2: " << type_id_with_cvr<decltype(x2)>().pretty_name() << endl;
    cout << "x3: " << type_id_with_cvr<decltype(x3)>().pretty_name() << endl;
    cout << "x4: " << type_id_with_cvr<decltype(x4)>().pretty_name() << endl;
    f({11, 12, 13});
}

// C++14
auto createInit() {
    return 1;
}

void demo5() {
    cout << "auto func: " << type_id_with_cvr<decltype(createInit)>().pretty_name() << endl;
    vector<int> v;
    auto resetV = [&v](const auto &newValue) { v = newValue; };
    vector<int> v2{2, 3, 4};
    resetV(v2);
    for (auto a: v)
        cout << a << " ";
    cout << endl;
}


int main() {
/*-----case 1&3----*/
    cout << "------demo1------" << endl;
    demo1();
/* -----case 2----- */
    cout << "------demo2------" << endl;
    demo2();
/* -----array & functions----- */
    cout << "------demo3------" << endl;
    demo3();
/* -----initializer_list----- */
    cout << "------demo4------" << endl;
    demo4();
/* -----C++14----- */
    cout << "------demo5------" << endl;
    demo5();
}
