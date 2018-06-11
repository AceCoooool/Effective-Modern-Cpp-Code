#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <chrono>
#include <memory>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

/* -----demo1: move own----- */
// C++11
template<typename T>
typename remove_reference<T>::type &&
move11(T &&param) {
    using ReturnType = typename remove_reference<T>::type &&;
    return static_cast<ReturnType >(param);
}

// C++14
template<typename T>
decltype(auto) move14(T &&param) {
    using ReturnType = remove_reference_t<T> &&;
    return static_cast<ReturnType >(param);
}

void demo1() {
    vector<int> v;
    cout << type_id_with_cvr<decltype(v)>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(move11(v))>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(move14(v))>().pretty_name() << endl;
}

class Temp {
public:
    Temp(string s) : temp(s) {};

    Temp(const Temp &rhs) : temp(rhs.temp) { cout << "call Temp(const Temp &rhs)" << endl; };

    Temp(Temp &&rhs) : temp(move(rhs.temp)) { cout << "call Temp(Temp &&rhs)" << endl; };

private:
    string temp;
};

class Annotation {
public:
    explicit Annotation(const Temp t) : tmp(move(t)) {};

private:
    Temp tmp;
};

void demo2() {
    Temp s("hello");
    Annotation a1(s);
}

/* -----demo2: forward----- */
class Widget {
public:
    Widget() = default;
};

void makeLogEntry(string s, chrono::system_clock::time_point now) {
    time_t now_c = chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    cout << s << put_time(localtime(&now_c), "%F %T") << endl;
}

void process(const Widget &lval) {
    cout << "process with left val" << endl;
}

void process(Widget &&rval) {
    cout << "process with right val" << endl;
}

template<typename T>
void logAndProcess(T &&param) {
    auto now = chrono::system_clock::now();
    makeLogEntry("Calling process: ", now);
    process(param);
    process(forward<T>(param));
}

void demo3() {
    Widget w;
    logAndProcess(w);
    logAndProcess(move(w));
}

/* -----demo3: forward vs move----- */
class Widget2 {
public:
    Widget2(Widget2 &&rhs) : s(move(rhs.s)) {
        ++moveCtorCalls;
    }

    Widget2() = default;

    static void Print() {
        cout << "nums: " << moveCtorCalls << endl;
    }

private:
    static size_t moveCtorCalls;
    string s;
};

size_t Widget2::moveCtorCalls = 0; //静态成员变量的定义性说明

class Widget3 {
public:
    Widget3(Widget3 &&rhs) : s(forward<string>(rhs.s)) {   // Note: potential bug rhs.s is string&
        ++moveCtorCalls;
    }

    Widget3() = default;

    static void Print() {
        cout << "nums: " << moveCtorCalls << endl;
    }

private:
    static size_t moveCtorCalls;
    string s;
};

size_t Widget3::moveCtorCalls = 0; //静态成员变量的定义性说明

void demo4() {
    cout << "move version" << endl;
    Widget2 w1;
    Widget2::Print();
    Widget2 w2(move(w1));
    Widget2::Print();
    cout << "forward version" << endl;
    Widget3 w31;
    Widget3::Print();
    Widget3 w32(move(w31));
    Widget3::Print();
}

int main() {
/* -----demo1: move own----- */
    cout << "--------demo1--------" << endl;
    demo1();
    cout << "--------demo2--------" << endl;
    demo2();
/* -----demo2: forward----- */
    cout << "--------demo3--------" << endl;
    demo3();
/* -----demo4: forward vs move----- */
    cout << "--------demo4--------" << endl;
    demo4();
}

