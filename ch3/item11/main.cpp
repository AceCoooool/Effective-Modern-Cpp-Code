#include <iostream>
#include <memory>
#include <unordered_map>
#include <list>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: delete in function----- */
bool isLucky(int number) {
    cout << "call bool (int)" << endl;
    return (number == 3);
}

bool isLucky(char) = delete;

bool isLucky(bool) = delete;

bool isLucky(double) = delete;

void demo1() {
    cout << isLucky(10) << endl;
    // Note: illegal form
//    cout << isLucky(true) << endl;
//    cout << isLucky(10.0) << endl;
//    cout << isLucky('a') << endl;
}

/* -----demo2: delete in template----- */
template<typename T>
void processPointer(T *ptr) {
    cout << "call void (T *ptr)" << endl;
    cout << *ptr << endl;
}

template<>
void processPointer<void>(void *)= delete;

template<>
void processPointer<char>(char *)= delete;

template<>
void processPointer<const void>(const void *)= delete;

template<>
void processPointer<const char>(const char *)= delete;

void demo2() {
    int num[] = {1, 2, 3};
    processPointer(num);
    // Note: illegal
//    char a[] = {'a', 'b', 'c'};
//    processPointer(a);
}

int main() {
/* -----demo1: delete in function----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: delete in template----- */
    cout << "--------demo2--------" << endl;
    demo2();
}
