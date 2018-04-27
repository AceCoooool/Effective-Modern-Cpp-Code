#include <iostream>
#include <mutex>
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

using MuxGuard = lock_guard<mutex>;

/* -----demo2: mutex----- */
void f1(shared_ptr<int> spw) {
    cout << "f1(shared_ptr)" << endl;
}

void f2(unique_ptr<int> upw) {
    cout << "f2(unique_ptr)" << endl;
}

void f3(int *pw) {
    cout << "f3(int *)" << endl;
}

template<typename FuncType, typename MuxType, typename PtrType>
auto lockAndCall(FuncType func, MuxType &mutex, PtrType ptr) -> decltype(func(ptr)) {
    MuxGuard g(mutex);
    return func(ptr);
};

void demo2() {
    mutex f1m, f2m, f3m;
    // Note: will throw error
//    lockAndCall(f1, f1m, 0);
//    lockAndCall(f2, f2m, NULL);
    lockAndCall(f3, f3m, nullptr);
}

int main() {
/* -----demo1: overload func----- */
//    demo1();
/* -----demo2: mutex----- */
    demo2();
}
