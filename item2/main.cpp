#include <iostream>
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
    cout << "x: " << type_id_with_cvr<decltype(uref1)>().pretty_name() << endl;
    cout << "cx: " << type_id_with_cvr<decltype(uref2)>().pretty_name() << endl;
    cout << "rx: " << type_id_with_cvr<decltype(uref3)>().pretty_name() << endl;
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


int main() {
/*-----case 1&3----*/
//    demo1();
/* -----case 2----- */
//    demo2();
/* -----array & functions----- */
    demo3();
}