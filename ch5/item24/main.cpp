#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <chrono>
#include <memory>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: rvalue reference vs universal reference----- */
class Widget {
};

template<typename T>
void f2(vector<T> &&param);

template<typename T>
void f3(T &&param);

void demo1() {
    // rvalue reference
    cout << "rvalue reference:" << endl;
    void f(Widget &&param);
    cout << type_id_with_cvr<decltype(f)>().pretty_name() << endl;
    Widget &&var1 = Widget();
    cout << type_id_with_cvr<decltype(var1)>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(f2<Widget>)>().pretty_name() << endl;
    // universal reference
    cout << "universal reference:" << endl;
    auto &&var2 = var1;
    cout << type_id_with_cvr<decltype(var2)>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(f3<Widget>)>().pretty_name() << endl;
}

/* -----demo2: universal reference----- */
template<typename T>
void ff(T &&param) {
    cout << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

void demo2() {
    Widget w;
    ff(w);
    ff(move(w));
}

/* -----demo3: rvalue reference vs universal reference 2----- */
template<class T, class Allocator=allocator<T>>
class vector_own {
public:
    // rvalue reference
    void push_back(T &&x) {
        cout << type_id_with_cvr<decltype(x)>().pretty_name() << endl;
    }

    // universal reference
    template<class Args>
    void emplace_back(Args &&args) {
        cout << type_id_with_cvr<decltype(args)>().pretty_name() << endl;
    }
};

void demo3() {
    vector_own<Widget> v;
    Widget w;
//    v.push_back(w);   // error
    v.push_back(move(w));
    v.emplace_back(w);
}

/* -----demo4: auto &&----- */
auto funcInvocation = [](auto &&func, auto &&... params) {
    forward<decltype(func)>(func)(forward<decltype(params)>(params)...);
};

struct callable {
    explicit callable(string s) : str(move(s)) {};

    string operator()(int, double) const &{
        cout << "call operator()(int, double)const & --- lvalue" << endl;
        return str;
    }

    string operator()(int, double) &&{
        cout << "call operator()(int, double)&& --- rvalue" << endl;
        return move(str);
    }

private:
    string str;
};

void demo4() {
    funcInvocation(callable("one"), 2, 3.4);
    callable a("one");
    funcInvocation(a, 2, 3.4);
}


int main() {
/* -----demo1: rvalue reference vs universal reference----- */
    cout << "--------demo1--------" << endl;
    demo1();
/* -----demo2: universal reference----- */
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo3: rvalue reference vs universal reference 2----- */
    cout << "--------demo3--------" << endl;
    demo3();
/* -----demo4: auto &&----- */
    cout << "--------demo4--------" << endl;
    demo4();
}

