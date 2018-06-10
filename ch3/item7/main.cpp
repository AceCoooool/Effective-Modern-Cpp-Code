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
class Widget1 {
public:
    Widget1(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget1(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget1(initializer_list<long double> il) { cout << "Widget(initializer_list<long double>)" << endl; }

    // 默认构造函数
    Widget1() { cout << "default constructor" << endl; }

    // 复制构造函数
    Widget1(const Widget1 &w) { cout << "copy constructor" << endl; }

    // 复制赋值运算符
    Widget1 &operator=(const Widget1 &w) { cout << "copy operator=" << endl; }
};

void demo2() {
    Widget1 w1;
    Widget1 w2 = w1;
    w1 = w2;
}


/* -----demo3: initializer_list----- */
class Widget2 {
public:
    Widget2(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget2(int i, double d) { cout << "Widget(int, double)" << endl; }
};

void demo3() {
    Widget2 w1(10, true);
    Widget2 w2{10, true};
    Widget2 w3(10, 5.0);
    Widget2 w4{10, 5.0};
}


class Widget3 {
public:
    Widget3(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget3(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget3(initializer_list<long double> il) { cout << "Widget(initializer_list)" << endl; }
};

void demo4() {
    Widget3 w1(10, true);
    Widget3 w2{10, true};
    Widget3 w3(10, 5.0);
    Widget3 w4{10, 5.0};
}

class Widget4 {
public:
    Widget4(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget4(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget4(initializer_list<long double> il) : tmp(il) { cout << "Widget(initializer_list)" << endl; }

    Widget4() { cout << "default constructor" << endl; }

    Widget4(const Widget4 &w) { cout << "copy constructor" << endl; }

    Widget4(Widget4 &&w) { cout << "move constructor" << endl; }

    Widget4 &operator=(const Widget4 &w) { cout << "copy operator=" << endl; }

private:
    vector<long double> tmp;
};

void demo5() {
    Widget4 w4{10, 5.0};
    Widget4 w5(w4);
    // Note: the output is not the same as the book
    Widget4 w6{w4};
    Widget4 w7(std::move(w4));
    Widget4 w8{std::move(w4)};
}

class Widget5 {
public:
    Widget5(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget5(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget5() { cout << "default constructor" << endl; }

    Widget5(initializer_list<bool> il) { cout << "Widget(initializer_list<bool>)" << endl; }
};

void demo6() {
//    Widget5 w{10, 5.0};  // Note: this will throw error
    Widget5 w1;
    Widget5 w2{};
    Widget5 w3({});
    Widget5 w4{{}};
}


class Widget6 {
public:
    Widget6(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget6(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget6() { cout << "default constructor" << endl; }

    Widget6(initializer_list<string> il) { cout << "Widget(initializer_list<string>)" << endl; }
};

void demo7(){
    Widget6 w1(10, true);
    Widget6 w2{10, true};
    Widget6 w3(10, 5.0);
    Widget6 w4{10, 5.0};
}

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

void demo8() {
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
    cout << "--------demo7--------" << endl;
    demo7();
/* -----demo4: template----- */
    cout << "--------demo7--------" << endl;
    demo8();
}
