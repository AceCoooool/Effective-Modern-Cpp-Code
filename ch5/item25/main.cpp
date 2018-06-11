#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <chrono>
#include <valarray>
#include <memory>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: move & forward----- */
// Note: bad code
class Widget1 {
public:
    template<typename T>
    void setName(T &&newName) {
        name = move(newName);
    }

private:
    string name;
    shared_ptr<int> p;
};

string getWidgetName() {
    return string("name");
}

void demo1() {
    Widget1 w;
    auto n = getWidgetName();
    cout << n << endl;
    w.setName(n);   // 左值引用强制被转换为右值
    cout << n << endl;  // n becomes unknown
}

// Note: bad code
class Widget2 {
public:
    void setName(const string &newName) {
        cout << "call setName(const string&)" << endl;
        name = newName;
    }

    void setName(string &&newName) {
        cout << "call setName(string &&)" << endl;
        name = move(newName);
    }

private:
    string name;
    shared_ptr<int> p;
};

void demo2() {
    Widget2 w;
    w.setName("Adela Novak");
}

// good code
class Widget3 {
public:
    template<typename T>
    void setName(T &&newName) {
        name = forward<T>(newName);
    }

private:
    string name;
    shared_ptr<int> p;
};

void demo3() {
    Widget3 w;
    auto n = getWidgetName();
    cout << n << endl;
    w.setName(n);
    cout << n << endl;
}

/* -----demo2: back with move & forward----- */
// good code
template<typename T>
valarray<T> addopt(valarray<T> &&lhs, valarray<T> &rhs) {
    lhs += rhs;
    return move(lhs);
}

void demo4() {
    valarray<int> lhs{1, 2, 3, 4};
    valarray<int> rhs{2, 3, 4, 5};
    valarray<int> res = addopt(move(lhs), rhs);
    for (auto a: res)
        cout << a << " ";
    cout << endl;
}


int main() {
/* -----demo1: rvalue reference vs universal reference----- */
    cout << "--------demo1--------" << endl;
    demo1();
    cout << "--------demo2--------" << endl;
    demo2();
    cout << "--------demo3--------" << endl;
    demo3();
/* -----demo2: back with move & forward----- */
    cout << "--------demo4--------" << endl;
    demo4();
}

