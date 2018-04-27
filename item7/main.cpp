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

class Widget {
public:
    Widget(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget(initializer_list<long double> il) { cout << "Widget(initializer_list<long double>)" << endl; }

    Widget() { cout << "default constructor" << endl; }

    Widget(const Widget &w) { cout << "copy constructor" << endl; }

    Widget &operator=(const Widget &w) { cout << "copy operator=" << endl; }
};

class Widget2 {
public:
    Widget2(int i, bool b) { cout << "Widget(int, bool)" << endl; }

    Widget2(int i, double d) { cout << "Widget(int, double)" << endl; }

    Widget2(initializer_list<bool> il) { cout << "Widget(initializer_list<long double>)" << endl; }

    Widget2() { cout << "default constructor" << endl; }

    Widget2(const Widget &w) { cout << "copy constructor" << endl; }

    Widget2 &operator=(const Widget &w) { cout << "copy operator=" << endl; }
};

/* -----demo2: class initialize----- */
void demo2() {
    Widget w1;
    Widget w2 = w1;
    w1 = w2;
}

/* -----demo3: initializer_list----- */
void demo3() {
    Widget w1(10, true);
    Widget w2{10, true};
    Widget w3(10, 5.0);
    Widget w4{10, 5.0};

    // Note: results is different with book
    Widget w5(w4);
    Widget w6{w4};
    Widget w7(move(w4));
    Widget w8{move(w4)};
}

void demo4(){
    Widget2 w{10, 5.0};  // Note: will throw error
}

/* -----demo4: template----- */


int main() {
/* -----demo1: initialize----- */
//    demo1();
/* -----demo2: class initialize----- */
//    demo2();
/* -----demo3: initializer_list----- */
//    demo3();
    demo4();
}
