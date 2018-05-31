#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----case1: typeid----- */
void demo1() {
    const int theAnswer = 42;
    auto x = theAnswer;
    auto y = &theAnswer;
    cout << "type x: " << typeid(x).name() << endl;
    cout << "type y: " << typeid(y).name() << endl;
}

template<typename T>
void f(const T &param) {
    cout << "T=" << typeid(T).name() << endl;
    cout << "param=" << typeid(param).name() << endl;
}

void demo2() {
    vector<int> vec{1, 2, 3, 5};
    const auto vw = vec;
    if (!vw.empty())
        f(&vw[0]);
}

/* -----case2: boost typeindex----- */
template<typename T>
void f2(const T &param) {
    cout << "T=" << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "param=" << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo3(){
    vector<int> vec{1, 2, 3, 5};
    const auto vw = vec;
    if (!vw.empty())
        f2(&vw[0]);
}


int main() {
/* -----case1: typeid----- */
    cout << "------demo1------" << endl;
    demo1();
    cout << "------demo2------" << endl;
    demo2();
/* -----case2: boost typeindex----- */
    cout << "------demo3------" << endl;
    demo3();
}
