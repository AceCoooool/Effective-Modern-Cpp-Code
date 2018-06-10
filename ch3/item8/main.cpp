#include <iostream>
#include <mutex>
#include <memory>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: overload func----- */
void f(int) { cout << "f(int)" << endl; }

void f(bool) { cout << "f(bool)" << endl; }

void f(void *) { cout << "f(void *)" << endl; }

void demo1() {
    f(0);
    // Note: f(NULL) throw error in my compiler
//    f(NULL);
    f(nullptr);
}

class Widget {
public:
    Widget() {}
};

using MuxGuard = lock_guard<mutex>;

/* -----demo2: mutex----- */
void f1(shared_ptr<Widget> spw) {
    cout << "f1(shared_ptr)" << endl;
}

void f2(unique_ptr<Widget> upw) {
    cout << "f2(unique_ptr)" << endl;
}

void f3(Widget *pw) {
    cout << "f3(int *)" << endl;
}

// C++11
template<typename FuncType, typename MuxType, typename PtrType>
auto lockAndCall(FuncType func, MuxType &mutex, PtrType ptr) -> decltype(func(ptr)) {
    MuxGuard g(mutex);
    return func(ptr);
};

// C++14
template<typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall14(FuncType func, MuxType &mutex, PtrType ptr) {
    MuxGuard g(mutex);
    return func(ptr);
};

void demo2() {
    mutex f1m, f2m, f3m;
    // Note: will throw error
//    lockAndCall(f1, f1m, 0);
//    lockAndCall(f2, f2m, NULL);
    lockAndCall(f1, f1m, nullptr);
    lockAndCall(f2, f2m, nullptr);
    lockAndCall(f3, f3m, nullptr);
    lockAndCall14(f1, f1m, nullptr);
    lockAndCall14(f2, f2m, nullptr);
    lockAndCall14(f3, f3m, nullptr);
}

int main() {
/* -----demo1: overload func----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: mutex----- */
    cout << "--------demo2--------" << endl;
    demo2();
}
