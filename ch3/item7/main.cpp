#include <iostream>
#include <valarray>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: initialize----- */
void demo1() {
    int x(0);
    int y = 0;
    int z{0};
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;
}

/* -----demo2: class initialize----- */
class Widget {
public:
    Widget(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget(initializer_list<long double> il) { cout << "Widget(initializer_list<long double>)" << endl; }

    // 默认构造函数
    Widget() { cout << "default constructor" << endl; }

    // 复制构造函数
    Widget(const Widget &w) { cout << "copy constructor" << endl; }

    // 复制赋值运算符
    Widget &operator=(const Widget &w) { cout << "copy operator=" << endl; }
};

void demo2() {
    Widget w1;
    Widget w2 = w1;
    w1 = w2;
}

/* -----demo3: initializer_list----- */
class Widget1 {
public:
    Widget1(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget1(int i, double d) { cout << "Widget(int, double)" << endl; }
};

void demo3() {
    Widget1 w1(10, true);
    Widget1 w2{10, true};
    Widget1 w3(10, 5.0);
    Widget1 w4{10, 5.0};
}


class Widget2 {
public:
    Widget2(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget2(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget2(initializer_list<long double> il) { cout << "Widget(initializer_list)" << endl; }
};

void demo4() {
    Widget2 w1(10, true);
    Widget2 w2{10, true};
    Widget2 w3(10, 5.0);
    Widget2 w4{10, 5.0};
}

class Widget3 {
public:
    Widget3(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget3(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget3(initializer_list<long double> il) : tmp(il) { cout << "Widget(initializer_list)" << endl; }

    Widget3() { cout << "default constructor" << endl; }

    Widget3(const Widget3 &w) { cout << "copy constructor" << endl; }

    Widget3(Widget3 &&w) { cout << "move constructor" << endl; }

    Widget3 &operator=(const Widget3 &w) { cout << "copy operator=" << endl; }

private:
    vector<long double> tmp;
};

void demo5() {
    Widget3 w4{10, 5.0};
    Widget3 w5(w4);
    // Note: the output is not the same as the book
    Widget3 w6{w4};
    Widget3 w7(std::move(w4));
    Widget3 w8{std::move(w4)};
}

class Widget4 {
public:
    Widget4(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget4(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget4() { cout << "default constructor" << endl; }

    Widget4(initializer_list<bool> il) { cout << "Widget(initializer_list<long double>)" << endl; }
};

void demo6() {
    // Note: this will throw error
//    Widget4 w{10, 5.0};
    Widget4 w1;
    Widget4 w2{};
    Widget4 w3({});
    Widget4 w4{{}};
}


//void demo3() {
//    Widget w1(10, true);
//    Widget w2{10, true};
//    Widget w3(10, 5.0);
//    Widget w4{10, 5.0};
//
//    // Note: results is different with book
//    Widget w5(w4);
//    Widget w6{w4};
//    Widget w7(move(w4));
//    Widget w8{move(w4)};
//}


/* -----demo4: template----- */
template<typename T, typename ... Ts>
void doSomeWork1(Ts &&... params) {
    T local(std::forward<Ts>(params)...);
    for (auto a: local)
        cout << a << " ";
    cout << endl;
};

template<typename T, typename ... Ts>
void doSomeWork2(Ts &&... params) {
    T local{std::forward<Ts>(params)...};
    for (auto a: local)
        cout << a << " ";
    cout << endl;
};

void demo7(){
    doSomeWork1<vector<int>>(10, 20);
    doSomeWork2<vector<int>>(10, 20);
}

int main() {
/* -----demo1: initialize----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: class initialize----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: initializer_list----- */
    cout << "--------demo3--------" << endl;
    demo3();
    cout << "--------demo4--------" << endl;
    demo4();
    cout << "--------demo5--------" << endl;
    demo5();
    cout << "--------demo6--------" << endl;
    demo6();
/* -----demo4: template----- */
    cout << "--------demo7--------" << endl;
    demo7();
}
