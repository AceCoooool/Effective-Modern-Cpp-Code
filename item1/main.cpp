#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----case 1----- */
template<typename T>
void f(T &param) {
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param=" << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo1() {
    int x = 27;
    const int cx = x;
    const int &rx = x;
    f(x);
    f(cx);
    f(rx);
}

template<typename T>
void f2(const T &param) {
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param=" << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo2() {
    int x = 27;
    const int cx = x;
    const int &rx = x;
    f2(x);
    f2(cx);
    f2(rx);
}

template<typename T>
void f3(T *param) {
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param=" << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo3() {
    int x = 27;
    const int *px = &x;
    f3(&x);
    f3(px);
}

/* -----case 2----- */
template<typename T>
void f4(T &&param) {
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param=" << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo4() {
    int x = 27;
    const int cx = x;
    const int &rx = x;
    f4(x);
    f4(cx);
    f4(rx);
    f4(27);
}

/* -----case 3----- */
template<typename T>
void f5(T param) {
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param=" << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo5() {
    int x = 27;
    const int cx = x;
    const int &rx = x;
    f5(x);
    f5(cx);
    f5(rx);
}

void demo6() {
    const char *const ptr = "Fun with pointers";
    f5(ptr);
}

/* -----array----- */
void demo7() {
    const char name[] = "J. P. Briggs";
    const char *ptrToName = name;
    f5(name);
}

void demo8() {
    const char name[] = "J. P. Briggs";
    const char *ptrToName = name;
    f(name);
}

template<typename T, size_t N>
constexpr size_t arraySize(T (&)[N]) noexcept {
    return N;
};

void demo9() {
    int keyVals[] = {1, 3, 7, 9, 11, 22, 35};
    int mappedVals[arraySize(keyVals)];
    cout << "Infer size: " << arraySize(keyVals) << endl;
}

/* -----function----- */
void someFunc(int, double) {};

void demo10() {
    f5(someFunc);
    f(someFunc);
}

int main() {
/*-----case 1----*/
//    demo1();
//    demo2();
//    demo3();
/*-----case 2----*/
//    demo4();
/*-----case 3----*/
//    demo5();
//    demo6();
/*-----array----*/
//    demo7();
//    demo8();
//    demo9();
/*-----functions----*/
    demo10();
}